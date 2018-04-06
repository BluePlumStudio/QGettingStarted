#include <QCoreApplication>

#include "QGSGameBuilder.h"
#include "../Util/QGSExceptionJsonPraseError.h"
#include "../Util/QGSExceptionVersionNotFound.h"
#include "../Util/QGSExceptionIO.h"
#include "../Util/QGSExceptionInvalidValue.h"

/**/

QGSGameBuilder::QGSGameBuilder(QGSGameVersionInfo & versionInfo, QGSGameDirectory * gameDirectory, QGSDownloadTaskFactory * downloadTaskFactory, QObject * parent)
	:QGSIBuilder(parent), 
	//mTimerPtr(nullptr),
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

QGSGameBuilder::~QGSGameBuilder()
{	
	QMutexLocker mutexLocker(&mMutex);

	for (auto & task : mTaskList)
	{
		task->deleteLater();
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
	
	mMutex.unlock();

	initDownloadTasks();
}

void QGSGameBuilder::templateStop(QGSTask * task)
{
	QMutexLocker mutexLocker(&mMutex);

	for (auto & downloadTask : mTaskList)
	{
		downloadTask->stop();
	}

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
}

void QGSGameBuilder::slotDownloadTaskDownloadProgress(qint64 bytesReceived, qint64 bytesTotal, QGSTask * task)
{
	auto * downloadTask(dynamic_cast<QGSDownloadTask *>(task));
	auto && downloadInfo(downloadTask->getDownloadInfo());

	emit downloadTaskDownloadProgress(bytesReceived, bytesTotal, downloadInfo);
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

			if (assetIndexJsonDownloadTask)
			{
				QObject::connect(assetIndexJsonDownloadTask, &QGSDownloadTask::finished, this, [=]()
				{
					QGSAssetIndexInfoFactory assetIndexversionInfoFactory;

					if (!assetIndexJsonDownloadTask->getTargetFile()->open(QIODevice::ReadOnly))
					{
						emit error(this);
						mLastErrorString = "Failed to open asset index json file!";

						return;
					}

					try
					{
						mAssetIndexInfo = assetIndexversionInfoFactory.createAssetIndexInfo(assetIndexJsonDownloadTask->getTargetFile()->readAll());
					}
					catch (const QGSExceptionJsonPraseError & exception)
					{
						emit error(this);
						mLastErrorString = "Failed to prase asset index json!";

						return;
					}

					if (initAssetObjectDownloadTasks());

					slotFinished(nullptr);

				});

			}

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
		mLastErrorString = "Failed to generate game version json download task!";

		return nullptr;
	}
	//mTaskList.push_back(downloadTask);
	QObject::connect(downloadTask, &QGSDownloadTask::started, this, &QGSGameBuilder::slotDownloadTaskStarted);
	QObject::connect(downloadTask, &QGSDownloadTask::finished, this, &QGSGameBuilder::slotDownloadTaskFinished);
	QObject::connect(downloadTask, &QGSDownloadTask::finished, downloadTask, &QGSDownloadTask::deleteLater);
	QObject::connect(downloadTask, &QGSDownloadTask::stoped, this, &QGSGameBuilder::slotDownloadTaskStoped);
	QObject::connect(downloadTask, &QGSDownloadTask::canceled, this, &QGSGameBuilder::slotDownloadTaskCanceled);
	QObject::connect(downloadTask, &QGSDownloadTask::canceled, downloadTask, &QGSDownloadTask::deleteLater);
	QObject::connect(downloadTask, &QGSDownloadTask::downloadProgress, this, &QGSGameBuilder::slotDownloadTaskDownloadProgress);
	QObject::connect(downloadTask, &QGSDownloadTask::downloadError, this, &QGSGameBuilder::slotDownloadTaskDownloadError);
	QObject::connect(downloadTask, &QGSDownloadTask::error, this, &QGSGameBuilder::slotDownloadTaskError);
	QObject::connect(downloadTask, &QGSDownloadTask::error, downloadTask, &QGSDownloadTask::deleteLater);
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
		mLastErrorString = "Failed to generate game version download task!";

		return false;
	}
	mTaskList.push_back(downloadTask);
	QObject::connect(downloadTask, &QGSDownloadTask::started, this, &QGSGameBuilder::slotDownloadTaskStarted);
	QObject::connect(downloadTask, &QGSDownloadTask::finished, this, &QGSGameBuilder::slotDownloadTaskFinished);
	QObject::connect(downloadTask, &QGSDownloadTask::finished, this, &QGSGameBuilder::slotEraseDownloadTask);
	QObject::connect(downloadTask, &QGSDownloadTask::stoped, this, &QGSGameBuilder::slotDownloadTaskStoped);
	QObject::connect(downloadTask, &QGSDownloadTask::canceled, this, &QGSGameBuilder::slotDownloadTaskCanceled);
	QObject::connect(downloadTask, &QGSDownloadTask::canceled, this, &QGSGameBuilder::slotEraseDownloadTask);
	QObject::connect(downloadTask, &QGSDownloadTask::downloadProgress, this, &QGSGameBuilder::slotDownloadTaskDownloadProgress);
	QObject::connect(downloadTask, &QGSDownloadTask::downloadError, this, &QGSGameBuilder::slotDownloadTaskDownloadError);
	QObject::connect(downloadTask, &QGSDownloadTask::error, this, &QGSGameBuilder::slotDownloadTaskError);
	QObject::connect(downloadTask, &QGSDownloadTask::error, this, &QGSGameBuilder::slotEraseDownloadTask);
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
		QObject::connect(downloadTask, &QGSDownloadTask::finished, this, &QGSGameBuilder::slotEraseDownloadTask);
		QObject::connect(downloadTask, &QGSDownloadTask::stoped, this, &QGSGameBuilder::slotDownloadTaskStoped);
		QObject::connect(downloadTask, &QGSDownloadTask::canceled, this, &QGSGameBuilder::slotDownloadTaskCanceled);
		QObject::connect(downloadTask, &QGSDownloadTask::canceled, this, &QGSGameBuilder::slotEraseDownloadTask);
		QObject::connect(downloadTask, &QGSDownloadTask::downloadProgress, this, &QGSGameBuilder::slotDownloadTaskDownloadProgress);
		QObject::connect(downloadTask, &QGSDownloadTask::downloadError, this, &QGSGameBuilder::slotDownloadTaskDownloadError);
		QObject::connect(downloadTask, &QGSDownloadTask::error, this, &QGSGameBuilder::slotDownloadTaskError);
		QObject::connect(downloadTask, &QGSDownloadTask::error, this, &QGSGameBuilder::slotEraseDownloadTask);
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
		mLastErrorString = "Failed to generate asset index json download task!";

		return nullptr;
	}
	//mTaskList.push_back(downloadTask);
	QObject::connect(downloadTask, &QGSDownloadTask::started, this, &QGSGameBuilder::slotDownloadTaskStarted);
	QObject::connect(downloadTask, &QGSDownloadTask::finished, this, &QGSGameBuilder::slotDownloadTaskFinished);
	QObject::connect(downloadTask, &QGSDownloadTask::finished, downloadTask, &QGSDownloadTask::deleteLater);
	QObject::connect(downloadTask, &QGSDownloadTask::stoped, this, &QGSGameBuilder::slotDownloadTaskStoped);
	QObject::connect(downloadTask, &QGSDownloadTask::canceled, this, &QGSGameBuilder::slotDownloadTaskCanceled);
	QObject::connect(downloadTask, &QGSDownloadTask::canceled, downloadTask, &QGSDownloadTask::deleteLater);
	QObject::connect(downloadTask, &QGSDownloadTask::downloadProgress, this, &QGSGameBuilder::slotDownloadTaskDownloadProgress);
	QObject::connect(downloadTask, &QGSDownloadTask::downloadError, this, &QGSGameBuilder::slotDownloadTaskDownloadError);
	QObject::connect(downloadTask, &QGSDownloadTask::error, this, &QGSGameBuilder::slotDownloadTaskError);
	QObject::connect(downloadTask, &QGSDownloadTask::error, downloadTask, &QGSDownloadTask::deleteLater);
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
			mLastErrorString = "Failed to generate asset object download task!";

			return false;
		}
		mTaskList.push_back(downloadTask);
		QObject::connect(downloadTask, &QGSDownloadTask::started, this, &QGSGameBuilder::slotDownloadTaskStarted);
		QObject::connect(downloadTask, &QGSDownloadTask::finished, this, &QGSGameBuilder::slotDownloadTaskFinished);
		QObject::connect(downloadTask, &QGSDownloadTask::finished, this, &QGSGameBuilder::slotEraseDownloadTask);
		QObject::connect(downloadTask, &QGSDownloadTask::stoped, this, &QGSGameBuilder::slotDownloadTaskStoped);
		QObject::connect(downloadTask, &QGSDownloadTask::canceled, this, &QGSGameBuilder::slotDownloadTaskCanceled);
		QObject::connect(downloadTask, &QGSDownloadTask::canceled, this, &QGSGameBuilder::slotEraseDownloadTask);
		QObject::connect(downloadTask, &QGSDownloadTask::downloadProgress, this, &QGSGameBuilder::slotDownloadTaskDownloadProgress);
		QObject::connect(downloadTask, &QGSDownloadTask::downloadError, this, &QGSGameBuilder::slotDownloadTaskDownloadError);
		QObject::connect(downloadTask, &QGSDownloadTask::error, this, &QGSGameBuilder::slotDownloadTaskError);
		QObject::connect(downloadTask, &QGSDownloadTask::error, this, &QGSGameBuilder::slotEraseDownloadTask);
		mThreadPool.addTaskBack(downloadTask);
	}

	return true;
}

void QGSGameBuilder::slotEraseDownloadTask(QGSTask * downloadTask)
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
			downloadTask->deleteLater();
			break;
		}
	}

	slotFinished(downloadTask);
}

void QGSGameBuilder::slotFinished(QGSTask * downloadTask)
{
	if (!mTaskList.size())
	{
		emit finished(this);
	}
}
