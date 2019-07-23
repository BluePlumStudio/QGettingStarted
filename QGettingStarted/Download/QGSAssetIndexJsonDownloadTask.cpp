#include "QGSAssetIndexJsonDownloadTask.h"
#include "../Util/QGSExceptionInvalidValue.h"

QGSAssetIndexJsonDownloadTask::QGSAssetIndexJsonDownloadTask(const QGSAssetIndex & assetIndex, QGSIDownloadSource * downloadSource, QGSGameDirectory & gameDirectory, int connectionCount, const QNetworkProxy & proxy, QObject * parent)
	:QGSDownloadTask(connectionCount, proxy, parent)
{
	if (!downloadSource || assetIndex.getUrl().isEmpty())
	{
		throw QGSExceptionInvalidValue();
	}

	mDownloadInfo.setUrl(downloadSource->generateAssetIndexJsonUrl(assetIndex));
	mTargetFilePtr = gameDirectory.generateAssetIndexJsonFile(assetIndex);
}

QGSAssetIndexJsonDownloadTask::~QGSAssetIndexJsonDownloadTask()
{
	if (mTargetFilePtr)
	{
		mTargetFilePtr->deleteLater();
		mTargetFilePtr = nullptr;
	}
}
