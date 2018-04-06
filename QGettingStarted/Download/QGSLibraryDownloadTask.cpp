#include "QGSLibraryDownloadTask.h"
#include "../Util/QGSExceptionInvalidValue.h"

QGSLibraryDownloadTask::QGSLibraryDownloadTask(const QGSLibrary & library, QGSIDownloadSource * downloadSource, QGSGameDirectory & gameDirectory, int connectionCount, const QNetworkProxy & proxy, QObject * parent)
	:QGSDownloadTask(connectionCount, proxy, parent)
{
	if (!downloadSource || library.getName().isEmpty() || library.getVersion().isEmpty() || library.getPackage().isEmpty())
	{
		throw QGSExceptionInvalidValue();
	}

	mDownloadInfo.setUrl(downloadSource->generateLibraryUrl(library));
	mTargetFilePtr = gameDirectory.generateLibraryFile(library);
}

QGSLibraryDownloadTask::~QGSLibraryDownloadTask()
{
	if (mTargetFilePtr)
	{
		mTargetFilePtr->deleteLater();
	}
}
