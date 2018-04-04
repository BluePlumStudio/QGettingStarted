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
		mGameBuilderPtr->mLastErrorString = "Generating game version json download task!";

		mutexLocker.unlock();
		emit error(this);
		emit generationTaskDownloadError(QGSNetworkError(QNetworkReply::NetworkError::NoError, "Generating game version json download task!"),
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
	QObject::connect(downloadTask, &QGSDownloadTask::finished, mGameBuilderPtr, &QGSGameBuilder::eraseDownloadTask);
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
		mGameBuilderPtr->mLastErrorString = "Generating game version download task!";

		mutexLocker.unlock();

		emit error(this);
		emit generationTaskDownloadError(QGSNetworkError(QNetworkReply::NetworkError::NoError, "Generating game version download task!"),
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
	QObject::connect(downloadTask, &QGSDownloadTask::finished, mGameBuilderPtr, &QGSGameBuilder::eraseDownloadTask);
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
			mGameBuilderPtr->mLastErrorString = "Generating library download task!";
			mutexLocker.unlock();

			emit error(this);
			emit generationTaskDownloadError(QGSNetworkError(QNetworkReply::NetworkError::NoError, "Generating library download task!"),
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
		QObject::connect(downloadTask, &QGSDownloadTask::finished, mGameBuilderPtr, &QGSGameBuilder::eraseDownloadTask);
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
		mGameBuilderPtr->mLastErrorString = "Generating asset index json download task!";
		mutexLocker.unlock();

		emit error(this);
		emit generationTaskDownloadError(QGSNetworkError(QNetworkReply::NetworkError::NoError, "Generating asset index json download task!"),
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
	QObject::connect(downloadTask, &QGSDownloadTask::finished, mGameBuilderPtr, &QGSGameBuilder::eraseDownloadTask);
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
		mGameBuilderPtr->mLastErrorString = "Opening asset index json file!";
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
		mGameBuilderPtr->mLastErrorString = "Prasing asset index json!";
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
			mGameBuilderPtr->mLastErrorString = "Generating asset object download task!";

			mutexLocker.unlock();
			emit error(this);
			emit generationTaskDownloadError(QGSNetworkError(QNetworkReply::NetworkError::NoError, "Generating asset object download task!"),
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
		QObject::connect(downloadTask, &QGSDownloadTask::finished, mGameBuilderPtr, &QGSGameBuilder::eraseDownloadTask);
		QObject::connect(downloadTask, &QGSDownloadTask::finished, mGameBuilderPtr, &QGSGameBuilder::slotDownloadTaskFinished);
		QGSThreadPool::getGlobalInstance().addTaskBack(downloadTask);
	}

	emit finished(this);
}
*/

/**/

static const unsigned long DEFAULT_SLEEP_TIME(1000);

QGSGameBuilder::QGSGameBuilder(QGSGameVersionInfo & versionInfo, QGSGameDirectory * gameDirectory, QGSDownloadTaskFactory * downloadTaskFactory, QObject * parent)
	:QGSIBuilder(parent), 
	//mTimerPtr(nullptr),
	mVersionInfo(versionInfo),
	mGameDirectoryPtr(gameDirectory),
	mDownloadTaskFactoryPtr(downloadTaskFactory), 
	mGameVersionJsonDownloadTask(nullptr),
	mAssetIndexJsonDownloadTask(nullptr),
	mFileOverride(false)
{
	if (!mGameDirectoryPtr || !mDownloadTaskFactoryPtr)
	{
		throw QGSExceptionInvalidValue();
	}

}

QGSGameBuilder::~QGSGameBuilder()
{	
	QMutexLocker mutexLocker(&mMutex);

	for (auto & task : mTaskList)
	{
		task->deleteLater();
	}

	if (mGameVersionJsonDownloadTask)
	{
		mGameVersionJsonDownloadTask->deleteLater();
		mGameVersionJsonDownloadTask = nullptr;
	}

	if (mAssetIndexJsonDownloadTask)
	{
		mAssetIndexJsonDownloadTask->deleteLater();
		mAssetIndexJsonDownloadTask = nullptr;
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

int QGSGameBuilder::getTaskListSize()
{
	QMutexLocker mutexLocker(&mMutex);

	return mTaskList.size();
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
	
	/*
	if (!mTimerPtr)
	{
		mTimerPtr = new QTimer(this);
	}
	QObject::connect(mTimerPtr, &QTimer::timeout, this, &QGSGameBuilder::deleteTasksFinished);
	mTimerPtr->start(DEFAULT_SLEEP_TIME);
	*/

	mMutex.unlock();

	initDownloadTasks();

	/*
	auto * gameVersionJsonDownloadTaskGenerationTask(new GameVersionJsonDownloadTaskGenerationTask(this));
	mTaskList.push_back(gameVersionJsonDownloadTaskGenerationTask);
	gameVersionJsonDownloadTaskGenerationTask->setTaskQueueBlock(true);
	QObject::connect(gameVersionJsonDownloadTaskGenerationTask, &QGSDownloadTask::finished, this, &QGSGameBuilder::eraseDownloadTask);
	QObject::connect(gameVersionJsonDownloadTaskGenerationTask, &QGSDownloadTask::finished, this, &QGSGameBuilder::slotDownloadTaskFinished);
	QGSThreadPool::getGlobalInstance().addTaskBack(gameVersionJsonDownloadTaskGenerationTask);

	auto * gameVersionDownloadTaskGenerationTask(new GameVersionDownloadTaskGenerationTask(this));
	mTaskList.push_back(gameVersionDownloadTaskGenerationTask);
	QObject::connect(gameVersionDownloadTaskGenerationTask, &QGSDownloadTask::finished, this, &QGSGameBuilder::eraseDownloadTask);
	QObject::connect(gameVersionDownloadTaskGenerationTask, &QGSDownloadTask::finished, this, &QGSGameBuilder::slotDownloadTaskFinished);
	QGSThreadPool::getGlobalInstance().addTaskBack(gameVersionDownloadTaskGenerationTask);

	auto * libraryDownloadTasksGenerationTask(new LibraryDownloadTasksGenerationTask(this));
	mTaskList.push_back(libraryDownloadTasksGenerationTask);
	QObject::connect(libraryDownloadTasksGenerationTask, &QGSDownloadTask::finished, this, &QGSGameBuilder::eraseDownloadTask);
	QObject::connect(libraryDownloadTasksGenerationTask, &QGSDownloadTask::finished, this, &QGSGameBuilder::slotDownloadTaskFinished);
	QGSThreadPool::getGlobalInstance().addTaskBack(libraryDownloadTasksGenerationTask);

	auto * assetIndexJsonDownloadTaskGenerationTask(new AssetIndexJsonDownloadTaskGenerationTask(this));
	mTaskList.push_back(assetIndexJsonDownloadTaskGenerationTask);
	assetIndexJsonDownloadTaskGenerationTask->setTaskQueueBlock(true);
	QObject::connect(assetIndexJsonDownloadTaskGenerationTask, &QGSDownloadTask::finished, this, &QGSGameBuilder::eraseDownloadTask);
	QObject::connect(assetIndexJsonDownloadTaskGenerationTask, &QGSDownloadTask::finished, this, &QGSGameBuilder::slotDownloadTaskFinished);
	QGSThreadPool::getGlobalInstance().addTaskBack(assetIndexJsonDownloadTaskGenerationTask);

	auto * assetObjectDownloadTasksGenerationTask(new AssetObjectDownloadTasksGenerationTask(this));
	mTaskList.push_back(assetObjectDownloadTasksGenerationTask);
	QObject::connect(assetObjectDownloadTasksGenerationTask, &QGSDownloadTask::finished, this, &QGSGameBuilder::eraseDownloadTask);
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

	//mTimerPtr->disconnect();

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

	if (mGameVersionJsonDownloadTask)
	{
		mGameVersionJsonDownloadTask->deleteLater();
		mGameVersionJsonDownloadTask = nullptr;
	}

	if (mAssetIndexJsonDownloadTask)
	{
		mAssetIndexJsonDownloadTask->deleteLater();
		mAssetIndexJsonDownloadTask = nullptr;
	}
	mutexLocker.unlock();

	emit canceled(this);
}

void QGSGameBuilder::slotDownloadTaskStarted(QGSTask * task)
{
	auto * downloadTask(dynamic_cast<QGSDownloadTask *>(task));
	auto && downloadInfo(downloadTask->getDownloadInfo());

	emit downloadTaskStarted(downloadInfo);
}

void QGSGameBuilder::slotDownloadTaskFinished(QGSTask * task)
{
	auto * downloadTask(dynamic_cast<QGSDownloadTask *>(task));
	auto && downloadInfo(downloadTask->getDownloadInfo());

	emit downloadTaskFinished(downloadInfo);

	QMutexLocker mutexLocker(&mMutex);
	taskFinished(downloadTask);
	mutexLocker.unlock();
}

void QGSGameBuilder::slotDownloadTaskStoped(QGSTask * task)
{
	auto * downloadTask(dynamic_cast<QGSDownloadTask *>(task));
	auto && downloadInfo(downloadTask->getDownloadInfo());

	emit downloadTaskStoped(downloadInfo);
}

void QGSGameBuilder::slotDownloadTaskCanceled(QGSTask * task)
{
	auto * downloadTask(dynamic_cast<QGSDownloadTask *>(task));
	auto && downloadInfo(downloadTask->getDownloadInfo());

	emit downloadTaskCanceled(downloadInfo);

	QMutexLocker mutexLocker(&mMutex);
	taskFinished(downloadTask);
	mutexLocker.unlock();
}

void QGSGameBuilder::slotDownloadTaskDownloadError(QGSNetworkError _error, QGSTask * task)
{
	auto * downloadTask(dynamic_cast<QGSDownloadTask *>(task));
	auto && downloadInfo(downloadTask->getDownloadInfo());
	auto && error(_error);

	emit downloadTaskDownloadError(error, downloadInfo);
}

void QGSGameBuilder::slotDownloadTaskError(QGSTask * task)
{
	auto * downloadTask(dynamic_cast<QGSDownloadTask *>(task));
	auto && downloadInfo(downloadTask->getDownloadInfo());

	emit downloadTaskError(downloadInfo);

	QMutexLocker mutexLocker(&mMutex);
	taskFinished(downloadTask);
	mutexLocker.unlock();
}

void QGSGameBuilder::slotDownloadTaskDownloadProgress(qint64 bytesReceived, qint64 bytesTotal, QGSTask * task)
{
	auto * downloadTask(dynamic_cast<QGSDownloadTask *>(task));
	auto && downloadInfo(downloadTask->getDownloadInfo());

	emit downloadTaskDownloadProgress(bytesReceived, bytesTotal, downloadInfo);
}

void QGSGameBuilder::initDownloadTasks()
{
	initGameVersionJsonDownloadTask();
	
	if (!mGameVersionJsonDownloadTask)
	{
		taskFinished(nullptr);

		return;
	}

	QObject::connect(mGameVersionJsonDownloadTask, &QGSDownloadTask::finished, this, [=]()
	{
		if (initGameVersionDownloadTask() && initLibraryDownloadTasks());

		initAssetIndexJsonDownloadTask();

		if (!mAssetIndexJsonDownloadTask)
		{
			taskFinished(nullptr);

			return;
		}

		QObject::connect(mAssetIndexJsonDownloadTask, &QGSDownloadTask::finished, this, [=]()
		{
			QGSAssetIndexInfoFactory assetIndexversionInfoFactory;

			if (!mAssetIndexJsonDownloadTask->getTargetFile()->open(QIODevice::ReadOnly))
			{
				emit error(this);
				mLastErrorString = "Failed to open asset index json file!";

				return;
			}

			try
			{
				mAssetIndexInfo = assetIndexversionInfoFactory.createAssetIndexInfo(mAssetIndexJsonDownloadTask->getTargetFile()->readAll());
			}
			catch (const QGSExceptionJsonPraseError & exception)
			{
				emit error(this);
				mLastErrorString = "Failed to prase asset index json!";

				return;
			}

			if (initAssetObjectDownloadTasks());

			taskFinished(nullptr);

		});

	});
}

QGSDownloadTask * QGSGameBuilder::initGameVersionJsonDownloadTask()
{
	QMutexLocker mutexLocker(&mMutex);

	mGameVersionJsonDownloadTask = mDownloadTaskFactoryPtr->generateGameVersionJsonDownloadTask(mVersionInfo, *mGameDirectoryPtr);
	if (!mGameVersionJsonDownloadTask)
	{
		emit error(this);
		mLastErrorString = "Failed to generate game version json download task!";

		return nullptr;
	}
	mTaskList.push_back(mGameVersionJsonDownloadTask);
	QObject::connect(mGameVersionJsonDownloadTask, &QGSDownloadTask::started, this, &QGSGameBuilder::slotDownloadTaskStarted);
	QObject::connect(mGameVersionJsonDownloadTask, &QGSDownloadTask::finished, this, &QGSGameBuilder::slotDownloadTaskFinished);
	QObject::connect(mGameVersionJsonDownloadTask, &QGSDownloadTask::stoped, this, &QGSGameBuilder::slotDownloadTaskStoped);
	QObject::connect(mGameVersionJsonDownloadTask, &QGSDownloadTask::canceled, this, &QGSGameBuilder::slotDownloadTaskCanceled);
	QObject::connect(mGameVersionJsonDownloadTask, &QGSDownloadTask::downloadProgress, this, &QGSGameBuilder::slotDownloadTaskDownloadProgress);
	QObject::connect(mGameVersionJsonDownloadTask, &QGSDownloadTask::downloadError, this, &QGSGameBuilder::slotDownloadTaskDownloadError);
	QObject::connect(mGameVersionJsonDownloadTask, &QGSDownloadTask::error, this, &QGSGameBuilder::slotDownloadTaskError);
	mThreadPool.addTaskBack(mGameVersionJsonDownloadTask);

	return mGameVersionJsonDownloadTask;
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
		mLastErrorString = "Failed to generate game version download task!";

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
			mLastErrorString = "Failed to generate library download task!";

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
		mThreadPool.addTaskBack(downloadTask);
	}

	return true;
}

QGSDownloadTask *  QGSGameBuilder::initAssetIndexJsonDownloadTask()
{
	QMutexLocker mutexLocker(&mMutex);

	try
	{
		mAssetIndexJsonDownloadTask = mDownloadTaskFactoryPtr->generateAssetIndexJsonDownloadTask(mGameDirectoryPtr->getVersion(mVersionInfo).getAssetIndex(),
			*mGameDirectoryPtr);
	}
	catch (const QGSExceptionVersionNotFound & exception)
	{
		emit error(this);
		mLastErrorString = "Game version:" + mVersionInfo.getId() + "not found!";

		return nullptr;
	}

	if (!mAssetIndexJsonDownloadTask)
	{
		emit error(this);
		mLastErrorString = "Failed to generate asset index json download task!";

		return nullptr;
	}
	mTaskList.push_back(mAssetIndexJsonDownloadTask);
	QObject::connect(mAssetIndexJsonDownloadTask, &QGSDownloadTask::started, this, &QGSGameBuilder::slotDownloadTaskStarted);
	QObject::connect(mAssetIndexJsonDownloadTask, &QGSDownloadTask::finished, this, &QGSGameBuilder::slotDownloadTaskFinished);
	QObject::connect(mAssetIndexJsonDownloadTask, &QGSDownloadTask::stoped, this, &QGSGameBuilder::slotDownloadTaskStoped);
	QObject::connect(mAssetIndexJsonDownloadTask, &QGSDownloadTask::canceled, this, &QGSGameBuilder::slotDownloadTaskCanceled);
	QObject::connect(mAssetIndexJsonDownloadTask, &QGSDownloadTask::downloadProgress, this, &QGSGameBuilder::slotDownloadTaskDownloadProgress);
	QObject::connect(mAssetIndexJsonDownloadTask, &QGSDownloadTask::downloadError, this, &QGSGameBuilder::slotDownloadTaskDownloadError);
	QObject::connect(mAssetIndexJsonDownloadTask, &QGSDownloadTask::error, this, &QGSGameBuilder::slotDownloadTaskError);
	mThreadPool.addTaskBack(mAssetIndexJsonDownloadTask);

	return mAssetIndexJsonDownloadTask;
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
			mLastErrorString = "Failed to generate asset object download task!";

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
		mThreadPool.addTaskBack(downloadTask);
	}

	return true;
}

/*
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
		mTaskWillBeDeletedList.front()->deleteLater();
		mTaskWillBeDeletedList.pop_front();
	}

	//qDebug() << "QGSGameBuilder::deleteTasksFinished!";
}
*/

void QGSGameBuilder::eraseDownloadTask(QGSTask * downloadTask)
{
	if (!downloadTask)
	{
		return;
	}

	for (auto it = mTaskList.begin(); it != mTaskList.end(); it++)
	{
		if (*it == downloadTask)
		{
			mTaskList.erase(it);
			if (downloadTask != mAssetIndexJsonDownloadTask && downloadTask != mGameVersionJsonDownloadTask)
			{
				downloadTask->deleteLater();

			}
			break;

		}
	}

}

void QGSGameBuilder::taskFinished(QGSTask * downloadTask)
{
	eraseDownloadTask(downloadTask);

	if (!mTaskList.size())
	{
		emit finished(this);
	}
}
