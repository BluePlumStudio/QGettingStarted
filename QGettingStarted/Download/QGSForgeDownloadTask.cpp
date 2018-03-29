#include "QGSForgeDownloadTask.h"

QGSForgeDownloadTask::QGSForgeDownloadTask(QFile * targetFile, const QGSDownloadInfo & downloadInfo, int threadCount, const QNetworkProxy & proxy, QObject * parent)
	:QGSDownloadTask(targetFile, downloadInfo, threadCount, proxy, parent)
{

}

QGSForgeDownloadTask::~QGSForgeDownloadTask()
{
}
