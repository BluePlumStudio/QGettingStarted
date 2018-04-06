#include "QGSGameVersionDownloadTaskGenerationTask.h"
#include "QGSGameVersionJsonDownloadTaskGenerationTask.h"
#include "../Util/QGSExceptionInvalidValue.h"
#include "../Util/QGSExceptionVersionNotFound.h"

QGSGameVersionDownloadTaskGenerationTask::QGSGameVersionDownloadTaskGenerationTask(
	QGSGameVersionBuilder * gameVersionBuilder,
	bool fileOverride,
	QObject * parent)

	:QGSDownloadTaskGenerationTask(parent), mFileOverride(fileOverride), mGameVersionBuilderPtr(gameVersionBuilder)
{
	if (!gameVersionBuilder)
	{
		throw QGSExceptionInvalidValue();
	}
}

QGSGameVersionDownloadTaskGenerationTask::~QGSGameVersionDownloadTaskGenerationTask()
{
}

void QGSGameVersionDownloadTaskGenerationTask::templateStart(QGSTask * task)
{
	QGSGameVersionJsonDownloadTaskGenerationTask::mMutex.lock();
	QGSGameVersionJsonDownloadTaskGenerationTask::mGameVersionJsonDownloadTaskEnded.wait(&QGSGameVersionJsonDownloadTaskGenerationTask::mMutex);
	QGSGameVersionJsonDownloadTaskGenerationTask::mMutex.unlock();
	emit started(this);

	QGSDownloadTask * downloadTask(nullptr);

	if (!mFileOverride)
	{
		QSharedPointer<QFile> gameVersionJarFile(mGameVersionBuilderPtr->mGameDirectoryPtr->generateGameVersionJarFile(mGameVersionBuilderPtr->mVersionInfo));
		
		if (gameVersionJarFile->exists())
		{
			emit finished(this);

			return;
		}
	}

	QGSGameVersion gameVersion;
	try
	{
		gameVersion = mGameVersionBuilderPtr->mGameDirectoryPtr->getVersion(mGameVersionBuilderPtr->mVersionInfo);
	}
	catch (const QGSExceptionVersionNotFound & exception)
	{
		emit error(this);

		return;
	}
	downloadTask = mGameVersionBuilderPtr->mDownloadTaskFactoryPtr->generateGameVersionDownloadTask(gameVersion,
		*(mGameVersionBuilderPtr->mGameDirectoryPtr), 
		"client");
	if (!downloadTask)
	{
		emit error(this);

		return ;
	}
	mGameVersionBuilderPtr->mTaskList.push_back(downloadTask);

	QObject::connect(downloadTask, &QGSDownloadTask::started, mGameVersionBuilderPtr, &QGSGameVersionBuilder::slotDownloadTaskStarted);

	QObject::connect(downloadTask, &QGSDownloadTask::finished, mGameVersionBuilderPtr, &QGSGameVersionBuilder::slotDownloadTaskFinished);

	QObject::connect(downloadTask, &QGSDownloadTask::stoped, mGameVersionBuilderPtr, &QGSGameVersionBuilder::slotDownloadTaskStoped);

	QObject::connect(downloadTask, &QGSDownloadTask::canceled, mGameVersionBuilderPtr, &QGSGameVersionBuilder::slotDownloadTaskCanceled);

	QObject::connect(downloadTask, &QGSDownloadTask::downloadProgress, mGameVersionBuilderPtr, &QGSGameVersionBuilder::slotDownloadTaskDownloadProgress);
	
	QObject::connect(downloadTask, &QGSDownloadTask::downloadError, mGameVersionBuilderPtr, &QGSGameVersionBuilder::slotDownloadTaskDownloadError);

	QObject::connect(downloadTask, &QGSDownloadTask::error, mGameVersionBuilderPtr, &QGSGameVersionBuilder::slotDownloadTaskError);

	mGameVersionBuilderPtr->mThreadPool.addTaskBack(downloadTask);

	emit finished(this);
}

void QGSGameVersionDownloadTaskGenerationTask::templateStop(QGSTask * task)
{
	emit stoped(this);
}

void QGSGameVersionDownloadTaskGenerationTask::templateCancel(QGSTask * task)
{
	emit canceled(this);
}

