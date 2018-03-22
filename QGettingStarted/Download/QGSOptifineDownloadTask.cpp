#include "QGSOptifineDownloadTask.h"

QGSOptifineDownloadTask::QGSOptifineDownloadTask(QFile * targetFile, const DownloadInfo & downloadInfo, const QNetworkProxy & proxy, QObject * parent)
	:QGSDownloadTask(targetFile, downloadInfo, proxy, parent)
{

}

QGSOptifineDownloadTask::~QGSOptifineDownloadTask()
{
}
