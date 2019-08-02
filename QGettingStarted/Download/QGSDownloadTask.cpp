#include <QFileInfo>
#include <QDir>
#include <QMutexLocker>
#include <QMutex>
#include <QTimer>
#include <QEventLoop>

#include "QGSDownloadTask.h"
#include "../Util/QGSUuidGenerator.h"
#include "../Util/QGSOperatingSystem.h"
#include "../Util/QGSExceptionInvalidValue.h"

static const QString SEPARATOR(QGSOperatingSystem::getInstance().getSeperator());
quint64 QGSDownloadTask::mLargeFileSize(4194304);
quint64 QGSDownloadTask::mSmallFileSize(262144);
const int QGSDownloadTask::DefaultConnectionCount(8);
/**/

QGSDownloadTask::QGSDownloadTask(int connectionCount, const QNetworkProxy & proxy, QObject * parent)
	:QGSTask(parent),
	mConnectionCount(connectionCount),
	mProxy(proxy),
	mBytesReceived(0),
	mBytesTotal(0),
	mState(DownloadState::Stop),
	mNetworkHelperPtr(nullptr)
{
	if (connectionCount < 1)
	{
		connectionCount = QGSDownloadTask::DefaultConnectionCount;
	}
}

QGSDownloadTask::QGSDownloadTask(QFile * targetFile, const QGSDownloadInfo downloadInfo, int connectionCount, const QNetworkProxy & proxy, QObject * parent)
	:QGSTask(parent),
	mTargetFilePtr(targetFile),
	mDownloadInfo(downloadInfo),
	mConnectionCount(connectionCount),
	mProxy(proxy),
	mBytesReceived(0),
	mBytesTotal(0),
	mState(DownloadState::Stop),
	mNetworkHelperPtr(nullptr)
{
	if (!mTargetFilePtr)
	{
		throw QGSExceptionInvalidValue();
	}

	if (connectionCount < 1)
	{
		connectionCount = QGSDownloadTask::DefaultConnectionCount;
	}

	mDownloadInfo.setPath(mTargetFilePtr->fileName());
}

QGSDownloadTask::~QGSDownloadTask()
{
	/*
	if (mReply)
	{
		mReply->deleteLater();
		mReply = nullptr;
	}
	*/

	if (mNetworkHelperPtr)
	{
		mNetworkHelperPtr->deleteLater();
		mNetworkHelperPtr = nullptr;
	}
}

QGSDownloadTask & QGSDownloadTask::setTargetFile(QFile * targetFile)
{
	mTargetFilePtr = targetFile;
	return *this;
}

QGSDownloadTask & QGSDownloadTask::setDownloadInfo(const QGSDownloadInfo & downloadInfo)
{
	mDownloadInfo = downloadInfo;
	return *this;
}

QFile * QGSDownloadTask::getTargetFile()
{
	return mTargetFilePtr;
}

DownloadState QGSDownloadTask::getState()
{
	return mState;
}

QGSDownloadInfo QGSDownloadTask::getDownloadInfo()
{
	return mDownloadInfo;
}

QString QGSDownloadTask::generateRandomFileName()
{
	return QString(QGSUuidGenerator::generateUuid() + ".qtmp");
}

void QGSDownloadTask::setLargeFileSize(const quint64 bytes)
{
	if (bytes > mSmallFileSize)
	{
		mLargeFileSize = bytes;
	}
}

void QGSDownloadTask::setSmallFileSize(const quint64 bytes)
{
	if (bytes < mLargeFileSize)
	{
		mSmallFileSize = bytes;
	}
}

