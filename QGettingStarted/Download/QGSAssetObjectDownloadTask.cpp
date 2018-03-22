#include "QGSAssetObjectDownloadTask.h"

QGSAssetObjectDownloadTask::QGSAssetObjectDownloadTask(QFile * targetFile, const DownloadInfo & downloadInfo, const QNetworkProxy & proxy, QObject * parent)
	:QGSDownloadTask(targetFile, downloadInfo, proxy, parent)
{

}

QGSAssetObjectDownloadTask::~QGSAssetObjectDownloadTask()
{
	if (mTargetFilePtr)
	{
		mTargetFilePtr->deleteLater();
	}
}
