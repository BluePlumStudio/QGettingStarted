#include <QCoreApplication>

#include "QGSGameBuilder.h"
#include "../Util/QGSExceptionJsonPraseError.h"
#include "../Util/QGSExceptionVersionNotFound.h"
#include "../Util/QGSExceptionIO.h"
#include "../Util/QGSExceptionInvalidValue.h"

/*
GameVersionJsonDownloadTaskGenerationTask::GameVersionJsonDownloadTaskGenerationTask(QGSGameBuilder * gameBuilder)
	:mGameBuilderPtr(gameBuilder)
{
	if (!mGameBuilderPtr)
	{
		throw QGSExceptionInvalidValue();
	}
}

GameVersionJsonDownloadTaskGenerationTask::~GameVersionJsonDownloadTaskGenerationTask()
{

}

void GameVersionJsonDownloadTaskGenerationTask::templateStart(QGSTask * task)
{
	QMutexLocker mutexLocker(&mGameBuilderPtr->mMutex);

	QGSDownloadTask * downloadTask(nullptr);

	downloadTask = mGameBuilderPtr->mDownloadTaskFactoryPtr->generateGameVersionJsonDownloadTask(
		mGameBuilderPtr->mVersionInfo, *(mGameBuilderPtr->mGameDirectoryPtr));
	if (!downloadTask)
	{
		QObject::connect(this, &GameVersionJsonDownloadTaskGenerationTask::error, mGameBuilderPtr, &QGSGameBuilder::error);
		QObject::connect(this, &GameVersionJsonDownloadTaskGenerationTask::generationTaskDownloadError, mGameBuilderPtr, &QGSGameBuilder::downloadTaskDownloadError);
		mGameBuilderPtr->mLastErrorString = "Generating game version json download task failed!";

		mutexLocker.unlock();
		emit error(this);
		emit generationTaskDownloadError(QGSNetworkError(QNetworkReply::NetworkError::NoError, "Generating game version json download task failed!"),
			downloadTask);

		return;
	}
	downloadTask->setTaskQueueBlock(true);
	mGameBuilderPtr->mTaskList.push_front(downloadTask);
	QObject::connect(downloadTask, &QGSDownloadTask::started, mGameBuilderPtr, &QGSGameBuilder::downloadTaskStarted);
	QObject::connect(downloadTask, &QGSDownloadTask::finished, mGameBuilderPtr, &QGSGameBuilder::downloadTaskFinished);
	QObject::connect(downloadTask, &QGSDownloadTask::stoped, mGameBuilderPtr, &QGSGameBuilder::downloadTaskStoped);
	QObject::connect(downloadTask, &QGSDownloadTask::canceled, mGameBuilderPtr, &QGSGameBuilder::downloadTaskCanceled);
	QObject::connect(downloadTask, &QGSDownloadTask::downloadError, mGameBuilderPtr, &QGSGameBuilder::downloadTaskDownloadError);
	QObject::connect(downloadTask, &QGSDownloadTask::error, mGameBuilderPtr, &QGSGameBuilder::downloadTaskError);
	QObject::connect(downloadTask, &QGSDownloadTask::finished, mGameBuilderPtr, &QGSGameBuilder::slotEraseDownloadTask);
	QObject::connect(downloadTask, &QGSDownloadTask::finished, mGameBuilderPtr, &QGSGameBuilder::slotDownloadTaskFinished);
	QGSThreadPool::getGlobalInstance().addTaskFront(downloadTask);

	emit finished(this);
}

GameVersionDownloadTaskGenerationTask::GameVersionDownloadTaskGenerationTask(QGSGameBuilder * gameBuilder)
	:mGameBuilderPtr(gameBuilder)
{
	if (!mGameBuilderPtr)
	{
		throw QGSExceptionInvalidValue();
	}
}

GameVersionDownloadTaskGenerationTask::~GameVersionDownloadTaskGenerationTask()
{
}

void GameVersionDownloadTaskGenerationTask::templateStart(QGSTask * task)
{
	QMutexLocker mutexLocker(&mGameBuilderPtr->mMutex);

	if (!mGameBuilderPtr->mFileOverride)
	{
		QSharedPointer<QFile> gameVersionJarFile(mGameBuilderPtr->mGameDirectoryPtr->generateGameVersionJarFile(mGameBuilderPtr->mVersionInfo.getId()));
		if (gameVersionJarFile->exists())
		{
			mutexLocker.unlock();
			emit finished(this);
			return;
		}
	}

	QGSDownloadTask * downloadTask(nullptr);

	auto & version(mGameBuilderPtr->mGameDirectoryPtr->getVersion(mGameBuilderPtr->mVersionInfo));
	downloadTask = mGameBuilderPtr->mDownloadTaskFactoryPtr->generateGameVersionDownloadTask(version, *(mGameBuilderPtr->mGameDirectoryPtr), "client");
	if (!downloadTask)
	{
		QObject::connect(this, &GameVersionJsonDownloadTaskGenerationTask::error, mGameBuilderPtr, &QGSGameBuilder::error);
		QObject::connect(this, &GameVersionJsonDownloadTaskGenerationTask::generationTaskDownloadError, mGameBuilderPtr, &QGSGameBuilder::downloadTaskDownloadError);
		mGameBuilderPtr->mLastErrorString = "Generating game version download task failed!";

		mutexLocker.unlock();

		emit error(this);
		emit generationTaskDownloadError(QGSNetworkError(QNetworkReply::NetworkError::NoError, "Generating game version download task failed!"),
			downloadTask);

		return;
	}
	mGameBuilderPtr->mTaskList.push_back(downloadTask);
	QObject::connect(downloadTask, &QGSDownloadTask::started, mGameBuilderPtr, &QGSGameBuilder::downloadTaskStarted);
	QObject::connect(downloadTask, &QGSDownloadTask::finished, mGameBuilderPtr, &QGSGameBuilder::downloadTaskFinished);
	QObject::connect(downloadTask, &QGSDownloadTask::stoped, mGameBuilderPtr, &QGSGameBuilder::downloadTaskStoped);
	QObject::connect(downloadTask, &QGSDownloadTask::canceled, mGameBuilderPtr, &QGSGameBuilder::downloadTaskCanceled);
	QObject::connect(downloadTask, &QGSDownloadTask::downloadError, mGameBuilderPtr, &QGSGameBuilder::downloadTaskDownloadError);
	QObject::connect(downloadTask, &QGSDownloadTask::error, mGameBuilderPtr, &QGSGameBuilder::downloadTaskError);
	QObject::connect(downloadTask, &QGSDownloadTask::finished, mGameBuilderPtr, &QGSGameBuilder::slotEraseDownloadTask);
	QObject::connect(downloadTask, &QGSDownloadTask::finished, mGameBuilderPtr, &QGSGameBuilder::slotDownloadTaskFinished);
	QGSThreadPool::getGlobalInstance().addTaskBack(downloadTask);

	emit finished(this);
}

LibraryDownloadTasksGenerationTask::LibraryDownloadTasksGenerationTask(QGSGameBuilder * gameBuilder)
	:mGameBuilderPtr(gameBuilder)
{
	if (!mGameBuilderPtr)
	{
		throw QGSExceptionInvalidValue();
	}
}

LibraryDownloadTasksGenerationTask::~LibraryDownloadTasksGenerationTask()
{
}

void LibraryDownloadTasksGenerationTask::templateStart(QGSTask * task)
{
	QList<QGSLibrary> libraryList;

	QMutexLocker mutexLocker(&mGameBuilderPtr->mMutex);

	QObject::connect(this, &GameVersionJsonDownloadTaskGenerationTask::error, mGameBuilderPtr, &QGSGameBuilder::error);
	QObject::connect(this, &GameVersionJsonDownloadTaskGenerationTask::generationTaskDownloadError, mGameBuilderPtr, &QGSGameBuilder::downloadTaskDownloadError);

	try
	{
		libraryList = mGameBuilderPtr->mGameDirectoryPtr->getVersion(mGameBuilderPtr->mVersionInfo).getLibraries();
	}
	catch (const QGSExceptionVersionNotFound & exception)
	{
		mGameBuilderPtr->mLastErrorString = "Game version:" + mGameBuilderPtr->mVersionInfo.getId() + "not found!";

		mutexLocker.unlock();
		emit error(this);

		return;
	}

	QGSDownloadTask * downloadTask(nullptr);

	for (auto & i : libraryList)
	{
		if (!mGameBuilderPtr->mFileOverride)
		{
			QSharedPointer<QFile> libraryFile(mGameBuilderPtr->mGameDirectoryPtr->generateLibraryFile(i));
			if (libraryFile->exists())
			{
				continue;
			}
		}

		downloadTask = mGameBuilderPtr->mDownloadTaskFactoryPtr->generateLibraryDownloadTask(i, *(mGameBuilderPtr->mGameDirectoryPtr));
		if (!downloadTask)
		{
			mGameBuilderPtr->mLastErrorString = "Generating library download task failed!";
			mutexLocker.unlock();

			emit error(this);
			emit generationTaskDownloadError(QGSNetworkError(QNetworkReply::NetworkError::NoError, "Generating library download task failed!"),
				downloadTask);

			return;
		}
		mGameBuilderPtr->mTaskList.push_back(downloadTask);
		QObject::connect(downloadTask, &QGSDownloadTask::started, mGameBuilderPtr, &QGSGameBuilder::downloadTaskStarted);
		QObject::connect(downloadTask, &QGSDownloadTask::finished, mGameBuilderPtr, &QGSGameBuilder::downloadTaskFinished);
		QObject::connect(downloadTask, &QGSDownloadTask::stoped, mGameBuilderPtr, &QGSGameBuilder::downloadTaskStoped);
		QObject::connect(downloadTask, &QGSDownloadTask::canceled, mGameBuilderPtr, &QGSGameBuilder::downloadTaskCanceled);
		QObject::connect(downloadTask, &QGSDownloadTask::downloadError, mGameBuilderPtr, &QGSGameBuilder::downloadTaskDownloadError);
		QObject::connect(downloadTask, &QGSDownloadTask::error, mGameBuilderPtr, &QGSGameBuilder::downloadTaskError);
		QObject::connect(downloadTask, &QGSDownloadTask::finished, mGameBuilderPtr, &QGSGameBuilder::slotEraseDownloadTask);
		QObject::connect(downloadTask, &QGSDownloadTask::finished, mGameBuilderPtr, &QGSGameBuilder::slotDownloadTaskFinished);
		QGSThreadPool::getGlobalInstance().addTaskBack(downloadTask);
	}

	emit finished(this);
}

AssetIndexJsonDownloadTaskGenerationTask::AssetIndexJsonDownloadTaskGenerationTask(QGSGameBuilder * gameBuilder)
	:mGameBuilderPtr(gameBuilder)
{
	if (!mGameBuilderPtr)
	{
		throw QGSExceptionInvalidValue();
	}
}

AssetIndexJsonDownloadTaskGenerationTask::~AssetIndexJsonDownloadTaskGenerationTask()
{
}

void AssetIndexJsonDownloadTaskGenerationTask::templateStart(QGSTask * task)
{
	QGSDownloadTask * downloadTask(nullptr);

	QMutexLocker mutexLocker(&mGameBuilderPtr->mMutex);

	QObject::connect(this, &GameVersionJsonDownloadTaskGenerationTask::error, mGameBuilderPtr, &QGSGameBuilder::error);
	QObject::connect(this, &GameVersionJsonDownloadTaskGenerationTask::generationTaskDownloadError, mGameBuilderPtr, &QGSGameBuilder::downloadTaskDownloadError);

	try
	{
		downloadTask = mGameBuilderPtr->mDownloadTaskFactoryPtr->generateAssetIndexJsonDownloadTask(mGameBuilderPtr->mGameDirectoryPtr->getVersion(mGameBuilderPtr->mVersionInfo).getAssetIndex(),
			*(mGameBuilderPtr->mGameDirectoryPtr));
	}
	catch (const QGSExceptionVersionNotFound & exception)
	{
		mGameBuilderPtr->mLastErrorString = "Game version:" + mGameBuilderPtr->mVersionInfo.getId() + "not found!";
		mutexLocker.unlock();

		emit error(this);

		return;
	}

	if (!downloadTask)
	{
		mGameBuilderPtr->mLastErrorString = "Generating asset index json download task failed!";
		mutexLocker.unlock();

		emit error(this);
		emit generationTaskDownloadError(QGSNetworkError(QNetworkReply::NetworkError::NoError, "Generating asset index json download task failed!"),
			downloadTask);

		return;
	}
	downloadTask->setTaskQueueBlock(true);
	mGameBuilderPtr->mTaskList.push_front(downloadTask);
	QObject::connect(downloadTask, &QGSDownloadTask::started, mGameBuilderPtr, &QGSGameBuilder::downloadTaskStarted);
	QObject::connect(downloadTask, &QGSDownloadTask::finished, mGameBuilderPtr, &QGSGameBuilder::downloadTaskFinished);
	QObject::connect(downloadTask, &QGSDownloadTask::stoped, mGameBuilderPtr, &QGSGameBuilder::downloadTaskStoped);
	QObject::connect(downloadTask, &QGSDownloadTask::canceled, mGameBuilderPtr, &QGSGameBuilder::downloadTaskCanceled);
	QObject::connect(downloadTask, &QGSDownloadTask::downloadError, mGameBuilderPtr, &QGSGameBuilder::downloadTaskDownloadError);
	QObject::connect(downloadTask, &QGSDownloadTask::error, mGameBuilderPtr, &QGSGameBuilder::downloadTaskError);
	QObject::connect(downloadTask, &QGSDownloadTask::finished, mGameBuilderPtr, &QGSGameBuilder::slotEraseDownloadTask);
	QObject::connect(downloadTask, &QGSDownloadTask::finished, mGameBuilderPtr, &QGSGameBuilder::slotDownloadTaskFinished);
	QGSThreadPool::getGlobalInstance().addTaskFront(downloadTask);

	emit finished(this);
}

AssetObjectDownloadTasksGenerationTask::AssetObjectDownloadTasksGenerationTask(QGSGameBuilder * gameBuilder)
	:mGameBuilderPtr(gameBuilder)
{
	if (!mGameBuilderPtr)
	{
		throw QGSExceptionInvalidValue();
	}
}

AssetObjectDownloadTasksGenerationTask::~AssetObjectDownloadTasksGenerationTask()
{
}

void AssetObjectDownloadTasksGenerationTask::templateStart(QGSTask * task)
{
	QGSDownloadTask * downloadTask(nullptr);

	QMutexLocker mutexLocker(&mGameBuilderPtr->mMutex);

	QObject::connect(this, &GameVersionJsonDownloadTaskGenerationTask::error, mGameBuilderPtr, &QGSGameBuilder::error);
	QObject::connect(this, &GameVersionJsonDownloadTaskGenerationTask::generationTaskDownloadError, mGameBuilderPtr, &QGSGameBuilder::downloadTaskDownloadError);

	QGSAssetIndexInfoFactory assetIndexversionInfoFactory;

	QSharedPointer<QFile> assetIndexJsonFile(mGameBuilderPtr->mGameDirectoryPtr->generateAssetIndexJsonFile(mGameBuilderPtr->mVersionInfo));
	if (!assetIndexJsonFile->open(QIODevice::ReadOnly))
	{
		mGameBuilderPtr->mLastErrorString = "Opening asset index json file failed!";
		mutexLocker.unlock();

		emit error(this);

		return;
	}

	QGSAssetIndexInfo assetIndexInfo;
	try
	{
		assetIndexInfo = assetIndexversionInfoFactory.createAssetIndexInfo(assetIndexJsonFile->readAll());
	}
	catch (const QGSExceptionJsonPraseError & exception)
	{
		mGameBuilderPtr->mLastErrorString = "Prasing asset index json failed!";
		mutexLocker.unlock();

		emit error(this);

		return;
	}

	auto && assetObjectMap(assetIndexInfo.getAssetObjectMap());

	for (auto & i : assetObjectMap)
	{
		if (!mGameBuilderPtr->mFileOverride)
		{
			QSharedPointer<QFile> libraryFile(mGameBuilderPtr->mGameDirectoryPtr->generateAssetObjectFile(i));
			if (libraryFile->exists())
			{
				continue;
			}
		}

		downloadTask = mGameBuilderPtr->mDownloadTaskFactoryPtr->generateAssetObjectDownloadTask(i, *(mGameBuilderPtr->mGameDirectoryPtr));
		if (!downloadTask)
		{
			mGameBuilderPtr->mLastErrorString = "Generating asset object download task failed!";

			mutexLocker.unlock();
			emit error(this);
			emit generationTaskDownloadError(QGSNetworkError(QNetworkReply::NetworkError::NoError, "Generating asset object download task failed!"),
				downloadTask);

			return;
		}
		mGameBuilderPtr->mTaskList.push_back(downloadTask);
		QObject::connect(downloadTask, &QGSDownloadTask::started, mGameBuilderPtr, &QGSGameBuilder::downloadTaskStarted);
		QObject::connect(downloadTask, &QGSDownloadTask::finished, mGameBuilderPtr, &QGSGameBuilder::downloadTaskFinished);
		QObject::connect(downloadTask, &QGSDownloadTask::stoped, mGameBuilderPtr, &QGSGameBuilder::downloadTaskStoped);
		QObject::connect(downloadTask, &QGSDownloadTask::canceled, mGameBuilderPtr, &QGSGameBuilder::downloadTaskCanceled);
		QObject::connect(downloadTask, &QGSDownloadTask::downloadError, mGameBuilderPtr, &QGSGameBuilder::downloadTaskDownloadError);
		QObject::connect(downloadTask, &QGSDownloadTask::error, mGameBuilderPtr, &QGSGameBuilder::downloadTaskError);
		QObject::connect(downloadTask, &QGSDownloadTask::finished, mGameBuilderPtr, &QGSGameBuilder::slotEraseDownloadTask);
		QObject::connect(downloadTask, &QGSDownloadTask::finished, mGameBuilderPtr, &QGSGameBuilder::slotDownloadTaskFinished);
		QGSThreadPool::getGlobalInstance().addTaskBack(downloadTask);
	}

	emit finished(this);
}
*/

