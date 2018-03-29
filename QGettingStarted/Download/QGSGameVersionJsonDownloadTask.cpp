#include "QGSGameVersionJsonDownloadTask.h"

QGSGameVersionJsonDownloadTask::QGSGameVersionJsonDownloadTask(QFile * targetFile, const QGSDownloadInfo & downloadInfo, int threadCount, const QNetworkProxy & proxy, QObject * parent)
	:QGSDownloadTask(targetFile, downloadInfo, threadCount, proxy, parent)
{

}

QGSGameVersionJsonDownloadTask::~QGSGameVersionJsonDownloadTask()
{
	if (mTargetFilePtr)
	{
		mTargetFilePtr->deleteLater();
	}
}
