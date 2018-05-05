#include "QGSAssetIndexJsonDownloadTaskGenerationTask.h"
#include "QGSGameVersionJsonDownloadTaskGenerationTask.h"
#include "../Util/QGSExceptionInvalidValue.h"
#include "../Util/QGSExceptionVersionNotFound.h"

QMutex QGSAssetIndexJsonDownloadTaskGenerationTask::mMutex;
QWaitCondition QGSAssetIndexJsonDownloadTaskGenerationTask::mAssetIndexJsonDownloadTaskEnded;

QGSAssetIndexJsonDownloadTaskGenerationTask::QGSAssetIndexJsonDownloadTaskGenerationTask(
	QGSAssetBuilder * assetBuilder,
	bool fileOverride,
	QObject * parent)

	:QGSDownloadTaskGenerationTask(parent), mFileOverride(fileOverride), mAssetBuilderPtr(assetBuilder)
{
	if (!mAssetBuilderPtr)
	{
		throw QGSExceptionInvalidValue();
	}
}

QGSAssetIndexJsonDownloadTaskGenerationTask::~QGSAssetIndexJsonDownloadTaskGenerationTask()
{
}

void QGSAssetIndexJsonDownloadTaskGenerationTask::templateStart(QGSTask * task)
{
	emit started(this);

	QGSDownloadTask * downloadTask(nullptr);

	QGSGameVersion gameVersion;
	try
	{
		gameVersion = mAssetBuilderPtr->mGameDirectoryPtr->getVersion(mAssetBuilderPtr->mVersionInfo);

	}
	catch (const QGSExceptionVersionNotFound & exception)
	{
		emit error(this);

		wakeAssetIndexJsonDownloadTaskEnded();

		return;
	}

	if (!mAssetBuilderPtr->mFileOverride)
	{
		QSharedPointer<QFile> mAssetIndexJsonFile(mAssetBuilderPtr->mGameDirectoryPtr->generateAssetIndexJsonFile(gameVersion.getAssetIndex()));

		if (mAssetIndexJsonFile->exists())
		{
			emit finished(this);

			wakeAssetIndexJsonDownloadTaskEnded();

			return;
		}
	}

	downloadTask = mAssetBuilderPtr->mDownloadTaskFactoryPtr->generateAssetIndexJsonDownloadTask(
		gameVersion.getAssetIndex(),
		*(mAssetBuilderPtr->mGameDirectoryPtr));

	if (!downloadTask)
	{
		emit error(this);

		wakeAssetIndexJsonDownloadTaskEnded();

		return ;
	}
	mAssetBuilderPtr->mTaskList.push_back(downloadTask);

	QObject::connect(downloadTask, &QGSDownloadTask::started, mAssetBuilderPtr, &QGSAssetBuilder::slotDownloadTaskStarted);

	QObject::connect(downloadTask, &QGSDownloadTask::finished, this, &QGSAssetIndexJsonDownloadTaskGenerationTask::wakeAssetIndexJsonDownloadTaskEnded, Qt::ConnectionType::DirectConnection);
	QObject::connect(downloadTask, &QGSDownloadTask::finished, mAssetBuilderPtr, &QGSAssetBuilder::slotDownloadTaskFinished);

	QObject::connect(downloadTask, &QGSDownloadTask::stoped, mAssetBuilderPtr, &QGSAssetBuilder::slotDownloadTaskStoped);

	QObject::connect(downloadTask, &QGSDownloadTask::canceled, this, &QGSAssetIndexJsonDownloadTaskGenerationTask::wakeAssetIndexJsonDownloadTaskEnded, Qt::ConnectionType::DirectConnection);
	QObject::connect(downloadTask, &QGSDownloadTask::canceled, mAssetBuilderPtr, &QGSAssetBuilder::slotDownloadTaskCanceled);

	QObject::connect(downloadTask, &QGSDownloadTask::downloadProgress, mAssetBuilderPtr, &QGSAssetBuilder::slotDownloadTaskDownloadProgress);

	QObject::connect(downloadTask, &QGSDownloadTask::downloadError, mAssetBuilderPtr, &QGSAssetBuilder::slotDownloadTaskDownloadError);

	QObject::connect(downloadTask, &QGSDownloadTask::error, this, &QGSAssetIndexJsonDownloadTaskGenerationTask::wakeAssetIndexJsonDownloadTaskEnded, Qt::ConnectionType::DirectConnection);
	QObject::connect(downloadTask, &QGSDownloadTask::error, mAssetBuilderPtr, &QGSAssetBuilder::slotDownloadTaskError);

	mAssetBuilderPtr->mThreadPoolManagerPtr->addTaskBack(downloadTask);

	emit finished(this);
}

void QGSAssetIndexJsonDownloadTaskGenerationTask::templateStop(QGSTask * task)
{
	emit stoped(this);
}

void QGSAssetIndexJsonDownloadTaskGenerationTask::templateCancel(QGSTask * task)
{
	emit canceled(this);
}

void QGSAssetIndexJsonDownloadTaskGenerationTask::wakeAssetIndexJsonDownloadTaskEnded()
{
	mAssetIndexJsonDownloadTaskEnded.wakeAll();
}

