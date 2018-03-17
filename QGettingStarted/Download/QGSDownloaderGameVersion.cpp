#include "QGSDownloaderGameVersion.h"

QGSDownloaderGameVersion::QGSDownloaderGameVersion(QFile * targetFile, const DownloadInfo & downloadInfo, const QNetworkProxy & proxy, QObject * parent)
	:QGSDownloader(targetFile, downloadInfo, proxy, parent)
{

}

QGSDownloaderGameVersion::~QGSDownloaderGameVersion()
{
	if (mTargetFilePtr)
	{
		mTargetFilePtr->deleteLater();
	}
}
