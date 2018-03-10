#include <QFileInfo>
#include <QCoreApplication>
#include <QDir>

#include "QGSDownloader.h"
#include "QGSOperatingSystem.h"

static QString SEPATATOR{ QGSOperatingSystem::getInstance().getSeparator() };

QGSDownloader::QGSDownloader(const DownloadInfo & downloadInfo, QObject *parent)
	: QObject(parent), mDownloadInfo(downloadInfo), mFile(nullptr), mReply(nullptr)
{

}

QGSDownloader::~QGSDownloader()
{
}

bool QGSDownloader::start()
{
	auto request{ QGSNetwork::generateNetworkRequestWithSSL() };
	//检查Url是否为空以及有效
	auto && url{ mDownloadInfo.getUrl() };
	if(!url.isValid()
		|| url.isEmpty()
		|| url.isLocalFile())
	{
		return false;
	}
	url = QGSNetwork::getRedirectURL(url);
	mDownloadInfo.setUrl(url);
	request.setUrl(url);
	//检查下载路径
	if(mDownloadInfo.getPath().isEmpty())
	{
		QFileInfo fileInfo{ url.toString() };
		mDownloadInfo.setPath(QCoreApplication::applicationDirPath()
			+ SEPATATOR + fileInfo.fileName());
		
	}

	mFile.setFileName(QFileInfo{ mDownloadInfo.getPath() }.absolutePath() + SEPATATOR + "QGSDownloaderTempFile.tmp");
	if (!mFile.open(QIODevice::WriteOnly | QIODevice::Truncate))
	{
		return false;
	}

	mReply = QGSNetwork::getInstance().getManager()->get(request);
	if (!mReply)
	{
		return false;
	}

	connect(mReply, &QNetworkReply::downloadProgress, this, &QGSDownloader::downloadProgressSlot);
	connect(mReply, &QNetworkReply::finished, this, &QGSDownloader::finishedSlot);

	return true;
}

QFile * QGSDownloader::generateFile() const
{
	return new QFile{ mFile.fileName() };
}

void QGSDownloader::finishedSlot()
{
	mFile.flush();
	mFile.close();
	mFile.rename(mDownloadInfo.getPath());
	mReply->deleteLater();
	mReply = nullptr;

	emit finished();
}

void QGSDownloader::downloadProgressSlot(qint64 bytesReceived, qint64 bytesTotal)
{
	auto receivedData{ mReply->readAll() };
	mFile.write(receivedData);
	mFile.flush();

	emit downloadProgress(bytesReceived, bytesTotal);
}
