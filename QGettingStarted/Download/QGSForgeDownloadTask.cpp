#include "QGSForgeDownloadTask.h"

QGSForgeDownloadTask::QGSForgeDownloadTask(QFile * targetFile, const DownloadInfo & downloadInfo, const QNetworkProxy & proxy, QObject * parent)
	:QGSDownloadTask(targetFile, downloadInfo, proxy, parent)
{

}

QGSForgeDownloadTask::~QGSForgeDownloadTask()
{
}