/**/

static const unsigned long DEFAULT_SLEEP_TIME(1000);

QGSThreadPool QGSGameBuilder::mThreadPool(8,200);

QGSGameBuilder::QGSGameBuilder(QGSGameVersionInfo & versionInfo, QGSGameDirectory * gameDirectory, QGSDownloadTaskFactory * downloadTaskFactory, QObject * parent)
	:QGSIBuilder(parent), mTimerPtr(nullptr), mVersionInfo(versionInfo), mGameDirectoryPtr(gameDirectory), mDownloadTaskFactoryPtr(downloadTaskFactory), mFileOverride(false)
{
	if (!mGameDirectoryPtr || !mDownloadTaskFactoryPtr)
	{
		throw QGSExceptionInvalidValue();
	}

	if (!mThreadPool.isRunning())
	{
		mThreadPool.start();
	}

}

QGSGameBuilder::~QGSGameBuilder()
{	
	QMutexLocker mutexLocker(&mMutex);

	for (auto & task : mTaskList)
	{
		task->deleteLater();
	}

	if (mTimerPtr)
	{
		mTimerPtr->deleteLater();
		mTimerPtr = nullptr;
	}
}

bool QGSGameBuilder::isFileOverride()
{
	QMutexLocker mutexLocker(&mMutex);

	return mFileOverride;
}

