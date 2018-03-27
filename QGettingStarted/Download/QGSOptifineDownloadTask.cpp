#include "QGSOptifineDownloadTask.h"

QGSOptifineDownloadTask::QGSOptifineDownloadTask(QFile * targetFile, const QGSDownloadInfo & downloadInfo, const QNetworkProxy & proxy, QObject * parent)
	:QGSDownloadTask(targetFile, downloadInfo, proxy, parent)
{

}

QGSOptifineDownloadTask::~QGSOptifineDownloadTask()
{
}
