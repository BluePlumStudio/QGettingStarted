#include "QGSGameVersionBuilder.h"
#include "../Util/QGSExceptionJsonPraseError.h"
#include "../Util/QGSExceptionVersionNotFound.h"
#include "../Util/QGSExceptionIO.h"
#include "../Util/QGSExceptionInvalidValue.h"
#include "../Util/QGSExceptionGameDirectoryIsBuildingGame.h"
#include "QGSGameVersionJsonDownloadTaskGenerationTask.h"
#include "QGSGameVersionDownloadTaskGenerationTask.h"
/**/

QList<QGSGameDirectory *> QGSGameVersionBuilder::mDirectoriesBuilding;

QGSGameVersionBuilder::QGSGameVersionBuilder(
	QGSThreadPoolManager * threadPoolManagerPtr,
	QGSGameVersionInfo & versionInfo,
	QGSGameDirectory * gameDirectory,
	QGSDownloadTaskFactory * downloadTaskFactory,
	QObject * parent)

	:QGSIBuilder(threadPoolManagerPtr, gameDirectory, parent),
	mVersionInfo(versionInfo),
	mDownloadTaskFactoryPtr(downloadTaskFactory),
	mFileOverride(false)

{
	if (!mGameDirectoryPtr || !mDownloadTaskFactoryPtr)
	{
		throw QGSExceptionInvalidValue();
	}
}

QGSGameVersionBuilder::~QGSGameVersionBuilder()
{
	QMutexLocker mutexLocker(&mMutex);

	for (auto & task : mTaskList)
	{
		task->cancel();
	}

	for (auto & task : mTaskDeletedLaterList)
	{
		task->deleteLater();
	}
}

bool QGSGameVersionBuilder::isFileOverride()
{
	QMutexLocker mutexLocker(&mMutex);

	return mFileOverride;
}

QGSGameVersionBuilder & QGSGameVersionBuilder::setFileOverride(const bool fileOverride)
{
	QMutexLocker mutexLocker(&mMutex);

	mFileOverride = fileOverride;
	return *this;
}

int QGSGameVersionBuilder::getTaskListSize()
{
	QMutexLocker mutexLocker(&mMutex);

	return mTaskList.size();
}

void QGSGameVersionBuilder::templateStart(QGSTask * task)
{
	emit started(this);

	for (auto & directory : mDirectoriesBuilding)
	{
		if (mGameDirectoryPtr == directory)
		{
			throw QGSExceptionGameDirectoryIsBuildingGame(mGameDirectoryPtr);
		}
	}

	mDirectoriesBuilding.push_back(mGameDirectoryPtr);

	QMutexLocker mutexLocker(&mMutex);

	if (mTaskList.size())
	{
		for (auto & task : mTaskList)
		{
			task->start();
		}
	}
	else
	{
		initDownloadTasks();
	}
}

void QGSGameVersionBuilder::templateStop(QGSTask * task)
{
	emit stoped(this);

	QMutexLocker mutexLocker(&mMutex);

	for (auto & task : mTaskList)
	{
		task->stop();
	}
}

void QGSGameVersionBuilder::templateCancel(QGSTask * task)
{
	emit canceled(this);

	QMutexLocker mutexLocker(&mMutex);

	for (auto & task : mTaskList)
	{
		task->cancel();
	}
}

void QGSGameVersionBuilder::slotDownloadTaskStarted(QGSTask * task)
{
	emit downloadTaskStarted(dynamic_cast<QGSDownloadTask *>(task));
}

void QGSGameVersionBuilder::slotDownloadTaskFinished(QGSTask * task)
{
	slotEraseTask(task);

	emit downloadTaskFinished(dynamic_cast<QGSDownloadTask *>(task));

	slotFinished();
}

void QGSGameVersionBuilder::slotDownloadTaskStoped(QGSTask * task)
{
	emit downloadTaskStoped(dynamic_cast<QGSDownloadTask *>(task));
}

void QGSGameVersionBuilder::slotDownloadTaskCanceled(QGSTask * task)
{
	slotEraseTask(task);

	emit downloadTaskCanceled(dynamic_cast<QGSDownloadTask *>(task));

	//slotFinished();
}

void QGSGameVersionBuilder::slotDownloadTaskDownloadProgress(qint64 bytesReceived, qint64 bytesTotal, QGSTask * task)
{
	emit downloadTaskDownloadProgress(bytesReceived, bytesTotal, dynamic_cast<QGSDownloadTask *>(task));
}

void QGSGameVersionBuilder::slotDownloadTaskDownloadError(QGSNetworkError error, QGSTask * task)
{
	emit downloadTaskDownloadError(error, dynamic_cast<QGSDownloadTask *>(task));
}

void QGSGameVersionBuilder::slotDownloadTaskError(QGSTask * task)
{
	slotEraseTask(task);

	emit downloadTaskError(dynamic_cast<QGSDownloadTask *>(task));

	slotFinished();
}

