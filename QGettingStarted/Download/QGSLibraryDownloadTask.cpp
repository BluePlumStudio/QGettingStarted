#include "QGSLibraryDownloadTask.h"

QGSLibraryDownloadTask::QGSLibraryDownloadTask(QFile * targetFile, const QGSDownloadInfo & downloadInfo, int threadCount, const QNetworkProxy & proxy, QObject * parent)
	:QGSDownloadTask(targetFile, downloadInfo, threadCount, proxy, parent)
{

}

QGSLibraryDownloadTask::~QGSLibraryDownloadTask()
{
	if (mTargetFilePtr)
	{
		mTargetFilePtr->deleteLater();
	}
}
