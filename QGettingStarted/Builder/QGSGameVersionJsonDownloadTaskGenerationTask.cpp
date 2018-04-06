#include "QGSGameVersionJsonDownloadTaskGenerationTask.h"
#include "../Util/QGSExceptionInvalidValue.h"

QMutex QGSGameVersionJsonDownloadTaskGenerationTask::mMutex;
QWaitCondition QGSGameVersionJsonDownloadTaskGenerationTask::mGameVersionJsonDownloadTaskEnded;

QGSGameVersionJsonDownloadTaskGenerationTask::QGSGameVersionJsonDownloadTaskGenerationTask(
	QGSGameVersionBuilder * gameVersionBuilder,
	QObject * parent)

	:QGSDownloadTaskGenerationTask(parent), mGameVersionBuilderPtr(gameVersionBuilder)
{
	if (!mGameVersionBuilderPtr)
	{
		throw QGSExceptionInvalidValue();
	}
}

QGSGameVersionJsonDownloadTaskGenerationTask::~QGSGameVersionJsonDownloadTaskGenerationTask()
{
}

void QGSGameVersionJsonDownloadTaskGenerationTask::templateStart(QGSTask * task)
{
	emit started(this);

	QGSDownloadTask * downloadTask(nullptr);

	downloadTask = mGameVersionBuilderPtr->mDownloadTaskFactoryPtr->generateGameVersionJsonDownloadTask(mGameVersionBuilderPtr->mVersionInfo,
		*(mGameVersionBuilderPtr->mGameDirectoryPtr));
	if (!downloadTask)
	{
		emit error(this);

		return;
	}
	mGameVersionBuilderPtr->mTaskList.push_back(downloadTask);

	QObject::connect(downloadTask, &QGSDownloadTask::started, mGameVersionBuilderPtr, &QGSGameVersionBuilder::slotDownloadTaskStarted);

	QObject::connect(downloadTask, &QGSDownloadTask::finished, this, &QGSGameVersionJsonDownloadTaskGenerationTask::wakeGameVersionJsonDownloadTaskEnded, Qt::ConnectionType::DirectConnection);
	QObject::connect(downloadTask, &QGSDownloadTask::finished, mGameVersionBuilderPtr, &QGSGameVersionBuilder::slotDownloadTaskFinished);

	QObject::connect(downloadTask, &QGSDownloadTask::stoped, mGameVersionBuilderPtr, &QGSGameVersionBuilder::slotDownloadTaskStoped);

	QObject::connect(downloadTask, &QGSDownloadTask::canceled, this, &QGSGameVersionJsonDownloadTaskGenerationTask::wakeGameVersionJsonDownloadTaskEnded, Qt::ConnectionType::DirectConnection);
	QObject::connect(downloadTask, &QGSDownloadTask::canceled, mGameVersionBuilderPtr, &QGSGameVersionBuilder::slotDownloadTaskCanceled);

	QObject::connect(downloadTask, &QGSDownloadTask::downloadProgress, mGameVersionBuilderPtr, &QGSGameVersionBuilder::slotDownloadTaskDownloadProgress);

	QObject::connect(downloadTask, &QGSDownloadTask::downloadError, mGameVersionBuilderPtr, &QGSGameVersionBuilder::slotDownloadTaskDownloadError);

	QObject::connect(downloadTask, &QGSDownloadTask::error, this, &QGSGameVersionJsonDownloadTaskGenerationTask::wakeGameVersionJsonDownloadTaskEnded, Qt::ConnectionType::DirectConnection);
	QObject::connect(downloadTask, &QGSDownloadTask::error, mGameVersionBuilderPtr, &QGSGameVersionBuilder::slotDownloadTaskError);

	mGameVersionBuilderPtr->mThreadPool.addTaskBack(downloadTask);

	emit finished(this);
}

void QGSGameVersionJsonDownloadTaskGenerationTask::templateStop(QGSTask * task)
{
	emit stoped(this);
}

void QGSGameVersionJsonDownloadTaskGenerationTask::templateCancel(QGSTask * task)
{
	emit canceled(this);
}

void QGSGameVersionJsonDownloadTaskGenerationTask::wakeGameVersionJsonDownloadTaskEnded()
{
	mGameVersionJsonDownloadTaskEnded.wakeAll();
}
