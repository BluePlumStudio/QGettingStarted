#include "QGSAssetIndexJsonDownloadTask.h"

QGSAssetIndexJsonDownloadTask::QGSAssetIndexJsonDownloadTask(QFile * targetFile, const QGSDownloadInfo & downloadInfo, const QNetworkProxy & proxy, QObject * parent)
	:QGSDownloadTask(targetFile, downloadInfo, proxy, parent)
{

}

QGSAssetIndexJsonDownloadTask::~QGSAssetIndexJsonDownloadTask()
{
	if (mTargetFilePtr)
	{
		mTargetFilePtr->deleteLater();
	}
}
