#include "QGSAssetIndexJsonDownloadTask.h"

QGSAssetIndexJsonDownloadTask::QGSAssetIndexJsonDownloadTask(QFile * targetFile, const QGSDownloadInfo & downloadInfo, int threadCount, const QNetworkProxy & proxy, QObject * parent)
	:QGSDownloadTask(targetFile, downloadInfo, threadCount, proxy, parent)
{

}

QGSAssetIndexJsonDownloadTask::~QGSAssetIndexJsonDownloadTask()
{
	if (mTargetFilePtr)
	{
		mTargetFilePtr->deleteLater();
	}
}