QGSGameBuilder & QGSGameBuilder::setFileOverride(const bool fileOverride)
{
	QMutexLocker mutexLocker(&mMutex);

	mFileOverride = fileOverride;
	return *this;
}

QString QGSGameBuilder::getLastErrorString()
{
	QMutexLocker mutexLocker(&mMutex);

	return mLastErrorString;
}

int QGSGameBuilder::getTaskListSize()
{
	QMutexLocker mutexLocker(&mMutex);

	return mTaskList.size();
}

QGSThreadPool & QGSGameBuilder::getThreadPool()
{
	return mThreadPool;
}

void QGSGameBuilder::templateStart(QGSTask * task)
{
	emit started(this);

	mMutex.lock();

	if (mTaskList.size())
	{
		for (auto & downloadTask : mTaskList)
		{
			downloadTask->start();
		}

		return;
	}
	
	if (!mTimerPtr)
	{
		mTimerPtr = new QTimer(this);
	}
	QObject::connect(mTimerPtr, &QTimer::timeout, this, &QGSGameBuilder::deleteTasksFinished);
	mTimerPtr->start(DEFAULT_SLEEP_TIME);

	mMutex.unlock();

	initDownloadTasks();

	/*
	auto * gameVersionJsonDownloadTaskGenerationTask(new GameVersionJsonDownloadTaskGenerationTask(this));
	mTaskList.push_back(gameVersionJsonDownloadTaskGenerationTask);
	gameVersionJsonDownloadTaskGenerationTask->setTaskQueueBlock(true);
	QObject::connect(gameVersionJsonDownloadTaskGenerationTask, &QGSDownloadTask::finished, this, &QGSGameBuilder::slotEraseDownloadTask);
	QObject::connect(gameVersionJsonDownloadTaskGenerationTask, &QGSDownloadTask::finished, this, &QGSGameBuilder::slotDownloadTaskFinished);
	QGSThreadPool::getGlobalInstance().addTaskBack(gameVersionJsonDownloadTaskGenerationTask);

	auto * gameVersionDownloadTaskGenerationTask(new GameVersionDownloadTaskGenerationTask(this));
	mTaskList.push_back(gameVersionDownloadTaskGenerationTask);
	QObject::connect(gameVersionDownloadTaskGenerationTask, &QGSDownloadTask::finished, this, &QGSGameBuilder::slotEraseDownloadTask);
	QObject::connect(gameVersionDownloadTaskGenerationTask, &QGSDownloadTask::finished, this, &QGSGameBuilder::slotDownloadTaskFinished);
	QGSThreadPool::getGlobalInstance().addTaskBack(gameVersionDownloadTaskGenerationTask);

	auto * libraryDownloadTasksGenerationTask(new LibraryDownloadTasksGenerationTask(this));
	mTaskList.push_back(libraryDownloadTasksGenerationTask);
	QObject::connect(libraryDownloadTasksGenerationTask, &QGSDownloadTask::finished, this, &QGSGameBuilder::slotEraseDownloadTask);
	QObject::connect(libraryDownloadTasksGenerationTask, &QGSDownloadTask::finished, this, &QGSGameBuilder::slotDownloadTaskFinished);
	QGSThreadPool::getGlobalInstance().addTaskBack(libraryDownloadTasksGenerationTask);

	auto * assetIndexJsonDownloadTaskGenerationTask(new AssetIndexJsonDownloadTaskGenerationTask(this));
	mTaskList.push_back(assetIndexJsonDownloadTaskGenerationTask);
	assetIndexJsonDownloadTaskGenerationTask->setTaskQueueBlock(true);
	QObject::connect(assetIndexJsonDownloadTaskGenerationTask, &QGSDownloadTask::finished, this, &QGSGameBuilder::slotEraseDownloadTask);
	QObject::connect(assetIndexJsonDownloadTaskGenerationTask, &QGSDownloadTask::finished, this, &QGSGameBuilder::slotDownloadTaskFinished);
	QGSThreadPool::getGlobalInstance().addTaskBack(assetIndexJsonDownloadTaskGenerationTask);

	auto * assetObjectDownloadTasksGenerationTask(new AssetObjectDownloadTasksGenerationTask(this));
	mTaskList.push_back(assetObjectDownloadTasksGenerationTask);
	QObject::connect(assetObjectDownloadTasksGenerationTask, &QGSDownloadTask::finished, this, &QGSGameBuilder::slotEraseDownloadTask);
	QObject::connect(assetObjectDownloadTasksGenerationTask, &QGSDownloadTask::finished, this, &QGSGameBuilder::slotDownloadTaskFinished);
	QGSThreadPool::getGlobalInstance().addTaskBack(assetObjectDownloadTasksGenerationTask);
	*/
	//slotDownloadTaskFinished(nullptr);
}

