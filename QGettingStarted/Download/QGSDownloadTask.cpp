#include <QFileInfo>
#include <QCoreApplication>
#include <QDir>
#include <QMutexLocker>
#include <QMutex>
#include <QTimer>

#include "QGSDownloadTask.h"
#include "../Util/QGSUuidGenerator.h"
#include "../Util/QGSOperatingSystem.h"
#include "../Util/QGSExceptionInvalidValue.h"

static const QString SEPARATOR{ QGSOperatingSystem::getInstance().getSeparator() };

/**/

QGSDownloadTask::QGSDownloadTask(QFile * targetFile, const QGSDownloadInfo & downloadInfo, int threadCount, const QNetworkProxy & proxy, QObject * parent)
	:mTargetFilePtr(targetFile), 
	mDownloadInfo(downloadInfo), 
	mThreadCount(threadCount), 
	mProxy(proxy), 
	mBytesReceived(0),
	mDelete(false), 
	mState(State::Stop), 
	mReply(nullptr), 
	mNetworkAccessManagerPtr(nullptr)
{
	if (!mTargetFilePtr)
	{
		throw QGSExceptionInvalidValue();
	}

	if (threadCount < 1)
	{
		threadCount = 1;
	}

	mDownloadInfo.setPath(mTargetFilePtr->fileName());
}

QGSDownloadTask::~QGSDownloadTask()
{
	if (mReply)
	{
		mReply->deleteLater();
		mReply = nullptr;
	}

	if (mNetworkAccessManagerPtr)
	{
		mNetworkAccessManagerPtr->deleteLater();
		mNetworkAccessManagerPtr = nullptr;
	}
}

QFile * QGSDownloadTask::getTargetFile()
{
	return mTargetFilePtr;
}

QGSDownloadTask::State QGSDownloadTask::getState()
{
	return mState;
}

QGSDownloadInfo QGSDownloadTask::getDownloadInfo()
{
	return mDownloadInfo;
}

QString QGSDownloadTask::generateRandomFileName()
{
	return QString{ QGSUuidGenerator::generateUuid() + ".qtmp" };
}

void QGSDownloadTask::templateStart(QGSTask * task)
{
	if (mState == State::Start)
	{
		emit error(this);
		return;
	}
    auto && request{ QGSNetworkAccessManager::generateHttpsNetworkRequest() };

	auto && url{ mDownloadInfo.getUrl() };
	if (!url.isValid()
		|| url.isEmpty()
		|| url.isLocalFile())
	{
		emit error(this);
		return;
	}

	request.setUrl(url);
	request.setAttribute(QNetworkRequest::FollowRedirectsAttribute, true);
	request.setRawHeader(QByteArray{ "Connection" }, QByteArray{ "Keep-Alive" });
	request.setRawHeader(QByteArray{ "Keep-Alive" }, QByteArray{ "Timeout=60" });
	mDownloadInfo.setUrl(url);

	mTargetFilePtr->setFileName(mTargetFilePtr->fileName() + ".qtmp");
	if (!mTargetFilePtr->isOpen())
	{
		QFileInfo{ *mTargetFilePtr }.absoluteDir().mkpath("." + SEPARATOR);
		if (!mTargetFilePtr->open(QIODevice::WriteOnly | QIODevice::Truncate))
		{
			emit error(this);
			return;
		}
	}

	if (mBytesReceived)
	{
		QString strRange = QString("bytes=%1-").arg(mBytesReceived);
		request.setRawHeader("Range", strRange.toLatin1());
	}
	if (!mNetworkAccessManagerPtr)
	{
		mNetworkAccessManagerPtr = new QGSNetworkAccessManager;
	}
	//mNetworkAccessManagerPtr->connectToHostEncrypted(url.host(), url.port(), request.sslConfiguration());
	mNetworkAccessManagerPtr->setProxy(mProxy);
	mReply = mNetworkAccessManagerPtr->get(request);
	if (!mReply)
	{
		emit error(this);
		emit downloadError(QGSNetworkError{ QNetworkReply::NetworkError::UnknownNetworkError,"Unknown download task error!" }, this);
		return;
	}

	connect(mReply, QOverload<QNetworkReply::NetworkError>::of(&QNetworkReply::error), this, &QGSDownloadTask::slotError);
	connect(mReply, &QNetworkReply::sslErrors, this, &QGSDownloadTask::slotSslErrors);
	connect(mReply, &QNetworkReply::redirected, this, &QGSDownloadTask::slotRedirected);

	if (!waitForConnected())
	{
		if (mReply)
		{
			mReply->disconnect();
			mReply->deleteLater();
			mReply = nullptr;
		}

		emit error(this);
		emit downloadError(QGSNetworkError{ QNetworkReply::NetworkError::UnknownNetworkError,"Unknown download task error!" }, this);
		return;
	}

	mState = State::Start;

	emit started(this);
}

void QGSDownloadTask::templateStop(QGSTask * task)
{
	mState = State::Stop;

	mTargetFilePtr->flush();
	mBytesReceived = mTargetFilePtr->size();
	if (mReply)
	{
		mReply->disconnect();
		mReply->deleteLater();
		mReply = nullptr;
	}
}

