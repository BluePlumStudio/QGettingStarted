#include <QFileInfo>
#include <QCoreApplication>
#include <QDir>
#include <QMutexLocker>
#include <QMutex>

#include "QGSDownloadTask.h"
#include "../Util/QGSUuidGenerator.h"
#include "../Util/QGSOperatingSystem.h"

static const QString SEPARATOR{ QGSOperatingSystem::getInstance().getSeparator() };

QGSDownloadTask::QGSDownloadTask(QFile * targetFile, const QGSDownloadInfo & downloadInfo, const QNetworkProxy & proxy, QObject * parent)
	:mTargetFilePtr(targetFile), mDownloadInfo(downloadInfo), mProxy(proxy), mBytesReceived(0), mDelete(false), mState(State::Stop), mReply(nullptr), mNetworkPtr(nullptr)
{
	if (!mTargetFilePtr)
	{

	}
	mDownloadInfo.setPath(mTargetFilePtr->fileName());

}

QGSDownloadTask::~QGSDownloadTask()
{
	if (mReply)
	{
		mReply->deleteLater();
	}

	if (mNetworkPtr)
	{
		mNetworkPtr->deleteLater();
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
    QNetworkRequest request{ QGSNetwork::generateNetworkRequestWithSsl() };

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
	if (!mNetworkPtr)
	{
		mNetworkPtr = new QGSNetwork;
	}
	//mNetworkPtr->connectToHostEncrypted(url.host(), url.port(), request.sslConfiguration());
	mReply = mNetworkPtr->setProxy(mProxy).get(request);
	if (!mReply)
	{
		emit error(this);
		return;
	}

	mReply->setParent(nullptr);

	connect(mReply, &QNetworkReply::downloadProgress, this, &QGSDownloadTask::slotDownloadProgress);
	connect(mReply, &QNetworkReply::finished, this, &QGSDownloadTask::slotFinished);
	connect(mReply, QOverload<QNetworkReply::NetworkError>::of(&QNetworkReply::error), this, &QGSDownloadTask::slotError);
	connect(mReply, &QNetworkReply::sslErrors, this, &QGSDownloadTask::slotSslErrors);
	connect(mReply, &QNetworkReply::redirected, this, &QGSDownloadTask::slotRedirected);

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
		disconnect(mReply, &QNetworkReply::downloadProgress, this, &QGSDownloadTask::slotDownloadProgress);
		disconnect(mReply, &QNetworkReply::finished, this, &QGSDownloadTask::slotFinished);
		disconnect(mReply, QOverload<QNetworkReply::NetworkError>::of(&QNetworkReply::error), this, &QGSDownloadTask::slotError);
		disconnect(mReply, &QNetworkReply::sslErrors, this, &QGSDownloadTask::slotSslErrors);
		disconnect(mReply, &QNetworkReply::redirected, this, &QGSDownloadTask::slotRedirected);
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
		disconnect(mReply, &QNetworkReply::downloadProgress, this, &QGSDownloadTask::slotDownloadProgress);
		disconnect(mReply, &QNetworkReply::finished, this, &QGSDownloadTask::slotFinished);
		disconnect(mReply, QOverload<QNetworkReply::NetworkError>::of(&QNetworkReply::error), this, &QGSDownloadTask::slotError);
		disconnect(mReply, &QNetworkReply::sslErrors, this, &QGSDownloadTask::slotSslErrors);
		disconnect(mReply, &QNetworkReply::redirected, this, &QGSDownloadTask::slotRedirected);
		mReply->deleteLater();
		mReply = nullptr;
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
		mReply->deleteLater();
		mReply = nullptr;
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
	cancel();
	downloadTemplateSslErrors(errors);

	emit error(this);
	emit sslErrors(errors, this);
}

void QGSDownloadTask::slotRedirected(const QUrl & url)
{
	downloadTemplateRedirected(url);
}

QGSDownloadInfo::QGSDownloadInfo(const QUrl & url, const QString & path, const QString & SHA1)
	:QGSIDownload(-1, SHA1, path, url)
{

}

QGSDownloadInfo::~QGSDownloadInfo()
{
}
