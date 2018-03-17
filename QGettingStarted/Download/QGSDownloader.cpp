#include <QFileInfo>
#include <QCoreApplication>
#include <QDir>
#include <QTimer>
#include <QMutexLocker>
#include <QMutex>

#include "QGSDownloader.h"
#include "QGSUuidGenerator.h"
#include "QGSOperatingSystem.h"

static const QString SEPARATOR{ QGSOperatingSystem::getInstance().getSeparator() };

QGSDownloader::QGSDownloader(QFile * targetFile, const DownloadInfo & downloadInfo, const QNetworkProxy & proxy, QObject * parent)
	:mTargetFilePtr(targetFile), mDownloadInfo(downloadInfo), QObject(parent), mProxy(proxy), mBytesReceived(0), mDelete(false), mState(State::Stop)
{
	setTimeout(Network::DefaultTimeout);
}

QGSDownloader::~QGSDownloader()
{
	if (mReply)
	{
		mReply->deleteLater();
	}
}

bool QGSDownloader::start()
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

	connect(mReply, &QNetworkReply::downloadProgress, this, &QGSDownloader::slotDownloadProgress);
	connect(mReply, &QNetworkReply::finished, this, &QGSDownloader::slotFinished);
	connect(mReply, QOverload<QNetworkReply::NetworkError>::of(&QNetworkReply::error), this, &QGSDownloader::slotError);
	connect(mReply, &QNetworkReply::sslErrors, this, &QGSDownloader::slotSslErrors);
	connect(&mTimer, &QTimer::timeout, this, &QGSDownloader::slotTimeout);
	connect(mReply, &QNetworkReply::redirected, this, &QGSDownloader::slotRedirected);
	mTimer.moveToThread(this->thread());

	mState = State::Start;
	return true;
}

bool QGSDownloader::stop()
{
	mState = State::Stop;

	mTargetFilePtr->flush();
	mBytesReceived = mTargetFilePtr->size();
	if (mReply)
	{
		disconnect(mReply, &QNetworkReply::downloadProgress, this, &QGSDownloader::slotDownloadProgress);
		disconnect(mReply, &QNetworkReply::finished, this, &QGSDownloader::slotFinished);
		disconnect(mReply, QOverload<QNetworkReply::NetworkError>::of(&QNetworkReply::error), this, &QGSDownloader::slotError);
		disconnect(mReply, &QNetworkReply::sslErrors, this, &QGSDownloader::slotSslErrors);
		disconnect(&mTimer, &QTimer::timeout, this, &QGSDownloader::slotTimeout);
		disconnect(mReply, &QNetworkReply::redirected, this, &QGSDownloader::slotRedirected);
		mReply->deleteLater();
		mReply = nullptr;
	}
	return true;
}

bool QGSDownloader::cancel()
{
	mState = State::Stop;

	mTargetFilePtr->flush();
	mTargetFilePtr->close();
	mBytesReceived = 0;
	mDelete = false;
	mTargetFilePtr->remove();
	if (mReply)
	{
		disconnect(mReply, &QNetworkReply::downloadProgress, this, &QGSDownloader::slotDownloadProgress);
		disconnect(mReply, &QNetworkReply::finished, this, &QGSDownloader::slotFinished);
		disconnect(mReply, QOverload<QNetworkReply::NetworkError>::of(&QNetworkReply::error), this, &QGSDownloader::slotError);
		disconnect(mReply, &QNetworkReply::sslErrors, this, &QGSDownloader::slotSslErrors);
		disconnect(&mTimer, &QTimer::timeout, this, &QGSDownloader::slotTimeout);
		disconnect(mReply, &QNetworkReply::redirected, this, &QGSDownloader::slotRedirected);
		mReply->deleteLater();
		mReply = nullptr;
	}

	return true;
}

QGSDownloader & QGSDownloader::setTimeout(const int msec)
{
	mTimer.setInterval(msec);
	return *this;
}

int QGSDownloader::getTimeout() const
{
	return mTimer.interval();
}

QFile * QGSDownloader::getTargetFile()
{
	return mTargetFilePtr;
}

QGSDownloader::State QGSDownloader::getState() const
{
	return mState;
}

void QGSDownloader::stepFinished()
{

}

void QGSDownloader::stepDownloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{

}

void QGSDownloader::stepError(QNetworkReply::NetworkError code)
{

}

void QGSDownloader::stepSslErrors(const QList<QSslError>& errors)
{

}

void QGSDownloader::stepTimeout()
{

}

void QGSDownloader::stepRedirected(const QUrl & url)
{

}

void QGSDownloader::slotFinished()
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

void QGSDownloader::slotDownloadProgress(qint64 bytesReceived, qint64 bytesTotal)
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

void QGSDownloader::slotError(QNetworkReply::NetworkError code)
{
	auto && errorString{ mReply ? mReply->errorString() : "" };
	cancel();
	stepError(code);

	emit error(Error{ code,errorString }, mDownloadInfo);
}

void QGSDownloader::slotSslErrors(const QList<QSslError>& errors)
{
	cancel();
	stepSslErrors(errors);

	emit sslErrors(errors, mDownloadInfo);
}

void QGSDownloader::slotTimeout()
{
	stop();
	stepTimeout();

	emit timeout(mDownloadInfo);
}

void QGSDownloader::slotRedirected(const QUrl & url)
{
	stepRedirected(url);
}

QString QGSDownloader::generateRandomFileName()
{
	return QString{ QGSUuidGenerator::generateUuid() + ".tmp" };
}
