#include "QGSOptifineDownloadTask.h"

QGSOptifineDownloadTask::QGSOptifineDownloadTask(QFile * targetFile, const QGSDownloadInfo & downloadInfo, int threadCount, const QNetworkProxy & proxy, QObject * parent)
	:QGSDownloadTask(targetFile, downloadInfo, threadCount, proxy, parent)
{

}

QGSOptifineDownloadTask::~QGSOptifineDownloadTask()
{
}
