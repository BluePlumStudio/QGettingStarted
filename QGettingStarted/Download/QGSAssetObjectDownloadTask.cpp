#include "QGSAssetObjectDownloadTask.h"

QGSAssetObjectDownloadTask::QGSAssetObjectDownloadTask(QFile * targetFile, const QGSDownloadInfo & downloadInfo, int threadCount, const QNetworkProxy & proxy, QObject * parent)
	:QGSDownloadTask(targetFile, downloadInfo, threadCount, proxy, parent)
{

}

QGSAssetObjectDownloadTask::~QGSAssetObjectDownloadTask()
{
	if (mTargetFilePtr)
	{
		mTargetFilePtr->deleteLater();
	}
	
}
