#include "QGSAssetObjectDownloadTask.h"
#include "../Util/QGSExceptionInvalidValue.h"

QGSAssetObjectDownloadTask::QGSAssetObjectDownloadTask(
	const QGSAssetObject & assetObject, 
	QGSIDownloadSource * downloadSource, 
	QGSGameDirectory & gameDirectory, 
	int connectionCount, 
	const QNetworkProxy & proxy, QObject * parent)

	:QGSDownloadTask(connectionCount, proxy, parent)
{
	if (!downloadSource || assetObject.getHash().isEmpty())
	{
		throw QGSExceptionInvalidValue();
	}

	mDownloadInfo.setUrl(downloadSource->generateAssetObjectUrl(assetObject));
	mTargetFilePtr = gameDirectory.generateAssetObjectFile(assetObject);
}

QGSAssetObjectDownloadTask::~QGSAssetObjectDownloadTask()
{
	if (mTargetFilePtr)
	{
		mTargetFilePtr->deleteLater();
	}
	
}
