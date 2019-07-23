#include "QGSGameVersionJsonDownloadTask.h"
#include "../Util/QGSExceptionInvalidValue.h"

QGSGameVersionJsonDownloadTask::QGSGameVersionJsonDownloadTask(
	const QGSGameVersionInfo & versionInfo, 
	QGSIDownloadSource * downloadSource, 
	QGSGameDirectory & gameDirectory, 
	int connectionCount, 
	const QNetworkProxy & proxy, 
	QObject * parent)

	:QGSDownloadTask(connectionCount, proxy, parent)
{
	if (!downloadSource || versionInfo.getUrl().isEmpty() || versionInfo.getId().isEmpty())
	{
		throw QGSExceptionInvalidValue();
	}

	mDownloadInfo.setUrl(downloadSource->generateGameVersionJsonUrl(versionInfo));
	mTargetFilePtr = gameDirectory.generateGameVersionJsonFile(versionInfo.getId());
}

QGSGameVersionJsonDownloadTask::~QGSGameVersionJsonDownloadTask()
{
	if (mTargetFilePtr)
	{
		mTargetFilePtr->deleteLater();
		mTargetFilePtr = nullptr;
	}
}
