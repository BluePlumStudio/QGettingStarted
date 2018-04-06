#include "QGSForgeDownloadTask.h"
#include "../Util/QGSExceptionInvalidValue.h"

QGSForgeDownloadTask::QGSForgeDownloadTask(
	QFile * targetFile,
	QGSIDownloadSource * downloadSource,
	const QString & mcversion,
	const QString & version,
	const QString & category,
	const QString & format,
	const QString & branch,
	int connectionCount,
	const QNetworkProxy & proxy,
	QObject *parent)

	:QGSDownloadTask(connectionCount, proxy, parent)
{
	if (!downloadSource || !targetFile || mcversion.isEmpty() || version.isEmpty() || category.isEmpty() || format.isEmpty())
	{
		throw QGSExceptionInvalidValue();
	}

	mDownloadInfo.setUrl(downloadSource->generateForgeUrl(mcversion, version, category, format, branch));
	mTargetFilePtr = targetFile;
}

QGSForgeDownloadTask::~QGSForgeDownloadTask()
{
}
