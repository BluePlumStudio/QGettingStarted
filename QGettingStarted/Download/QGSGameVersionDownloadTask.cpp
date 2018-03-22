#include "QGSGameVersionDownloadTask.h"

QGSGameVersionDownloadTask::QGSGameVersionDownloadTask(QFile * targetFile, const DownloadInfo & downloadInfo, const QNetworkProxy & proxy, QObject * parent)
	:QGSDownloadTask(targetFile, downloadInfo, proxy, parent)
{

}

QGSGameVersionDownloadTask::~QGSGameVersionDownloadTask()
{
	if (mTargetFilePtr)
	{
		mTargetFilePtr->deleteLater();
	}
}
