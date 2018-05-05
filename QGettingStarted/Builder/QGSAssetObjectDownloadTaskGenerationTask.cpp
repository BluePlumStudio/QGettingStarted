#include "QGSAssetObjectDownloadTaskGenerationTask.h"
#include "QGSGameVersionJsonDownloadTaskGenerationTask.h"
#include "../Util/QGSExceptionInvalidValue.h"
#include "../Util/QGSExceptionVersionNotFound.h"
#include "../Util/QGSExceptionJsonPraseError.h"
#include "../Util/QGSExceptionIO.h"

QGSAssetObjectDownloadTaskGenerationTask::QGSAssetObjectDownloadTaskGenerationTask(
	QGSAssetBuilder * assetBuilder,
	bool fileOverride,
	QObject * parent)

	:QGSDownloadTaskGenerationTask(parent), mFileOverride(fileOverride), mAssetBuilderPtr(assetBuilder)
{
	if (!assetBuilder)
	{
		throw QGSExceptionInvalidValue();
	}
}

QGSAssetObjectDownloadTaskGenerationTask::~QGSAssetObjectDownloadTaskGenerationTask()
{
}

void QGSAssetObjectDownloadTaskGenerationTask::templateStart(QGSTask * task)
{
	QGSAssetIndexJsonDownloadTaskGenerationTask::mMutex.lock();
	QGSAssetIndexJsonDownloadTaskGenerationTask::mAssetIndexJsonDownloadTaskEnded.wait(&QGSAssetIndexJsonDownloadTaskGenerationTask::mMutex);
	QGSAssetIndexJsonDownloadTaskGenerationTask::mMutex.unlock();

	emit started(this);

	QGSAssetIndexInfo assetIndexInfo;

	try
	{
		auto * assetIndexJsonFile(mAssetBuilderPtr->mGameDirectoryPtr->generateAssetIndexJsonFile(mAssetBuilderPtr->mVersionInfo));
		if (!assetIndexJsonFile->open(QIODevice::ReadOnly))
		{
			throw QGSExceptionIO(assetIndexJsonFile->fileName());
		}
		assetIndexInfo = QGSAssetIndexInfoFactory().createAssetIndexInfo(assetIndexJsonFile->readAll());
	}
	catch (const QGSExceptionJsonPraseError & exception)
	{
		emit error(this);

		return;
	}
	catch (const QGSExceptionIO & exception)
	{
		emit error(this);

		return;
	}

	auto && assetObjectMap(assetIndexInfo.getAssetObjectMap());
	QGSDownloadTask * downloadTask(nullptr);

	for (auto & i : assetObjectMap)
	{
		if (!mFileOverride)
		{
			QSharedPointer<QFile> assetObjectFile(mAssetBuilderPtr->mGameDirectoryPtr->generateAssetObjectFile(i));
			if (assetObjectFile->exists())
			{
				continue;
			}
		}

		downloadTask = mAssetBuilderPtr->mDownloadTaskFactoryPtr->generateAssetObjectDownloadTask(i, *(mAssetBuilderPtr->mGameDirectoryPtr));
		if (!downloadTask)
		{
			emit error(this);

			return;
		}
		mAssetBuilderPtr->mTaskList.push_back(downloadTask);

		QObject::connect(downloadTask, &QGSDownloadTask::started, mAssetBuilderPtr, &QGSAssetBuilder::slotDownloadTaskStarted);

		QObject::connect(downloadTask, &QGSDownloadTask::finished, mAssetBuilderPtr, &QGSAssetBuilder::slotDownloadTaskFinished);

		QObject::connect(downloadTask, &QGSDownloadTask::stoped, mAssetBuilderPtr, &QGSAssetBuilder::slotDownloadTaskStoped);

		QObject::connect(downloadTask, &QGSDownloadTask::canceled, mAssetBuilderPtr, &QGSAssetBuilder::slotDownloadTaskCanceled);

		QObject::connect(downloadTask, &QGSDownloadTask::downloadProgress, mAssetBuilderPtr, &QGSAssetBuilder::slotDownloadTaskDownloadProgress);

		QObject::connect(downloadTask, &QGSDownloadTask::downloadError, mAssetBuilderPtr, &QGSAssetBuilder::slotDownloadTaskDownloadError);

		QObject::connect(downloadTask, &QGSDownloadTask::error, mAssetBuilderPtr, &QGSAssetBuilder::slotDownloadTaskError);

		mAssetBuilderPtr->mThreadPoolManagerPtr->addTaskBack(downloadTask);
	}

	emit finished(this);
}

void QGSAssetObjectDownloadTaskGenerationTask::templateStop(QGSTask * task)
{
	emit stoped(this);
}

void QGSAssetObjectDownloadTaskGenerationTask::templateCancel(QGSTask * task)
{
	emit canceled(this);
}