void QGSGameVersionBuilder::slotEraseTask(QGSTask * task)
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

void QGSGameVersionBuilder::slotFinished()
{
	if (!mTaskList.size())
	{
		emit finished(this);
	}
}

void QGSGameVersionBuilder::initDownloadTasks()
{
	initGameVersionJsonDownloadTaskGenerationTask();
	initGameVersionDownloadTaskGenerationTask();

	//±ØÐëË³Ðò¶Ôµ÷
	mTaskList.push_back(mDownloadTaskGenerationTask);
	mTaskDeletedLaterList.push_back(mDownloadTaskGenerationTask);
	mThreadPoolManagerPtr->addTaskBack(mDownloadTaskGenerationTask);

	mTaskList.push_back(mJsonDownloadTaskGenerationTask);
	mTaskDeletedLaterList.push_back(mJsonDownloadTaskGenerationTask);
	mThreadPoolManagerPtr->addTaskBack(mJsonDownloadTaskGenerationTask);
}

QGSGameVersionJsonDownloadTaskGenerationTask * QGSGameVersionBuilder::initGameVersionJsonDownloadTaskGenerationTask()
{
	//auto * generationTask(new QGSGameVersionJsonDownloadTaskGenerationTask(this, mFileOverride));
	mJsonDownloadTaskGenerationTask = new QGSGameVersionJsonDownloadTaskGenerationTask(this, mFileOverride);

	QObject::connect(mJsonDownloadTaskGenerationTask, &QGSGameVersionJsonDownloadTaskGenerationTask::finished, this, &QGSGameVersionBuilder::slotEraseTask);
	QObject::connect(mJsonDownloadTaskGenerationTask, &QGSGameVersionJsonDownloadTaskGenerationTask::finished, this, &QGSGameVersionBuilder::slotFinished);

	QObject::connect(mJsonDownloadTaskGenerationTask, &QGSGameVersionJsonDownloadTaskGenerationTask::canceled, this, &QGSGameVersionBuilder::slotEraseTask);
	//QObject::connect(mJsonDownloadTaskGenerationTask, &QGSGameVersionJsonDownloadTaskGenerationTask::canceled, this, &QGSGameVersionBuilder::slotFinished);

	QObject::connect(mJsonDownloadTaskGenerationTask, &QGSGameVersionJsonDownloadTaskGenerationTask::error, this, &QGSGameVersionBuilder::slotEraseTask);
	QObject::connect(mJsonDownloadTaskGenerationTask, &QGSGameVersionJsonDownloadTaskGenerationTask::error, this, &QGSGameVersionBuilder::error);

	/*
	mTaskList.push_back(generationTask);
	mTaskDeletedLaterList.push_back(generationTask);
	mThreadPoolManagerPtr->addTaskBack(generationTask);
	*/

	return mJsonDownloadTaskGenerationTask;
}

QGSGameVersionDownloadTaskGenerationTask * QGSGameVersionBuilder::initGameVersionDownloadTaskGenerationTask()
{
	/*
	auto * generationTask(new QGSGameVersionDownloadTaskGenerationTask(this,
		jsonDownloadTaskGenerationTask->mSharedMutex,
		jsonDownloadTaskGenerationTask->mGameVersionJsonDownloadTaskEnded,
		mFileOverride));
	*/

	mDownloadTaskGenerationTask = new QGSGameVersionDownloadTaskGenerationTask(this,
		mJsonDownloadTaskGenerationTask->mSharedMutex,
		mJsonDownloadTaskGenerationTask->mGameVersionJsonDownloadTaskEnded,
		mFileOverride);

	QObject::connect(mDownloadTaskGenerationTask, &QGSGameVersionDownloadTaskGenerationTask::finished, this, &QGSGameVersionBuilder::slotEraseTask);
	QObject::connect(mDownloadTaskGenerationTask, &QGSGameVersionDownloadTaskGenerationTask::finished, this, &QGSGameVersionBuilder::slotFinished);

	QObject::connect(mDownloadTaskGenerationTask, &QGSGameVersionDownloadTaskGenerationTask::canceled, this, &QGSGameVersionBuilder::slotEraseTask);
	//QObject::connect(mDownloadTaskGenerationTask, &QGSGameVersionDownloadTaskGenerationTask::canceled, this, &QGSGameVersionBuilder::slotFinished);

	QObject::connect(mDownloadTaskGenerationTask, &QGSGameVersionDownloadTaskGenerationTask::error, this, &QGSGameVersionBuilder::slotEraseTask);
	QObject::connect(mDownloadTaskGenerationTask, &QGSGameVersionDownloadTaskGenerationTask::error, this, &QGSGameVersionBuilder::error);

	/*
	mTaskList.push_back(generationTask);
	mTaskDeletedLaterList.push_back(generationTask);
	mThreadPoolManagerPtr->addTaskBack(generationTask);
	*/

	return mDownloadTaskGenerationTask;
}
