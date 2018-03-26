#include "QGSGameBuilder.h"
#include "../Util/QGSExceptionJsonPraseError.h"
#include "../Util/QGSExceptionVersionNotFound.h"
#include "../Util/QGSExceptionFileIO.h"
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
	QMutexLocker mutexLocker{ &mGameBuilderPtr->mMutex };

	QGSDownloadTask * downloadTask{ nullptr };

	downloadTask = mGameBuilderPtr->mDownloadTaskFactoryPtr->generateGameVersionJsonDownloadTask(
		mGameBuilderPtr->mVersionInfo, *(mGameBuilderPtr->mGameDirectoryPtr));
	if (!downloadTask)
	{
		QObject::connect(this, &GameVersionJsonDownloadTaskGenerationTask::error, mGameBuilderPtr, &QGSGameBuilder::error);
		QObject::connect(this, &GameVersionJsonDownloadTaskGenerationTask::generationTaskDownloadError, mGameBuilderPtr, &QGSGameBuilder::downloadTaskDownloadError);
		mGameBuilderPtr->mLastErrorString = "Generating game version json download task failed!";

		mutexLocker.unlock();
		emit error(this);
		emit generationTaskDownloadError(QGSNetworkError{ QNetworkReply::NetworkError::NoError, "Generating game version json download task failed!" },
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
	QMutexLocker mutexLocker{ &mGameBuilderPtr->mMutex };

	if (!mGameBuilderPtr->mFileOverride)
	{
		QSharedPointer<QFile> gameVersionJarFile{ mGameBuilderPtr->mGameDirectoryPtr->generateGameVersionJarFile(mGameBuilderPtr->mVersionInfo.getId()) };
		if (gameVersionJarFile->exists())
		{
			mutexLocker.unlock();
			emit finished(this);
			return;
		}
	}

	QGSDownloadTask * downloadTask{ nullptr };

	auto & version{ mGameBuilderPtr->mGameDirectoryPtr->getVersion(mGameBuilderPtr->mVersionInfo) };
	downloadTask = mGameBuilderPtr->mDownloadTaskFactoryPtr->generateGameVersionDownloadTask(version, *(mGameBuilderPtr->mGameDirectoryPtr), "client");
	if (!downloadTask)
	{
		QObject::connect(this, &GameVersionJsonDownloadTaskGenerationTask::error, mGameBuilderPtr, &QGSGameBuilder::error);
		QObject::connect(this, &GameVersionJsonDownloadTaskGenerationTask::generationTaskDownloadError, mGameBuilderPtr, &QGSGameBuilder::downloadTaskDownloadError);
		mGameBuilderPtr->mLastErrorString = "Generating game version download task failed!";

		mutexLocker.unlock();

		emit error(this);
		emit generationTaskDownloadError(QGSNetworkError{ QNetworkReply::NetworkError::NoError, "Generating game version download task failed!" },
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

	QMutexLocker mutexLocker{ &mGameBuilderPtr->mMutex };

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

	QGSDownloadTask * downloadTask{ nullptr };

	for (auto & i : libraryList)
	{
		if (!mGameBuilderPtr->mFileOverride)
		{
			QSharedPointer<QFile> libraryFile{ mGameBuilderPtr->mGameDirectoryPtr->generateLibraryFile(i) };
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
			emit generationTaskDownloadError(QGSNetworkError{ QNetworkReply::NetworkError::NoError, "Generating library download task failed!" },
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
	QGSDownloadTask * downloadTask{ nullptr };

	QMutexLocker mutexLocker{ &mGameBuilderPtr->mMutex };

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
		emit generationTaskDownloadError(QGSNetworkError{ QNetworkReply::NetworkError::NoError, "Generating asset index json download task failed!" },
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
	QGSDownloadTask * downloadTask{ nullptr };

	QMutexLocker mutexLocker{ &mGameBuilderPtr->mMutex };

	QObject::connect(this, &GameVersionJsonDownloadTaskGenerationTask::error, mGameBuilderPtr, &QGSGameBuilder::error);
	QObject::connect(this, &GameVersionJsonDownloadTaskGenerationTask::generationTaskDownloadError, mGameBuilderPtr, &QGSGameBuilder::downloadTaskDownloadError);

	QGSAssetIndexInfoFactory assetIndexversionInfoFactory;

	QSharedPointer<QFile> assetIndexJsonFile{ mGameBuilderPtr->mGameDirectoryPtr->generateAssetIndexJsonFile(mGameBuilderPtr->mVersionInfo) };
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

	auto && assetObjectMap{ assetIndexInfo.getAssetObjectMap() };

	for (auto & i : assetObjectMap)
	{
		if (!mGameBuilderPtr->mFileOverride)
		{
			QSharedPointer<QFile> libraryFile{ mGameBuilderPtr->mGameDirectoryPtr->generateAssetObjectFile(i) };
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
			emit generationTaskDownloadError(QGSNetworkError{ QNetworkReply::NetworkError::NoError, "Generating asset object download task failed!" },
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

QGSGameBuilder::QGSGameBuilder(QGSGameVersionInfo & versionInfo, QGSGameDirectory * gameDirectory, QGSDownloadTaskFactory * downloadTaskFactory)
	:mVersionInfo(versionInfo), mGameDirectoryPtr(gameDirectory), mDownloadTaskFactoryPtr(downloadTaskFactory), mFileOverride(false)
{
	if (!mGameDirectoryPtr || !mDownloadTaskFactoryPtr)
	{
		throw QGSExceptionInvalidValue();
	}
}

QGSGameBuilder::~QGSGameBuilder()
{
	QMutexLocker mutexLocker{ &mMutex };
	
	for (auto & task : mTaskList)
	{
		task->deleteLater();
	}
}

bool QGSGameBuilder::isFileOverride()
{
	QMutexLocker mutexLocker{ &mMutex };

	return mFileOverride;
}

QGSGameBuilder & QGSGameBuilder::setFileOverride(const bool fileOverride)
{
	QMutexLocker mutexLocker{ &mMutex };

	mFileOverride = fileOverride;
	return *this;
}

QString QGSGameBuilder::getLastErrorString()
{
	QMutexLocker mutexLocker{ &mMutex };

	return mLastErrorString;
}

void QGSGameBuilder::templateStart(QGSTask * task)
{
	mMutex.lock();

	emit started(this);

	if (mTaskList.size())
	{
		for (auto & downloadTask : mTaskList)
		{
			downloadTask->start();
		}

		return;
	}

	mMutex.unlock();

	initDownloadTasks();

	/*
	auto * gameVersionJsonDownloadTaskGenerationTask{ new GameVersionJsonDownloadTaskGenerationTask{ this } };
	mTaskList.push_back(gameVersionJsonDownloadTaskGenerationTask);
	gameVersionJsonDownloadTaskGenerationTask->setTaskQueueBlock(true);
	QObject::connect(gameVersionJsonDownloadTaskGenerationTask, &QGSDownloadTask::finished, this, &QGSGameBuilder::eraseDownloadTask);
	QObject::connect(gameVersionJsonDownloadTaskGenerationTask, &QGSDownloadTask::finished, this, &QGSGameBuilder::slotDownloadTaskFinished);
	QGSThreadPool::getGlobalInstance().addTaskBack(gameVersionJsonDownloadTaskGenerationTask);

	auto * gameVersionDownloadTaskGenerationTask{ new GameVersionDownloadTaskGenerationTask{ this } };
	mTaskList.push_back(gameVersionDownloadTaskGenerationTask);
	QObject::connect(gameVersionDownloadTaskGenerationTask, &QGSDownloadTask::finished, this, &QGSGameBuilder::eraseDownloadTask);
	QObject::connect(gameVersionDownloadTaskGenerationTask, &QGSDownloadTask::finished, this, &QGSGameBuilder::slotDownloadTaskFinished);
	QGSThreadPool::getGlobalInstance().addTaskBack(gameVersionDownloadTaskGenerationTask);

	auto * libraryDownloadTasksGenerationTask{ new LibraryDownloadTasksGenerationTask{ this } };
	mTaskList.push_back(libraryDownloadTasksGenerationTask);
	QObject::connect(libraryDownloadTasksGenerationTask, &QGSDownloadTask::finished, this, &QGSGameBuilder::eraseDownloadTask);
	QObject::connect(libraryDownloadTasksGenerationTask, &QGSDownloadTask::finished, this, &QGSGameBuilder::slotDownloadTaskFinished);
	QGSThreadPool::getGlobalInstance().addTaskBack(libraryDownloadTasksGenerationTask);

	auto * assetIndexJsonDownloadTaskGenerationTask{ new AssetIndexJsonDownloadTaskGenerationTask{ this } };
	mTaskList.push_back(assetIndexJsonDownloadTaskGenerationTask);
	assetIndexJsonDownloadTaskGenerationTask->setTaskQueueBlock(true);
	QObject::connect(assetIndexJsonDownloadTaskGenerationTask, &QGSDownloadTask::finished, this, &QGSGameBuilder::eraseDownloadTask);
	QObject::connect(assetIndexJsonDownloadTaskGenerationTask, &QGSDownloadTask::finished, this, &QGSGameBuilder::slotDownloadTaskFinished);
	QGSThreadPool::getGlobalInstance().addTaskBack(assetIndexJsonDownloadTaskGenerationTask);

	auto * assetObjectDownloadTasksGenerationTask{ new AssetObjectDownloadTasksGenerationTask{ this } };
	mTaskList.push_back(assetObjectDownloadTasksGenerationTask);
	QObject::connect(assetObjectDownloadTasksGenerationTask, &QGSDownloadTask::finished, this, &QGSGameBuilder::eraseDownloadTask);
	QObject::connect(assetObjectDownloadTasksGenerationTask, &QGSDownloadTask::finished, this, &QGSGameBuilder::slotDownloadTaskFinished);
	QGSThreadPool::getGlobalInstance().addTaskBack(assetObjectDownloadTasksGenerationTask);
	*/
	//slotDownloadTaskFinished(nullptr);
}

void QGSGameBuilder::templateStop(QGSTask * task)
{
	QMutexLocker mutexLocker{ &mMutex };

	for (auto & downloadTask : mTaskList)
	{
		downloadTask->stop();
	}
}

void QGSGameBuilder::templateCancel(QGSTask * task)
{
	QMutexLocker mutexLocker{ &mMutex };

	for (auto & downloadTask : mTaskList)
	{
		downloadTask->cancel();
	}
}

void QGSGameBuilder::slotDownloadTaskStarted(QGSTask * task)
{

}

void QGSGameBuilder::slotDownloadTaskFinished(QGSTask * task)
{
	QMutexLocker mutexLocker{ &mMutex };
	
	if (mTaskList.isEmpty())
	{
		mutexLocker.unlock();

		emit finished(this);
	}
}

void QGSGameBuilder::slotDownloadTaskStoped(QGSTask * task)
{

}

void QGSGameBuilder::slotDownloadTaskCanceled(QGSTask * task)
{

}

void QGSGameBuilder::slotDownloadTaskError(QGSNetworkError error, QGSTask * task)
{

}

void QGSGameBuilder::initDownloadTasks()
{
	auto * gameVersionJsonDownloadTask{ initGameVersionJsonDownloadTask() };
	if (gameVersionJsonDownloadTask)
	{
		QObject::connect(gameVersionJsonDownloadTask, &QGSDownloadTask::finished, [=]()
		{
			if (initGameVersionDownloadTask() && initLibraryDownloadTasks());

			auto * assetIndexJsonDownloadTask{ initAssetIndexJsonDownloadTask() };

			QObject::connect(assetIndexJsonDownloadTask, &QGSDownloadTask::finished, [=]()
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

				slotDownloadTaskFinished(nullptr);
			});
		});
	}

	slotDownloadTaskFinished(nullptr);
}

QGSDownloadTask * QGSGameBuilder::initGameVersionJsonDownloadTask()
{
	QGSDownloadTask * downloadTask{ nullptr };

	downloadTask = mDownloadTaskFactoryPtr->generateGameVersionJsonDownloadTask(mVersionInfo, *mGameDirectoryPtr);
	if (!downloadTask)
	{
		emit error(this);
		emit downloadTaskDownloadError(QGSNetworkError{ QNetworkReply::NetworkError::NoError, "Generating game version json download task failed!" },
			downloadTask);
		mLastErrorString = "Generating game version json download task failed!";

		return nullptr;
	}
	mTaskList.push_back(downloadTask);
	QObject::connect(downloadTask, &QGSDownloadTask::started, this, &QGSGameBuilder::downloadTaskStarted);
	QObject::connect(downloadTask, &QGSDownloadTask::finished, this, &QGSGameBuilder::downloadTaskFinished);
	QObject::connect(downloadTask, &QGSDownloadTask::stoped, this, &QGSGameBuilder::downloadTaskStoped);
	QObject::connect(downloadTask, &QGSDownloadTask::canceled, this, &QGSGameBuilder::downloadTaskCanceled);
	QObject::connect(downloadTask, &QGSDownloadTask::downloadError, this, &QGSGameBuilder::downloadTaskDownloadError);
	QObject::connect(downloadTask, &QGSDownloadTask::error, this, &QGSGameBuilder::downloadTaskError);
	QObject::connect(downloadTask, &QGSDownloadTask::finished, this, &QGSGameBuilder::eraseDownloadTask);
	QGSThreadPool::getGlobalInstance().addTaskBack(downloadTask);

	return downloadTask;
}

bool QGSGameBuilder::initGameVersionDownloadTask()
{
	if (!mFileOverride)
	{
		QSharedPointer<QFile> gameVersionJarFile{ mGameDirectoryPtr->generateGameVersionJarFile(mVersionInfo.getId()) };
		if (gameVersionJarFile->exists())
		{
			return true;
		}
	}

	QGSDownloadTask * downloadTask{ nullptr };

	auto & version{ mGameDirectoryPtr->getVersion(mVersionInfo) };
	downloadTask = mDownloadTaskFactoryPtr->generateGameVersionDownloadTask(version, *mGameDirectoryPtr, "client");
	if (!downloadTask)
	{
		emit error(this);
		emit downloadTaskDownloadError(QGSNetworkError{ QNetworkReply::NetworkError::NoError, "Generating game version download task failed!" },
			downloadTask);
		mLastErrorString = "Generating game version download task failed!";

		return false;
	}
	mTaskList.push_back(downloadTask);
	QObject::connect(downloadTask, &QGSDownloadTask::started, this, &QGSGameBuilder::downloadTaskStarted);
	QObject::connect(downloadTask, &QGSDownloadTask::finished, this, &QGSGameBuilder::downloadTaskFinished);
	QObject::connect(downloadTask, &QGSDownloadTask::stoped, this, &QGSGameBuilder::downloadTaskStoped);
	QObject::connect(downloadTask, &QGSDownloadTask::canceled, this, &QGSGameBuilder::downloadTaskCanceled);
	QObject::connect(downloadTask, &QGSDownloadTask::downloadError, this, &QGSGameBuilder::downloadTaskDownloadError);
	QObject::connect(downloadTask, &QGSDownloadTask::error, this, &QGSGameBuilder::downloadTaskError);
	QObject::connect(downloadTask, &QGSDownloadTask::finished, this, &QGSGameBuilder::eraseDownloadTask);
	QObject::connect(downloadTask, &QGSDownloadTask::finished, this, &QGSGameBuilder::slotDownloadTaskFinished);
	QGSThreadPool::getGlobalInstance().addTaskBack(downloadTask);

	return true;
}

bool QGSGameBuilder::initLibraryDownloadTasks()
{
	QList<QGSLibrary> libraryList;
	try
	{
		libraryList = mGameDirectoryPtr->getVersion(mVersionInfo).getLibraries();
	}
	catch (const QGSExceptionVersionNotFound & exception)
	{
		emit error(this);
		mLastErrorString = "Game version:" + mVersionInfo.getId() + "not found!";

		return nullptr;
	}

	QGSDownloadTask * downloadTask{ nullptr };

	for (auto & i : libraryList)
	{
		if (!mFileOverride)
		{
			QSharedPointer<QFile> libraryFile{ mGameDirectoryPtr->generateLibraryFile(i) };
			if (libraryFile->exists())
			{
				continue;
			}
		}

		downloadTask = mDownloadTaskFactoryPtr->generateLibraryDownloadTask(i, *mGameDirectoryPtr);
		if (!downloadTask)
		{
			emit error(this);
			emit downloadTaskDownloadError(QGSNetworkError{ QNetworkReply::NetworkError::NoError, "Generating library download task failed!" },
				downloadTask);
			mLastErrorString = "Generating library download task failed!";

			return false;
		}
		mTaskList.push_back(downloadTask);
		QObject::connect(downloadTask, &QGSDownloadTask::started, this, &QGSGameBuilder::downloadTaskStarted);
		QObject::connect(downloadTask, &QGSDownloadTask::finished, this, &QGSGameBuilder::downloadTaskFinished);
		QObject::connect(downloadTask, &QGSDownloadTask::stoped, this, &QGSGameBuilder::downloadTaskStoped);
		QObject::connect(downloadTask, &QGSDownloadTask::canceled, this, &QGSGameBuilder::downloadTaskCanceled);
		QObject::connect(downloadTask, &QGSDownloadTask::downloadError, this, &QGSGameBuilder::downloadTaskDownloadError);
		QObject::connect(downloadTask, &QGSDownloadTask::error, this, &QGSGameBuilder::downloadTaskError);
		QObject::connect(downloadTask, &QGSDownloadTask::finished, this, &QGSGameBuilder::eraseDownloadTask);
		QObject::connect(downloadTask, &QGSDownloadTask::finished, this, &QGSGameBuilder::slotDownloadTaskFinished);
		QGSThreadPool::getGlobalInstance().addTaskBack(downloadTask);
	}

	return true;
}

QGSDownloadTask *  QGSGameBuilder::initAssetIndexJsonDownloadTask()
{
	QGSDownloadTask * downloadTask{ nullptr };

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
		emit downloadTaskDownloadError(QGSNetworkError{ QNetworkReply::NetworkError::NoError, "Generating asset index json download task failed!" },
			downloadTask);
		mLastErrorString = "Generating asset index json download task failed!";

		return nullptr;
	}
	mTaskList.push_back(downloadTask);
	QObject::connect(downloadTask, &QGSDownloadTask::started, this, &QGSGameBuilder::downloadTaskStarted);
	QObject::connect(downloadTask, &QGSDownloadTask::finished, this, &QGSGameBuilder::downloadTaskFinished);
	QObject::connect(downloadTask, &QGSDownloadTask::stoped, this, &QGSGameBuilder::downloadTaskStoped);
	QObject::connect(downloadTask, &QGSDownloadTask::canceled, this, &QGSGameBuilder::downloadTaskCanceled);
	QObject::connect(downloadTask, &QGSDownloadTask::downloadError, this, &QGSGameBuilder::downloadTaskDownloadError);
	QObject::connect(downloadTask, &QGSDownloadTask::error, this, &QGSGameBuilder::downloadTaskError);
	QObject::connect(downloadTask, &QGSDownloadTask::finished, this, &QGSGameBuilder::eraseDownloadTask);
	QGSThreadPool::getGlobalInstance().addTaskBack(downloadTask);

	return downloadTask;
}

bool QGSGameBuilder::initAssetObjectDownloadTasks()
{
	auto && assetObjectMap{ mAssetIndexInfo.getAssetObjectMap() };
	QGSDownloadTask * downloadTask{ nullptr };

	for (auto & i : assetObjectMap)
	{
		if (!mFileOverride)
		{
			QSharedPointer<QFile> libraryFile{ mGameDirectoryPtr->generateAssetObjectFile(i) };
			if (libraryFile->exists())
			{
				continue;
			}
		}

		downloadTask = mDownloadTaskFactoryPtr->generateAssetObjectDownloadTask(i, *mGameDirectoryPtr);
		if (!downloadTask)
		{
			emit error(this);
			emit downloadTaskDownloadError(QGSNetworkError{ QNetworkReply::NetworkError::NoError, "Generating asset object download task failed!" },
				downloadTask);
			mLastErrorString = "Generating asset object download task failed!";

			return false;
		}
		mTaskList.push_back(downloadTask);
		QObject::connect(downloadTask, &QGSDownloadTask::started, this, &QGSGameBuilder::downloadTaskStarted);
		QObject::connect(downloadTask, &QGSDownloadTask::finished, this, &QGSGameBuilder::downloadTaskFinished);
		QObject::connect(downloadTask, &QGSDownloadTask::stoped, this, &QGSGameBuilder::downloadTaskStoped);
		QObject::connect(downloadTask, &QGSDownloadTask::canceled, this, &QGSGameBuilder::downloadTaskCanceled);
		QObject::connect(downloadTask, &QGSDownloadTask::downloadError, this, &QGSGameBuilder::downloadTaskDownloadError);
		QObject::connect(downloadTask, &QGSDownloadTask::error, this, &QGSGameBuilder::downloadTaskError);
		QObject::connect(downloadTask, &QGSDownloadTask::finished, this, &QGSGameBuilder::eraseDownloadTask);
		QObject::connect(downloadTask, &QGSDownloadTask::finished, this, &QGSGameBuilder::slotDownloadTaskFinished);
		QGSThreadPool::getGlobalInstance().addTaskBack(downloadTask);
	}

	return true;
}

void QGSGameBuilder::eraseDownloadTask(QGSTask * downloadTask)
{
	if (!downloadTask)
	{
		return;
	}
	QMutexLocker mutexLocker{ &mMutex };
	for (auto it = mTaskList.begin(); it != mTaskList.end(); it++)
	{
		if (*it == downloadTask)
		{
			mTaskList.erase(it);
			break;
		}
	}
}