void QGSDownloadTask::templateCancel(QGSTask * task)
{
	mState = State::Stop;

	mTargetFilePtr->flush();
	mTargetFilePtr->close();
	mBytesReceived = 0;
	mDelete = false;
	mTargetFilePtr->remove();
	if (mReply)
	{
		mReply->disconnect();
		mReply->deleteLater();
		mReply = nullptr;
	}

	if (mNetworkAccessManagerPtr)
	{
		mNetworkAccessManagerPtr->disconnect();
		mNetworkAccessManagerPtr->deleteLater();
		mNetworkAccessManagerPtr = nullptr;
	}
}

void QGSDownloadTask::downloadTemplateFinished()
{
}

void QGSDownloadTask::downloadTemplateDownloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
}

void QGSDownloadTask::downloadTemplateError(QNetworkReply::NetworkError error)
{
}

void QGSDownloadTask::downloadTemplateSslErrors(const QList<QSslError>& errors)
{
}

void QGSDownloadTask::downloadTemplateRedirected(const QUrl & url)
{
}

bool QGSDownloadTask::waitForConnected()
{
	QTimer *timer{ nullptr };
	QEventLoop eventLoop;
	bool readTimeOut{ false };
	const int timeOutms{ 5000 };

	if (timeOutms > 0)
	{
		timer = new QTimer{ this };

		connect(timer, &QTimer::timeout, [&readTimeOut]()
		{
			readTimeOut = true;
		});
		connect(timer, &QTimer::timeout, &eventLoop, &QEventLoop::quit);
		timer->setSingleShot(true);
	}

	connect(mNetworkAccessManagerPtr, &QGSNetworkAccessManager::finished, &eventLoop, &QEventLoop::quit);

	if (!mReply)
	{
		timer->start(timeOutms);
		eventLoop.exec();
	}

	if (mReply)
	{
		// Preferrably we wait for the first reply which comes faster than the finished signal
		connect(mReply, &QNetworkReply::downloadProgress, this, &QGSDownloadTask::slotDownloadProgress);
		connect(mReply, &QNetworkReply::finished, this, &QGSDownloadTask::slotFinished);
	}

	if (!timer)
	{
		timer->stop();
		delete timer;
		timer = nullptr;
	}
	
	return !readTimeOut;
}

quint64 QGSDownloadTask::getFileSize()
{
	QTimer *timer{ nullptr };
	QEventLoop eventLoop;
	bool readTimeOut{ false };
	const int timeOutms{ 5000 };
	quint64 ret{ 0 };

	if (timeOutms > 0)
	{
		timer = new QTimer{ this };

		connect(timer, &QTimer::timeout, [&readTimeOut]()
		{
			readTimeOut = true;
		});
		connect(timer, &QTimer::timeout, &eventLoop, &QEventLoop::quit);
		timer->setSingleShot(true);
	}

	auto && request{ QGSNetworkAccessManager::generateHttpsNetworkRequest() };
	request.setUrl(mDownloadInfo.getUrl());
	request.setAttribute(QNetworkRequest::FollowRedirectsAttribute, true);

	connect(mNetworkAccessManagerPtr, &QGSNetworkAccessManager::finished, &eventLoop, &QEventLoop::quit);

	auto * headReply{ mNetworkAccessManagerPtr->head(request) };
	if (!headReply)
	{
		timer->start(timeOutms);
		eventLoop.exec();
	}

	if (headReply)
	{
		auto && contentLength{ headReply->header(QNetworkRequest::ContentLengthHeader) };
		headReply->deleteLater();
		ret = contentLength.toLongLong();
	}

	if (!timer)
	{
		timer->stop();
		delete timer;
		timer = nullptr;
	}

	return ret;
}

void QGSDownloadTask::slotFinished()
{	
	downloadTemplateFinished();

	mTargetFilePtr->flush();
	mTargetFilePtr->close();
	mTargetFilePtr->remove(mDownloadInfo.getPath());
	mTargetFilePtr->rename(mDownloadInfo.getPath());
	if (!mDownloadInfo.getSHA1().isEmpty())
	{

	}

	if (mDelete)
	{
		mTargetFilePtr->remove();
	}

	if (mReply)
	{
		mReply->disconnect();
		mReply->deleteLater();
		mReply = nullptr;
	}
	if (mNetworkAccessManagerPtr)
	{
		mNetworkAccessManagerPtr->disconnect();
		mNetworkAccessManagerPtr->deleteLater();
		mNetworkAccessManagerPtr = nullptr;
	}

	emit finished(this);
}

void QGSDownloadTask::slotDownloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
	downloadTemplateDownloadProgress(bytesReceived, bytesTotal);

	if (mReply)
	{
		mTargetFilePtr->write(mReply->readAll());
		mTargetFilePtr->flush();
	}

	emit downloadProgress(mBytesReceived + bytesReceived, bytesTotal, this);
}

void QGSDownloadTask::slotError(QNetworkReply::NetworkError _error)
{
	downloadTemplateError(_error);
	auto && errorString{ mReply ? mReply->errorString() : "" };
	auto && errorCode{ mReply ? mReply->error() : QNetworkReply::NetworkError::UnknownNetworkError };
	cancel();

	emit error(this);
	emit downloadError(QGSNetworkError{ errorCode,errorString }, this);
}

void QGSDownloadTask::slotSslErrors(const QList<QSslError>& errors)
{
	downloadTemplateSslErrors(errors);
	cancel();

	emit error(this);
	emit sslErrors(errors, this);
}

void QGSDownloadTask::slotRedirected(const QUrl & url)
{
	downloadTemplateRedirected(url);
}
