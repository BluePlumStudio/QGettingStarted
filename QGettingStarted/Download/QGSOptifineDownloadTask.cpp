#include "QGSOptifineDownloadTask.h"

QGSOptifineDownloadTask::QGSOptifineDownloadTask(QFile * targetFile, const QGSDownloadInfo & downloadInfo, int connectionCount, const QNetworkProxy & proxy, QObject * parent)
	:QGSDownloadTask(targetFile, downloadInfo, connectionCount, proxy, parent)
{

}

QGSOptifineDownloadTask::~QGSOptifineDownloadTask()
{
}
