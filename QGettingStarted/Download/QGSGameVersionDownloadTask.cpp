#include "QGSGameVersionDownloadTask.h"
#include "../Util/QGSExceptionInvalidValue.h"

QGSGameVersionDownloadTask::QGSGameVersionDownloadTask(
	const QGSGameVersion & version, 
	const QString & category, 
	QGSIDownloadSource * downloadSource, 
	QGSGameDirectory & gameDirectory, 
	int connectionCount, 
	const QNetworkProxy & proxy, 
	QObject * parent)

	:QGSDownloadTask(connectionCount, proxy, parent)
{
	auto && versionDownloads(version.getDownloads());

	if (!downloadSource ||
		category.isEmpty() ||
		versionDownloads.isEmpty() ||
		!versionDownloads.contains(category) ||
		versionDownloads.value(category).getUrl().isEmpty())
	{
		throw QGSExceptionInvalidValue();
	}

	mDownloadInfo.setUrl(downloadSource->generateGameVersionUrl(version, category));
	mTargetFilePtr = gameDirectory.generateGameVersionJarFile(version.getId());
}

QGSGameVersionDownloadTask::~QGSGameVersionDownloadTask()
{
	if (mTargetFilePtr)
	{
		mTargetFilePtr->deleteLater();
	}
}