void QGSGameBuilder::templateStop(QGSTask * task)
{
	QMutexLocker mutexLocker(&mMutex);

	for (auto & downloadTask : mTaskList)
	{
		downloadTask->stop();
	}

	mTimerPtr->disconnect();

	mutexLocker.unlock();

	emit stoped(this);
}

void QGSGameBuilder::templateCancel(QGSTask * task)
{
	QMutexLocker mutexLocker(&mMutex);

	for (auto & downloadTask : mTaskList)
	{
		downloadTask->cancel();
	}

	mTimerPtr->disconnect();

	mutexLocker.unlock();

	emit canceled(this);
}

void QGSGameBuilder::slotDownloadTaskStarted(QGSTask * task)
{
	QMutexLocker mutexLocker(&mMutex);

	auto * downloadTask(dynamic_cast<QGSDownloadTask *>(task));

	mutexLocker.unlock();

	emit downloadTaskStarted(downloadTask->getDownloadInfo());
}

void QGSGameBuilder::slotDownloadTaskFinished(QGSTask * task)
{
	QMutexLocker mutexLocker(&mMutex);

	auto * downloadTask(dynamic_cast<QGSDownloadTask *>(task));

	mutexLocker.unlock();

	emit downloadTaskFinished(downloadTask->getDownloadInfo());
}

