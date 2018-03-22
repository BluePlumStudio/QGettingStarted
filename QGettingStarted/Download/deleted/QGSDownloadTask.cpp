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

QGSDownloadTask::Error::Error(const QNetworkReply::NetworkError code, const QString & message)
	:mCode(code), mMessage(message)
{

}

QGSDownloadTask::Error::~Error()
{

}

QNetworkReply::NetworkError QGSDownloadTask::Error::getCode()const
{
	return mCode;
}

QString QGSDownloadTask::Error::getMessage()const
{
	return mMessage;
}

/**/

QGSDownloadTask::QGSDownloadTask(QFile * targetFile, const DownloadInfo & downloadInfo, const QNetworkProxy & proxy, QObject * parent)
	:mTargetFilePtr(targetFile), mDownloadInfo(downloadInfo), QObject(parent), mProxy(proxy), mBytesReceived(0), mDelete(false), mState(State::Stop)
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

bool QGSDownloadTask::start()
{
	if (mState == State::Start)
	{
		return false;
	}
	auto request{ QGSNetwork::generateNetworkRequestWithSSL() };
	//检查Url是否为空以及有效
	auto && url{ mDownloadInfo.getUrl() };
	if(!url.isValid()
		|| url.isEmpty()
		|| url.isLocalFile())
	{
		return false;
	}

	request.setUrl(url);
	request.setAttribute(QNetworkRequest::FollowRedirectsAttribute, true);
	mDownloadInfo.setUrl(url);

	mDownloadInfo.setPath(mTargetFilePtr->fileName());
	mTargetFilePtr->setFileName(mTargetFilePtr->fileName() + ".tmp");
	//打开文件
	if (!mTargetFilePtr->isOpen())
	{
		QFileInfo{ *mTargetFilePtr }.absoluteDir().mkpath("." + SEPARATOR);
		if (!mTargetFilePtr->open(QIODevice::WriteOnly | QIODevice::Truncate))
		{
			return false;
		}
	}

	//开始下载
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
	return true;
}

bool QGSDownloadTask::stop()
{
	mState = State::Stop;

	mTargetFilePtr->flush();
	mBytesReceived = mTargetFilePtr->size();
	if (mReply)
	{
		disconnect(mReply, &QNetworkReply::downloadProgress, this, &QGSDownloadTask::slotDownloadProgress);
		disconnect(mReply, &QNetworkReply::finished, this, &QGSDownloadTask::slotFinished);
		disconnect(mReply, QOverload<QNetworkReply::NetworkError>::of(&QNetworkReply::error), this, &QGSDownloadTask::slotError);
		disconnect(mReply, &QNetworkReply::sslErrors, this, &QGSDownloadTask::slotSslErrors);
		disconnect(&mTimer, &QTimer::timeout, this, &QGSDownloadTask::slotTimeout);
		disconnect(mReply, &QNetworkReply::redirected, this, &QGSDownloadTask::slotRedirected);
		mReply->deleteLater();
		mReply = nullptr;
	}
	return true;
}

bool QGSDownloadTask::cancel()
{
	mState = State::Stop;

	mTargetFilePtr->flush();
	mTargetFilePtr->close();
	mBytesReceived = 0;
	mDelete = false;
	mTargetFilePtr->remove();
	if (mReply)
	{
		disconnect(mReply, &QNetworkReply::downloadProgress, this, &QGSDownloadTask::slotDownloadProgress);
		disconnect(mReply, &QNetworkReply::finished, this, &QGSDownloadTask::slotFinished);
		disconnect(mReply, QOverload<QNetworkReply::NetworkError>::of(&QNetworkReply::error), this, &QGSDownloadTask::slotError);
		disconnect(mReply, &QNetworkReply::sslErrors, this, &QGSDownloadTask::slotSslErrors);
		disconnect(&mTimer, &QTimer::timeout, this, &QGSDownloadTask::slotTimeout);
		disconnect(mReply, &QNetworkReply::redirected, this, &QGSDownloadTask::slotRedirected);
		mReply->deleteLater();
		mReply = nullptr;
	}

	return true;
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

void QGSDownloadTask::stepFinished()
{

}

void QGSDownloadTask::stepDownloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{

}

void QGSDownloadTask::stepError(QNetworkReply::NetworkError code)
{

}

void QGSDownloadTask::stepSslErrors(const QList<QSslError>& errors)
{

}

void QGSDownloadTask::stepTimeout()
{

}

void QGSDownloadTask::stepRedirected(const QUrl & url)
{

}

void QGSDownloadTask::slotFinished()
{
	stepFinished();

	mTargetFilePtr->flush();
	mTargetFilePtr->close();
	mTargetFilePtr->remove(mDownloadInfo.getPath());
	mTargetFilePtr->rename(mDownloadInfo.getPath());
	if (!mDownloadInfo.getSHA1().isEmpty())
	{
		//文件SHA1检查
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

	emit finished(mDownloadInfo);
}

void QGSDownloadTask::slotDownloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
	mTimer.stop();
	stepDownloadProgress(bytesReceived, bytesTotal);

	if(mReply)
	{
		mTargetFilePtr->write(mReply->readAll());
		mTargetFilePtr->flush();
	}

	mTimer.start();
	emit downloadProgress(mBytesReceived + bytesReceived, bytesTotal, mDownloadInfo);
}

void QGSDownloadTask::slotError(QNetworkReply::NetworkError code)
{
	auto && errorString{ mReply ? mReply->errorString() : "" };
	cancel();
	stepError(code);

	emit error(Error{ code,errorString }, mDownloadInfo);
}

void QGSDownloadTask::slotSslErrors(const QList<QSslError>& errors)
{
	cancel();
	stepSslErrors(errors);

	emit sslErrors(errors, mDownloadInfo);
}

void QGSDownloadTask::slotTimeout()
{
	stop();
	stepTimeout();

	emit timeout(mDownloadInfo);
}

void QGSDownloadTask::slotRedirected(const QUrl & url)
{
	stepRedirected(url);
}

QString QGSDownloadTask::generateRandomFileName()
{
	return QString{ QGSUuidGenerator::generateUuid() + ".tmp" };
}
