#include "QGSDownloaderAssetIndexJson.h"

QGSDownloaderAssetIndexJson::QGSDownloaderAssetIndexJson(QFile * targetFile, const DownloadInfo & downloadInfo, const QNetworkProxy & proxy, QObject * parent)
	:QGSDownloader(targetFile, downloadInfo, proxy, parent)
{

}

QGSDownloaderAssetIndexJson::~QGSDownloaderAssetIndexJson()
{
	if (mTargetFilePtr)
	{
		mTargetFilePtr->deleteLater();
	}
}
