#include "QGSAssetObjectDownloadTaskGenerationTask.h"
#include "QGSGameVersionJsonDownloadTaskGenerationTask.h"
#include "../Util/QGSExceptionInvalidValue.h"
#include "../Util/QGSExceptionVersionNotFound.h"
#include "../Util/QGSExceptionJsonPraseError.h"
#include "../Util/QGSExceptionIO.h"

QGSAssetObjectDownloadTaskGenerationTask::QGSAssetObjectDownloadTaskGenerationTask(
	QGSAssetBuilder * assetBuilder,
	QSharedPointer<QMutex> sharedMutex,
	QSharedPointer<QWaitCondition> jsonDownloadTaskEnded,
	bool fileOverride,
	QObject * parent)

	:QGSDownloadTaskGenerationTask(parent), 
	mSharedMutex(sharedMutex),
	mAssetIndexJsonDownloadTaskEnded(jsonDownloadTaskEnded),
	mFileOverride(fileOverride), 
	mAssetBuilderPtr(assetBuilder)
{
	if (!assetBuilder || mSharedMutex.isNull() || mAssetIndexJsonDownloadTaskEnded.isNull())
	{
		throw QGSExceptionInvalidValue();
	}
}

QGSAssetObjectDownloadTaskGenerationTask::~QGSAssetObjectDownloadTaskGenerationTask()
{
}

void QGSAssetObjectDownloadTaskGenerationTask::templateStart(QGSTask * task)
{
	mSharedMutex->lock();
	mAssetIndexJsonDownloadTaskEnded->wait(mSharedMutex.data());
	mSharedMutex->unlock();

	emit started(this);

	try
	{
		auto * assetIndexJsonFile(mAssetBuilderPtr->mGameDirectoryPtr->generateAssetIndexJsonFile(mAssetBuilderPtr->mVersionInfo));
		if (!assetIndexJsonFile->open(QIODevice::ReadOnly))
		{
			throw QGSExceptionIO(assetIndexJsonFile->fileName());
		}
		mAssetBuilderPtr->mAssetIndexInfo = QGSAssetIndexInfoFactory().createAssetIndexInfo(assetIndexJsonFile->readAll());
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

	auto && assetObjectMap(mAssetBuilderPtr->mAssetIndexInfo.getAssetObjectMap());
	QGSDownloadTask * downloadTask(nullptr);

	for (auto & i : assetObjectMap)
	{
		if (!mFileOverride)
		{
			QString assetObjectFileName(mAssetBuilderPtr->mGameDirectoryPtr->generateAssetObjectFileName(i));

			if (QFileInfo::exists(assetObjectFileName) || QFileInfo::exists(assetObjectFileName + ".qtmp"))
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

