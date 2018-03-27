#include "QGSLibraryDownloadTask.h"

QGSLibraryDownloadTask::QGSLibraryDownloadTask(QFile * targetFile, const QGSDownloadInfo & downloadInfo, const QNetworkProxy & proxy, QObject * parent)
	:QGSDownloadTask(targetFile, downloadInfo, proxy, parent)
{

}

QGSLibraryDownloadTask::~QGSLibraryDownloadTask()
{
	if (mTargetFilePtr)
	{
		mTargetFilePtr->deleteLater();
	}
}
