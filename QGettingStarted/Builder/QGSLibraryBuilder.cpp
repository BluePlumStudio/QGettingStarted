#include "QGSLibraryBuilder.h"
#include "../Util/QGSExceptionJsonPraseError.h"
#include "../Util/QGSExceptionVersionNotFound.h"
#include "../Util/QGSExceptionIO.h"
#include "../Util/QGSExceptionInvalidValue.h"
#include "QGSGameVersionJsonDownloadTaskGenerationTask.h"
#include "QGSGameVersionDownloadTaskGenerationTask.h"
/**/

QGSLibraryBuilder::QGSLibraryBuilder(QGSGameVersionInfo & versionInfo, QGSGameDirectory * gameDirectory, QGSDownloadTaskFactory * downloadTaskFactory, QObject * parent)
	:QGSIBuilder(parent),
	mVersionInfo(versionInfo),
	mGameDirectoryPtr(gameDirectory),
	mDownloadTaskFactoryPtr(downloadTaskFactory),
	mFileOverride(false)

{
	if (!mGameDirectoryPtr || !mDownloadTaskFactoryPtr)
	{
		throw QGSExceptionInvalidValue();
	}

}

QGSLibraryBuilder::~QGSLibraryBuilder()
{
	for (auto & task : mTaskList)
	{
		task->cancel();
		task->deleteLater();
	}

}

bool QGSLibraryBuilder::isFileOverride()
{
	QMutexLocker mutexLocker(&mMutex);

	return mFileOverride;
}

QGSLibraryBuilder & QGSLibraryBuilder::setFileOverride(const bool fileOverride)
{
	QMutexLocker mutexLocker(&mMutex);

	mFileOverride = fileOverride;
	return *this;
}

int QGSLibraryBuilder::getTaskListSize()
{
	QMutexLocker mutexLocker(&mMutex);

	return mTaskList.size();
}

void QGSLibraryBuilder::templateStart(QGSTask * task)
{
	emit started(this);

	QMutexLocker mutexLocker(&mMutex);

	if (mTaskList.size())
	{
		for (auto & task : mTaskList)
		{
			QMetaObject::invokeMethod(task, "start", Qt::ConnectionType::QueuedConnection);
		}
	}
	else
	{
		initDownloadTasks();
	}
}

void QGSLibraryBuilder::templateStop(QGSTask * task)
{
	emit stoped(this);

	QMutexLocker mutexLocker(&mMutex);

	for (auto & task : mTaskList)
	{
		QMetaObject::invokeMethod(task, "stop", Qt::ConnectionType::DirectConnection);
	}
}

void QGSLibraryBuilder::templateCancel(QGSTask * task)
{
	emit canceled(this);

	QMutexLocker mutexLocker(&mMutex);

	for (auto & task : mTaskList)
	{
		QMetaObject::invokeMethod(task, "cancel", Qt::ConnectionType::DirectConnection);
	}
}

void QGSLibraryBuilder::slotDownloadTaskStarted(QGSTask * task)
{
	emit downloadTaskStarted(dynamic_cast<QGSDownloadTask *>(task));
}

void QGSLibraryBuilder::slotDownloadTaskFinished(QGSTask * task)
{
	slotEraseTask(task);

	emit downloadTaskFinished(dynamic_cast<QGSDownloadTask *>(task));

	slotFinished();
}

void QGSLibraryBuilder::slotDownloadTaskStoped(QGSTask * task)
{
	emit downloadTaskStoped(dynamic_cast<QGSDownloadTask *>(task));
}

void QGSLibraryBuilder::slotDownloadTaskCanceled(QGSTask * task)
{
	slotEraseTask(task);

	emit downloadTaskCanceled(dynamic_cast<QGSDownloadTask *>(task));

	slotFinished();
}

void QGSLibraryBuilder::slotDownloadTaskDownloadProgress(qint64 bytesReceived, qint64 bytesTotal, QGSTask * task)
{
	emit downloadTaskDownloadProgress(bytesReceived, bytesTotal, dynamic_cast<QGSDownloadTask *>(task));
}

void QGSLibraryBuilder::slotDownloadTaskDownloadError(QGSNetworkError error, QGSTask * task)
{
	emit downloadTaskDownloadError(error, dynamic_cast<QGSDownloadTask *>(task));
}

void QGSLibraryBuilder::slotDownloadTaskError(QGSTask * task)
{
	slotEraseTask(task);

	emit downloadTaskError(dynamic_cast<QGSDownloadTask *>(task));

	slotFinished();
}

void QGSLibraryBuilder::slotEraseTask(QGSTask * task)
{
	if (!task)
	{
		return;
	}

	QMutexLocker mutexLocker(&mMutex);

	for (auto it = mTaskList.begin(); it != mTaskList.end(); it++)
	{
		if (*it == task)
		{
			mTaskList.erase(it);
			break;
		}
	}
}

void QGSLibraryBuilder::slotFinished()
{
	if (!mTaskList.size())
	{
		emit finished(this);
	}
}

void QGSLibraryBuilder::initDownloadTasks()
{
	if (!initLibraryDownloadTasks())
	{
		slotFinished();
	}
}

bool QGSLibraryBuilder::initLibraryDownloadTasks()
{
	bool ret(false);
	QList<QGSLibrary> libraryList;

	try
	{
		libraryList = mGameDirectoryPtr->getVersion(mVersionInfo).getLibraries();
	}
	catch (const QGSExceptionVersionNotFound & exception)
	{
		emit error(this);
		mLastErrorString = "Game version:" + mVersionInfo.getId() + "not found!";

		return ret;
	}

	QGSDownloadTask * downloadTask(nullptr);

	for (auto & i : libraryList)
	{
		if (!mFileOverride)
		{
			QSharedPointer<QFile> libraryFile(mGameDirectoryPtr->generateLibraryFile(i));
			if (libraryFile->exists())
			{
				continue;
			}
		}

		downloadTask = mDownloadTaskFactoryPtr->generateLibraryDownloadTask(i, *mGameDirectoryPtr);
		if (!downloadTask)
		{
			emit error(this);
			mLastErrorString = "Failed to generate library download task!";

			continue;
		}

		QObject::connect(downloadTask, &QGSDownloadTask::started, this, &QGSLibraryBuilder::slotDownloadTaskStarted);

		QObject::connect(downloadTask, &QGSDownloadTask::finished, this, &QGSLibraryBuilder::slotDownloadTaskFinished);

		QObject::connect(downloadTask, &QGSDownloadTask::stoped, this, &QGSLibraryBuilder::slotDownloadTaskStoped);

		QObject::connect(downloadTask, &QGSDownloadTask::canceled, this, &QGSLibraryBuilder::slotDownloadTaskCanceled);

		QObject::connect(downloadTask, &QGSDownloadTask::downloadProgress, this, &QGSLibraryBuilder::slotDownloadTaskDownloadProgress);

		QObject::connect(downloadTask, &QGSDownloadTask::downloadError, this, &QGSLibraryBuilder::slotDownloadTaskDownloadError);

		QObject::connect(downloadTask, &QGSDownloadTask::error, this, &QGSLibraryBuilder::slotDownloadTaskError);

		ret = true;

		mTaskList.push_back(downloadTask);
		mThreadPool.addTaskBack(downloadTask);
	}

	return ret;
}