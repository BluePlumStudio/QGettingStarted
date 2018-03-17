#include "QGSDownloaderLibrary.h"

QGSDownloaderLibrary::QGSDownloaderLibrary(QFile * targetFile, const DownloadInfo & downloadInfo, const QNetworkProxy & proxy, QObject * parent)
	:QGSDownloader(targetFile, downloadInfo, proxy, parent)
{

}

QGSDownloaderLibrary::~QGSDownloaderLibrary()
{
	if (mTargetFilePtr)
	{
		mTargetFilePtr->deleteLater();
	}
}
