#include "QGSDownloaderAssetObject.h"

QGSDownloaderAssetObject::QGSDownloaderAssetObject(QFile * targetFile, const DownloadInfo & downloadInfo, const QNetworkProxy & proxy, QObject * parent)
	:QGSDownloader(targetFile, downloadInfo, proxy, parent)
{

}

QGSDownloaderAssetObject::~QGSDownloaderAssetObject()
{
	if (mTargetFilePtr)
	{
		mTargetFilePtr->deleteLater();
	}
}
