#include "QGSLiteLoaderDownloadTask.h"

QGSLiteLoaderDownloadTask::QGSLiteLoaderDownloadTask(QFile * targetFile, const QGSDownloadInfo & downloadInfo, int connectionCount, const QNetworkProxy & proxy, QObject * parent)
	:QGSDownloadTask(targetFile, downloadInfo, connectionCount, proxy, parent)
{

}

QGSLiteLoaderDownloadTask::~QGSLiteLoaderDownloadTask()
{
}
