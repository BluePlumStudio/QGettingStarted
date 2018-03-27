#include "QGSForgeDownloadTask.h"

QGSForgeDownloadTask::QGSForgeDownloadTask(QFile * targetFile, const QGSDownloadInfo & downloadInfo, const QNetworkProxy & proxy, QObject * parent)
	:QGSDownloadTask(targetFile, downloadInfo, proxy, parent)
{

}

QGSForgeDownloadTask::~QGSForgeDownloadTask()
{
}
