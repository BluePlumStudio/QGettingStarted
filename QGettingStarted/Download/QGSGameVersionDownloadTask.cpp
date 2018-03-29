#include "QGSGameVersionDownloadTask.h"

QGSGameVersionDownloadTask::QGSGameVersionDownloadTask(QFile * targetFile, const QGSDownloadInfo & downloadInfo, int threadCount, const QNetworkProxy & proxy, QObject * parent)
	:QGSDownloadTask(targetFile, downloadInfo, threadCount, proxy, parent)
{

}

QGSGameVersionDownloadTask::~QGSGameVersionDownloadTask()
{
	if (mTargetFilePtr)
	{
		mTargetFilePtr->deleteLater();
	}
}