void QGSGameBuilder::slotDownloadTaskStoped(QGSTask * task)
{
	QMutexLocker mutexLocker(&mMutex);

	auto * downloadTask(dynamic_cast<QGSDownloadTask *>(task));

	mutexLocker.unlock();

	emit downloadTaskStoped(downloadTask->getDownloadInfo());
}

void QGSGameBuilder::slotDownloadTaskCanceled(QGSTask * task)
{
	QMutexLocker mutexLocker(&mMutex);

	auto * downloadTask(dynamic_cast<QGSDownloadTask *>(task));

	mutexLocker.unlock();

	emit downloadTaskCanceled(downloadTask->getDownloadInfo());
}

void QGSGameBuilder::slotDownloadTaskDownloadError(QGSNetworkError error, QGSTask * task)
{
	QMutexLocker mutexLocker(&mMutex);

	auto * downloadTask(dynamic_cast<QGSDownloadTask *>(task));

	mutexLocker.unlock();

	emit downloadTaskDownloadError(error, downloadTask->getDownloadInfo());
}

void QGSGameBuilder::slotDownloadTaskError(QGSTask * task)
{
	QMutexLocker mutexLocker(&mMutex);

	auto * downloadTask(dynamic_cast<QGSDownloadTask *>(task));

	mutexLocker.unlock();

	emit downloadTaskError(downloadTask->getDownloadInfo());
}