void QGSDownloadTask::templateStart(QGSTask * task)
{
	emit started(this);

	if (mState != DownloadState::Start)
	{
		mState = DownloadState::Start;

		auto && url(mDownloadInfo.getUrl());
		if (!url.isValid()
			|| url.isEmpty()
			|| url.isLocalFile())
		{
			emit error(this);
			return;
		}

		mDownloadInfo.setPath(mTargetFilePtr->fileName());
		mDownloadInfo.setUrl(url);

		mTargetFilePtr->setFileName(mTargetFilePtr->fileName() + ".qtmp");
		if (!mTargetFilePtr->isOpen())
		{
			QFileInfo(*mTargetFilePtr).absoluteDir().mkpath("." + SEPARATOR);
			if (!mTargetFilePtr->open(QIODevice::WriteOnly | QIODevice::Truncate))
			{
				emit error(this);
				return;
			}
		}

		if (!mNetworkHelperPtr)
		{
			mNetworkHelperPtr = new QGSNetworkHelper();
			//mNetworkHelperPtr = &QGSNetworkHelper::getGlobalInstance();
		}

		if (mDownloaderList.size())
		{
			for (auto & downloader : mDownloaderList)
			{
				QObject::connect(downloader, &QGSDownloader::finished, this, &QGSDownloadTask::slotFinished);
				QObject::connect(downloader, &QGSDownloader::downloadProgress, this, &QGSDownloadTask::slotDownloadProgress);
				QObject::connect(downloader, &QGSDownloader::downloadError, this, &QGSDownloadTask::slotDownloadError);
				QObject::connect(downloader, &QGSDownloader::sslErrors, this, &QGSDownloadTask::slotSslErrors);
				QObject::connect(downloader, &QGSDownloader::redirected, this, &QGSDownloadTask::slotRedirected);

				//QMetaObject::invokeMethod(downloader, "start", Qt::ConnectionType::DirectConnection);
				downloader->start();
			}
		}
		else
		{
			mBytesTotal = getFileSize();
			if (mConnectionCount > mBytesTotal)
			{
				mConnectionCount = QGSDownloadTask::DefaultConnectionCount;
			}

			if (mBytesTotal <= mSmallFileSize)
			{
				mConnectionCount = 1;
			}

			for (int i = 0; i < mConnectionCount; i++)
			{
				qint64 bytesBegin(mBytesTotal*i / mConnectionCount);
				qint64 bytesEnd(mBytesTotal*(i + 1) / mConnectionCount);

				auto * newDownloader(new QGSDownloader(mTargetFilePtr, mDownloadInfo, mNetworkHelperPtr, bytesBegin, bytesEnd, mProxy));

				QObject::connect(newDownloader, &QGSDownloader::finished, this, &QGSDownloadTask::slotFinished);
				QObject::connect(newDownloader, &QGSDownloader::downloadProgress, this, &QGSDownloadTask::slotDownloadProgress);
				QObject::connect(newDownloader, &QGSDownloader::downloadError, this, &QGSDownloadTask::slotDownloadError);
				QObject::connect(newDownloader, &QGSDownloader::sslErrors, this, &QGSDownloadTask::slotSslErrors);
				QObject::connect(newDownloader, &QGSDownloader::redirected, this, &QGSDownloadTask::slotRedirected);

				mDownloaderList.push_back(newDownloader);

				//QEventLoop eventLoop;
				//QObject::connect(newDownloader, &QGSDownloader::started, &eventLoop, &QEventLoop::quit);
				//QMetaObject::invokeMethod(newDownloader, "start", Qt::ConnectionType::AutoConnection);
				//eventLoop.exec();
				newDownloader->start();
			}
		}
	}
}

void QGSDownloadTask::templateStop(QGSTask * task)
{
	emit stoped(this);

	if (mState != DownloadState::Stop)
	{
		mState = DownloadState::Stop;

		for (auto & downloader : mDownloaderList)
		{
			QMetaObject::invokeMethod(downloader, "stop", Qt::ConnectionType::DirectConnection);
			downloader->disconnect();
		}

		if (mTargetFilePtr->isOpen())
		{
			mTargetFilePtr->close();
		}
	}
}

void QGSDownloadTask::templateCancel(QGSTask * task)
{
	mState = DownloadState::Stop;

	emit canceled(this);

	cancelTask();
}

void QGSDownloadTask::downloadTemplateFinished()
{
}

void QGSDownloadTask::downloadTemplateDownloadProgress(qint64 bytesNewlyReceived, qint64 bytesReceived, qint64 bytesTotal)
{
}

void QGSDownloadTask::downloadTemplateError(QGSNetworkError error)
{
}

void QGSDownloadTask::downloadTemplateSslErrors(const QList<QSslError>& errors)
{
}

