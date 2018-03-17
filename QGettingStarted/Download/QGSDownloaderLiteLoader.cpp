#include "QGSDownloaderLiteLoader.h"

QGSDownloaderLiteLoader::QGSDownloaderLiteLoader(QFile * targetFile, const DownloadInfo & downloadInfo, const QNetworkProxy & proxy, QObject * parent)
	:QGSDownloader(targetFile, downloadInfo, proxy, parent)
{

}

QGSDownloaderLiteLoader::~QGSDownloaderLiteLoader()
{
}