void QGSGameBuilder::slotDownloadTaskDownloadProgress(qint64 bytesReceived, qint64 bytesTotal, QGSTask * task)
{
	QMutexLocker mutexLocker(&mMutex);
	auto * downloadTask(dynamic_cast<QGSDownloadTask *>(task));

	mutexLocker.unlock();

	emit downloadTaskDownloadProgress(bytesReceived, bytesTotal, downloadTask->getDownloadInfo());
}

void QGSGameBuilder::initDownloadTasks()
{
	auto * gameVersionJsonDownloadTask(initGameVersionJsonDownloadTask());
	if (gameVersionJsonDownloadTask)
	{
		QObject::connect(gameVersionJsonDownloadTask, &QGSDownloadTask::finished, this, [=]()
		{
			if (initGameVersionDownloadTask() && initLibraryDownloadTasks());

			auto * assetIndexJsonDownloadTask(initAssetIndexJsonDownloadTask());

			QObject::connect(assetIndexJsonDownloadTask, &QGSDownloadTask::finished, this, [=]()
			{
				QGSAssetIndexInfoFactory assetIndexversionInfoFactory;

				if (!assetIndexJsonDownloadTask->getTargetFile()->open(QIODevice::ReadOnly))
				{
					emit error(this);
					mLastErrorString = "Opening asset index json file failed!";

					return;
				}

				try
				{
					mAssetIndexInfo = assetIndexversionInfoFactory.createAssetIndexInfo(assetIndexJsonDownloadTask->getTargetFile()->readAll());
				}
				catch (const QGSExceptionJsonPraseError & exception)
				{
					emit error(this);
					mLastErrorString = "Prasing asset index json failed!";

					return;
				}

				if (initAssetObjectDownloadTasks());

				slotFinished();

			});

		});
	}
}

QGSDownloadTask * QGSGameBuilder::initGameVersionJsonDownloadTask()
{
	QMutexLocker mutexLocker(&mMutex);
	QGSDownloadTask * downloadTask(nullptr);

	downloadTask = mDownloadTaskFactoryPtr->generateGameVersionJsonDownloadTask(mVersionInfo, *mGameDirectoryPtr);
	if (!downloadTask)
	{
		emit error(this);
		emit downloadTaskDownloadError(QGSNetworkError(QNetworkReply::NetworkError::NoError, "Generating game version json download task failed!"),
			downloadTask->getDownloadInfo());
		mLastErrorString = "Generating game version json download task failed!";

		return nullptr;
	}
	mTaskList.push_back(downloadTask);
	QObject::connect(downloadTask, &QGSDownloadTask::started, this, &QGSGameBuilder::slotDownloadTaskStarted);
	QObject::connect(downloadTask, &QGSDownloadTask::finished, this, &QGSGameBuilder::slotDownloadTaskFinished);
	QObject::connect(downloadTask, &QGSDownloadTask::stoped, this, &QGSGameBuilder::slotDownloadTaskStoped);
	QObject::connect(downloadTask, &QGSDownloadTask::canceled, this, &QGSGameBuilder::slotDownloadTaskCanceled);
	QObject::connect(downloadTask, &QGSDownloadTask::downloadProgress, this, &QGSGameBuilder::slotDownloadTaskDownloadProgress);
	QObject::connect(downloadTask, &QGSDownloadTask::downloadError, this, &QGSGameBuilder::slotDownloadTaskDownloadError);
	QObject::connect(downloadTask, &QGSDownloadTask::error, this, &QGSGameBuilder::slotDownloadTaskError);
	QObject::connect(downloadTask, &QGSDownloadTask::finished, this, &QGSGameBuilder::slotEraseDownloadTask);
	QObject::connect(downloadTask, &QGSDownloadTask::canceled, this, &QGSGameBuilder::slotEraseDownloadTask);
	QObject::connect(downloadTask, &QGSDownloadTask::error, this, &QGSGameBuilder::slotEraseDownloadTask);
	mThreadPool.addTaskBack(downloadTask);

	return downloadTask;
}

