#include "QGSDownloaderGameVersionJson.h"

QGSDownloaderGameVersionJson::QGSDownloaderGameVersionJson(QFile * targetFile, const DownloadInfo & downloadInfo, const QNetworkProxy & proxy, QObject * parent)
	:QGSDownloader(targetFile, downloadInfo, proxy, parent)
{

}

QGSDownloaderGameVersionJson::~QGSDownloaderGameVersionJson()
{
	if (mTargetFilePtr)
	{
		mTargetFilePtr->deleteLater();
	}
}
