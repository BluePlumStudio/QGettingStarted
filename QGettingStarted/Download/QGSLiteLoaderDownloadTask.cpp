#include "QGSLiteLoaderDownloadTask.h"

QGSLiteLoaderDownloadTask::QGSLiteLoaderDownloadTask(QFile * targetFile, const QGSDownloadInfo & downloadInfo, const QNetworkProxy & proxy, QObject * parent)
	:QGSDownloadTask(targetFile, downloadInfo, proxy, parent)
{

}

QGSLiteLoaderDownloadTask::~QGSLiteLoaderDownloadTask()
{
}