bool QGSGameBuilder::initGameVersionDownloadTask()
{
	QMutexLocker mutexLocker(&mMutex);
	if (!mFileOverride)
	{
		QSharedPointer<QFile> gameVersionJarFile(mGameDirectoryPtr->generateGameVersionJarFile(mVersionInfo.getId()));
		if (gameVersionJarFile->exists())
		{
			return true;
		}
	}

	QGSDownloadTask * downloadTask(nullptr);

	auto & version(mGameDirectoryPtr->getVersion(mVersionInfo));
	downloadTask = mDownloadTaskFactoryPtr->generateGameVersionDownloadTask(version, *mGameDirectoryPtr, "client");
	if (!downloadTask)
	{
		emit error(this);
		emit downloadTaskDownloadError(QGSNetworkError(QNetworkReply::NetworkError::NoError, "Generating game version download task failed!"),
			downloadTask->getDownloadInfo());
		mLastErrorString = "Generating game version download task failed!";

		return false;
	}
	mTaskList.push_back(downloadTask);
	QObject::connect(downloadTask, &QGSDownloadTask::started, this, &QGSGameBuilder::slotDownloadTaskStarted);
	QObject::connect(downloadTask, &QGSDownloadTask::finished, this, &QGSGameBuilder::slotDownloadTaskFinished);
	QObject::connect(downloadTask, &QGSDownloadTask::stoped, this, &QGSGameBuilder::slotDownloadTaskStoped);
	QObject::connect(downloadTask, &QGSDownloadTask::canceled, this, &QGSGameBuilder::slotDownloadTaskCanceled);
	QObject::connect(downloadTask, &QGSDownloadTask::downloadProgress, this, &QGSGameBuilder::slotDownloadTaskDownloadProgress);
	QObject::connect(downloadTask, &QGSDownloadTask::downloadError, this, &QGSGameBuilder::slotDownloadTaskDownloadError);
	QObject::connect(downloadTask, &QGSDownloadTask::error, this, &QGSGameBuilder::slotDownloadTaskError);
	QObject::connect(downloadTask, &QGSDownloadTask::finished, this, &QGSGameBuilder::slotEraseDownloadTask);
	QObject::connect(downloadTask, &QGSDownloadTask::finished, this, &QGSGameBuilder::slotFinished);
	QObject::connect(downloadTask, &QGSDownloadTask::canceled, this, &QGSGameBuilder::slotEraseDownloadTask);
	QObject::connect(downloadTask, &QGSDownloadTask::canceled, this, &QGSGameBuilder::slotFinished);
	QObject::connect(downloadTask, &QGSDownloadTask::error, this, &QGSGameBuilder::slotEraseDownloadTask);
	QObject::connect(downloadTask, &QGSDownloadTask::error, this, &QGSGameBuilder::slotFinished);
	mThreadPool.addTaskBack(downloadTask);

	return true;
}

bool QGSGameBuilder::initLibraryDownloadTasks()
{
	QMutexLocker mutexLocker(&mMutex);
	QList<QGSLibrary> libraryList;
	try
	{
		libraryList = mGameDirectoryPtr->getVersion(mVersionInfo).getLibraries();
	}
	catch (const QGSExceptionVersionNotFound & exception)
	{
		emit error(this);
		mLastErrorString = "Game version:" + mVersionInfo.getId() + "not found!";

        return false;
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
			emit downloadTaskDownloadError(QGSNetworkError(QNetworkReply::NetworkError::NoError, "Generating library download task failed!"),
				downloadTask->getDownloadInfo());
			mLastErrorString = "Generating library download task failed!";

			return false;
		}
		mTaskList.push_back(downloadTask);
		QObject::connect(downloadTask, &QGSDownloadTask::started, this, &QGSGameBuilder::slotDownloadTaskStarted);
		QObject::connect(downloadTask, &QGSDownloadTask::finished, this, &QGSGameBuilder::slotDownloadTaskFinished);
		QObject::connect(downloadTask, &QGSDownloadTask::stoped, this, &QGSGameBuilder::slotDownloadTaskStoped);
		QObject::connect(downloadTask, &QGSDownloadTask::canceled, this, &QGSGameBuilder::slotDownloadTaskCanceled);
		QObject::connect(downloadTask, &QGSDownloadTask::downloadProgress, this, &QGSGameBuilder::slotDownloadTaskDownloadProgress);
		QObject::connect(downloadTask, &QGSDownloadTask::downloadError, this, &QGSGameBuilder::slotDownloadTaskDownloadError);
		QObject::connect(downloadTask, &QGSDownloadTask::error, this, &QGSGameBuilder::slotDownloadTaskError);
		QObject::connect(downloadTask, &QGSDownloadTask::finished, this, &QGSGameBuilder::slotEraseDownloadTask);
		QObject::connect(downloadTask, &QGSDownloadTask::finished, this, &QGSGameBuilder::slotFinished);
		QObject::connect(downloadTask, &QGSDownloadTask::canceled, this, &QGSGameBuilder::slotEraseDownloadTask);
		QObject::connect(downloadTask, &QGSDownloadTask::canceled, this, &QGSGameBuilder::slotFinished);
		QObject::connect(downloadTask, &QGSDownloadTask::error, this, &QGSGameBuilder::slotEraseDownloadTask);
		QObject::connect(downloadTask, &QGSDownloadTask::error, this, &QGSGameBuilder::slotFinished);
		mThreadPool.addTaskBack(downloadTask);
	}

	return true;
}

QGSDownloadTask *  QGSGameBuilder::initAssetIndexJsonDownloadTask()
{
	QMutexLocker mutexLocker(&mMutex);
	QGSDownloadTask * downloadTask(nullptr);

	try
	{
		downloadTask = mDownloadTaskFactoryPtr->generateAssetIndexJsonDownloadTask(mGameDirectoryPtr->getVersion(mVersionInfo).getAssetIndex(),
			*mGameDirectoryPtr);
	}
	catch (const QGSExceptionVersionNotFound & exception)
	{
		emit error(this);
		mLastErrorString = "Game version:" + mVersionInfo.getId() + "not found!";

		return nullptr;
	}

	if (!downloadTask)
	{
		emit error(this);
		emit downloadTaskDownloadError(QGSNetworkError(QNetworkReply::NetworkError::NoError, "Generating asset index json download task failed!"),
			downloadTask->getDownloadInfo());
		mLastErrorString = "Generating asset index json download task failed!";

		return nullptr;
	}
	mTaskList.push_back(downloadTask);
	QObject::connect(downloadTask, &QGSDownloadTask::started, this, &QGSGameBuilder::slotDownloadTaskStarted);
	QObject::connect(downloadTask, &QGSDownloadTask::finished, this, &QGSGameBuilder::slotDownloadTaskFinished);
	QObject::connect(downloadTask, &QGSDownloadTask::stoped, this, &QGSGameBuilder::slotDownloadTaskStoped);
	QObject::connect(downloadTask, &QGSDownloadTask::canceled, this, &QGSGameBuilder::slotDownloadTaskCanceled);
	QObject::connect(downloadTask, &QGSDownloadTask::downloadProgress, this, &QGSGameBuilder::slotDownloadTaskDownloadProgress);
	QObject::connect(downloadTask, &QGSDownloadTask::downloadError, this, &QGSGameBuilder::slotDownloadTaskDownloadError);
	QObject::connect(downloadTask, &QGSDownloadTask::error, this, &QGSGameBuilder::slotDownloadTaskError);
	QObject::connect(downloadTask, &QGSDownloadTask::finished, this, &QGSGameBuilder::slotEraseDownloadTask);
	QObject::connect(downloadTask, &QGSDownloadTask::canceled, this, &QGSGameBuilder::slotEraseDownloadTask);
	QObject::connect(downloadTask, &QGSDownloadTask::error, this, &QGSGameBuilder::slotEraseDownloadTask);
	mThreadPool.addTaskBack(downloadTask);

	return downloadTask;
}