void QGSDownloadTask::downloadTemplateRedirected(const QUrl & url)
{
}


void QGSDownloadTask::slotFinished(QGSDownloader * downloader)
{	
	for (auto it = mDownloaderList.begin(); it != mDownloaderList.end(); it++)
	{
		if (*it == downloader)
		{
			(*it)->disconnect();
			(*it)->deleteLater();
			mDownloaderList.erase(it);
			break;
		}
	}

	if (mDownloaderList.size())
	{
		return;
	}

	downloadTemplateFinished();

	if (mTargetFilePtr->isOpen())
	{
		mTargetFilePtr->close();
	}
	mTargetFilePtr->remove(mDownloadInfo.getPath());
	mTargetFilePtr->rename(mDownloadInfo.getPath());
	if (!mDownloadInfo.getSHA1().isEmpty())
	{

	}

	if (mNetworkHelperPtr)
	{
		mNetworkHelperPtr->getNetworkAccessManager()->disconnect();
		mNetworkHelperPtr->deleteLater();
		mNetworkHelperPtr = nullptr;
	}

	mBytesReceived = 0;

	emit finished(this);
}

void QGSDownloadTask::slotDownloadProgress(qint64 bytesNewlyReceived, qint64 bytesReceived, qint64 bytesTotal, QGSDownloader * downloader)
{
	downloadTemplateDownloadProgress(bytesNewlyReceived, bytesReceived, bytesTotal);
	
	mBytesReceived += bytesNewlyReceived;

    emit downloadProgress(mBytesReceived, mBytesTotal, this);
}

void QGSDownloadTask::slotDownloadError(QGSNetworkError _error, QGSDownloader * downloader)
{
	downloadTemplateError(_error);
	cancelTask();

	emit downloadError(_error, this);
	emit error(this);
}

void QGSDownloadTask::slotSslErrors(const QList<QSslError>& errors, QGSDownloader * downloader)
{
	downloadTemplateSslErrors(errors);
	cancelTask();

	emit sslErrors(errors, this);
	emit error(this);
}

void QGSDownloadTask::slotRedirected(const QUrl & url, QGSDownloader * downloader)
{
	downloadTemplateRedirected(url);
}

quint64 QGSDownloadTask::getFileSize()
{
	QTimer *timer(nullptr);
	QEventLoop eventLoop;
	bool readTimeOut(false);
	const int timeOutms(60000);
	quint64 ret(0);

	if (timeOutms > 0)
	{
		timer = new QTimer(this);

		connect(timer, &QTimer::timeout, [&readTimeOut]()
		{
			readTimeOut = true;
		});
		connect(timer, &QTimer::timeout, &eventLoop, &QEventLoop::quit);
		timer->setSingleShot(true);
	}

	auto && request(QGSNetworkHelper::generateHttpsNetworkRequest());
	request.setUrl(mDownloadInfo.getUrl());
	request.setAttribute(QNetworkRequest::FollowRedirectsAttribute, true);

	auto * headReply(mNetworkHelperPtr->getNetworkAccessManager()->head(request));
	QObject::connect(headReply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit, Qt::DirectConnection);
	timer->start(timeOutms);

	eventLoop.exec();

	if (headReply)
	{
		ret = headReply->header(QNetworkRequest::ContentLengthHeader).toLongLong();
		headReply->deleteLater();
	}

	if (timer)
	{
		timer->stop();
		timer->deleteLater();
		timer = nullptr;
	}

	return ret;
}

void QGSDownloadTask::cancelTask()
{
	for (auto it = mDownloaderList.begin(); it != mDownloaderList.end(); it++)
	{
		QMetaObject::invokeMethod((*it), "cancel", Qt::ConnectionType::DirectConnection);
		(*it)->disconnect();
		(*it)->deleteLater();
		mDownloaderList.erase(it);
	}

	if (mTargetFilePtr->isOpen())
	{
		mTargetFilePtr->close();
	}
	mBytesReceived = 0;
	mTargetFilePtr->remove();

	if (mNetworkHelperPtr)
	{
		mNetworkHelperPtr->getNetworkAccessManager()->disconnect();
		mNetworkHelperPtr->deleteLater();
		mNetworkHelperPtr = nullptr;
	}
}
