#include <QFileInfo>
#include <QCoreApplication>
#include <QDir>
#include <QTimer>
#include <QMutexLocker>
#include <QMutex>

#include "QGSDownloadTask.h"
#include "QGSUuidGenerator.h"
#include "QGSOperatingSystem.h"

static const QString SEPARATOR{ QGSOperatingSystem::getInstance().getSeparator() };

QGSDownloadTask::QGSDownloadError::QGSDownloadError(const QNetworkReply::NetworkError code, const QString & message)
	:mCode(code), mMessage(message)
{

}

QGSDownloadTask::QGSDownloadError::~QGSDownloadError()
{

}

QNetworkReply::NetworkError QGSDownloadTask::QGSDownloadError::getCode()const
{
	return mCode;
}

QString QGSDownloadTask::QGSDownloadError::getMessage()const
{
	return mMessage;
}

/**/

QGSDownloadTask::QGSDownloadTask(QFile * targetFile, const DownloadInfo & downloadInfo, const QNetworkProxy & proxy, QObject * parent)
	:mTargetFilePtr(targetFile), mDownloadInfo(downloadInfo), mProxy(proxy), mBytesReceived(0), mDelete(false), mState(State::Stop)
{
	setTimeout(Network::DefaultTimeout);
}

QGSDownloadTask::~QGSDownloadTask()
{
	if (mReply)
	{
		mReply->deleteLater();
	}
}


QGSDownloadTask & QGSDownloadTask::setTimeout(const int msec)
{
	mTimer.setInterval(msec);
	return *this;
}

int QGSDownloadTask::getTimeout() const
{
	return mTimer.interval();
}

QFile * QGSDownloadTask::getTargetFile()
{
	return mTargetFilePtr;
}

QGSDownloadTask::State QGSDownloadTask::getState() const
{
	return mState;
}

QString QGSDownloadTask::generateRandomFileName()
{
	return QString{ QGSUuidGenerator::generateUuid() + "qtmp" };
}

void QGSDownloadTask::templateStart(QGSTask * task)
{
	if (mState == State::Start)
	{
		emit error(this);
		return;
	}
	auto request{ QGSNetwork::generateNetworkRequestWithSSL() };

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

	mDownloadInfo.setPath(mTargetFilePtr->fileName());
	mTargetFilePtr->setFileName(mTargetFilePtr->fileName() + "qtmp");

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
	mReply = QGSNetwork::getInstance().setProxy(mProxy).get(request);
	QGSNetwork::getInstance().setProxy(QNetworkProxy::NoProxy);

	connect(mReply, &QNetworkReply::downloadProgress, this, &QGSDownloadTask::slotDownloadProgress);
	connect(mReply, &QNetworkReply::finished, this, &QGSDownloadTask::slotFinished);
	connect(mReply, QOverload<QNetworkReply::NetworkError>::of(&QNetworkReply::error), this, &QGSDownloadTask::slotError);
	connect(mReply, &QNetworkReply::sslErrors, this, &QGSDownloadTask::slotSslErrors);
	connect(&mTimer, &QTimer::timeout, this, &QGSDownloadTask::slotTimeout);
	connect(mReply, &QNetworkReply::redirected, this, &QGSDownloadTask::slotRedirected);
	mTimer.moveToThread(this->thread());

	mState = State::Start;
}

void QGSDownloadTask::templateStop(QGSTask * task)
{
}

void QGSDownloadTask::templateCancel(QGSTask * task)
{
}

void QGSDownloadTask::downloadTemplateFinished()
{
}

void QGSDownloadTask::downloadTemplateDownloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
}

void QGSDownloadTask::downloadTemplateError(QNetworkReply::NetworkError code)
{
}

void QGSDownloadTask::downloadTemplateSslErrors(const QList<QSslError>& errors)
{
}

void QGSDownloadTask::downloadTemplateTimeout()
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
	mTimer.stop();
	downloadTemplateDownloadProgress(bytesReceived, bytesTotal);

	if (mReply)
	{
		mTargetFilePtr->write(mReply->readAll());
		mTargetFilePtr->flush();
	}

	mTimer.start();
	emit downloadProgress(mBytesReceived + bytesReceived, bytesTotal, this);
}

void QGSDownloadTask::slotError(QNetworkReply::NetworkError code)
{
	auto && errorString{ mReply ? mReply->errorString() : "" };
	cancel();
	downloadTemplateError(code);

	emit downloadError(QGSDownloadError{ code,errorString }, this);
}

void QGSDownloadTask::slotSslErrors(const QList<QSslError>& errors)
{
	cancel();
	downloadTemplateSslErrors(errors);

	emit sslErrors(errors, this);
}

void QGSDownloadTask::slotTimeout()
{
	stop();
	downloadTemplateTimeout();

	emit timeout(this);
}

void QGSDownloadTask::slotRedirected(const QUrl & url)
{
	downloadTemplateRedirected(url);
}