bool QGSGameBuilder::initAssetObjectDownloadTasks()
{
	QMutexLocker mutexLocker(&mMutex);
	auto && assetObjectMap(mAssetIndexInfo.getAssetObjectMap());
	QGSDownloadTask * downloadTask(nullptr);

	for (auto & i : assetObjectMap)
	{
		if (!mFileOverride)
		{
			QSharedPointer<QFile> assetObjectFile(mGameDirectoryPtr->generateAssetObjectFile(i));
			if (assetObjectFile->exists())
			{
				continue;
			}
		}

		downloadTask = mDownloadTaskFactoryPtr->generateAssetObjectDownloadTask(i, *mGameDirectoryPtr);
		if (!downloadTask)
		{
			emit error(this);
			emit downloadTaskDownloadError(QGSNetworkError(QNetworkReply::NetworkError::NoError, "Generating asset object download task failed!"),
				downloadTask->getDownloadInfo());
			mLastErrorString = "Generating asset object download task failed!";

			return false;
		}
		mTaskList.push_back(downloadTask);
		QObject::connect(downloadTask, &QGSDownloadTask::started, this, &QGSGameBuilder::slotDownloadTaskStarted);
		QObject::connect(downloadTask, &QGSDownloadTask::finished, this, &QGSGameBuilder::slotDownloadTaskFinished);
		QObject::connect(downloadTask, &QGSDownloadTask::stoped, this, &QGSGameBuilder::slotDownloadTaskStoped);
		QObject::connect(downloadTask, &QGSDownloadTask::canceled, this, &QGSGameBuilder::slotDownloadTaskCanceled);
		QObject::connect(downloadTask, &QGSDownloadTask::downloadProgress, this, &QGSGameBuilder::slotDownloadTaskDownloadProgress);
		QObject::connect(downloadTask, &QGSDownloadTask::downloadError, this, &QGSGameBuilder::slotDownloadTaskDownloadError);
		QObject::connect(downloadTask, &QGSDownloadTask::error, this, &QGSGameBuilder::slotDownloadTaskError);
		QObject::connect(downloadTask, &QGSDownloadTask::finished, this, &QGSGameBuilder::slotEraseDownloadTask);
		QObject::connect(downloadTask, &QGSDownloadTask::finished, this, &QGSGameBuilder::slotFinished);
		QObject::connect(downloadTask, &QGSDownloadTask::canceled, this, &QGSGameBuilder::slotEraseDownloadTask);
		QObject::connect(downloadTask, &QGSDownloadTask::canceled, this, &QGSGameBuilder::slotFinished);
		QObject::connect(downloadTask, &QGSDownloadTask::error, this, &QGSGameBuilder::slotEraseDownloadTask);
		QObject::connect(downloadTask, &QGSDownloadTask::error, this, &QGSGameBuilder::slotFinished);
		mThreadPool.addTaskBack(downloadTask);
	}

	return true;
}

void QGSGameBuilder::deleteTasksFinished()
{
	QMutexLocker mutexLocker(&mMutex);
	int halfSize(mTaskWillBeDeletedList.size() / 2);

	if (!halfSize&&mTaskWillBeDeletedList.size())
	{
		halfSize = 1;
	}

	for (auto i = 0; i < halfSize; i++)
	{
		QGSTask * taskWillBeDeleted(mTaskWillBeDeletedList.front());
		mTaskWillBeDeletedList.pop_front();
		taskWillBeDeleted->deleteLater();
	}

	//qDebug() << "QGSGameBuilder::deleteTasksFinished!";
}

void QGSGameBuilder::slotEraseDownloadTask(QGSTask * downloadTask)
{
	QMutexLocker mutexLocker(&mMutex);
	if (!downloadTask)
	{
		return;
	}

	for (auto it = mTaskList.begin(); it != mTaskList.end(); it++)
	{
		if (*it == downloadTask)
		{
			//downloadTask->moveToThread(QCoreApplication::instance()->thread());
			//downloadTask->deleteLater();
			mTaskWillBeDeletedList.push_back(downloadTask);
			mTaskList.erase(it);
			break;
		}
	}

}

void QGSGameBuilder::slotFinished()
{
	if (!getTaskListSize())
	{
		mMutex.lock();

		mTimerPtr->disconnect();

		mMutex.unlock();

		emit finished(this);
	}
}
