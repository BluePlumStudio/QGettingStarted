#include "QGSDownloaderForge.h"

QGSDownloaderForge::QGSDownloaderForge(QFile * targetFile, const DownloadInfo & downloadInfo, const QNetworkProxy & proxy, QObject * parent)
	:QGSDownloader(targetFile, downloadInfo, proxy, parent)
{

}

QGSDownloaderForge::~QGSDownloaderForge()
{
}
