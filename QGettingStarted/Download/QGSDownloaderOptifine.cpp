#include "QGSDownloaderOptifine.h"

QGSDownloaderOptifine::QGSDownloaderOptifine(QFile * targetFile, const DownloadInfo & downloadInfo, const QNetworkProxy & proxy, QObject * parent)
	:QGSDownloader(targetFile, downloadInfo, proxy, parent)
{

}

QGSDownloaderOptifine::~QGSDownloaderOptifine()
{
}
