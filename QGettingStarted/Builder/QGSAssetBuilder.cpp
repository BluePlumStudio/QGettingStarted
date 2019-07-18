#include "QGSAssetBuilder.h"
#include "../Util/QGSExceptionJsonPraseError.h"
#include "../Util/QGSExceptionVersionNotFound.h"
#include "../Util/QGSExceptionIO.h"
#include "../Util/QGSExceptionInvalidValue.h"
#include "QGSAssetIndexJsonDownloadTaskGenerationTask.h"
#include "QGSAssetObjectDownloadTaskGenerationTask.h"
/**/

static const QString SEPARATOR = QGSOperatingSystem::getInstance().getSeperator();

QGSAssetBuilder::QGSAssetBuilder(
	QGSThreadPoolManager * threadPoolManagerPtr,
	QGSGameVersionInfo & versionInfo, 
	QGSGameDirectory * gameDirectory, 
	QGSDownloadTaskFactory * downloadTaskFactory,
	QObject * parent)

	:QGSIBuilder(threadPoolManagerPtr, parent),
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

QGSAssetBuilder::~QGSAssetBuilder()
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

bool QGSAssetBuilder::isFileOverride()
{
	QMutexLocker mutexLocker(&mMutex);

	return mFileOverride;
}

QGSAssetBuilder & QGSAssetBuilder::setFileOverride(const bool fileOverride)
{
	QMutexLocker mutexLocker(&mMutex);

	mFileOverride = fileOverride;
	return *this;
}

int QGSAssetBuilder::getTaskListSize()
{
	QMutexLocker mutexLocker(&mMutex);

	return mTaskList.size();
}

void QGSAssetBuilder::templateStart(QGSTask * task)
{
	emit started(this);

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

void QGSAssetBuilder::templateStop(QGSTask * task)
{
	emit stoped(this);

	QMutexLocker mutexLocker(&mMutex);

	for (auto & task : mTaskList)
	{
		task->stop();
	}
}

void QGSAssetBuilder::templateCancel(QGSTask * task)
{
	emit canceled(this);

	QMutexLocker mutexLocker(&mMutex);

	for (auto & task : mTaskList)
	{
		task->cancel();
	}
}

void QGSAssetBuilder::slotDownloadTaskStarted(QGSTask * task)
{
	emit downloadTaskStarted(dynamic_cast<QGSDownloadTask *>(task));
}

void QGSAssetBuilder::slotDownloadTaskFinished(QGSTask * task)
{
	slotEraseTask(task);
	
	emit downloadTaskFinished(dynamic_cast<QGSDownloadTask *>(task));

	slotFinished();
}

void QGSAssetBuilder::slotDownloadTaskStoped(QGSTask * task)
{
	emit downloadTaskStoped(dynamic_cast<QGSDownloadTask *>(task));
}

void QGSAssetBuilder::slotDownloadTaskCanceled(QGSTask * task)
{
	slotEraseTask(task);

	emit downloadTaskCanceled(dynamic_cast<QGSDownloadTask *>(task));

	//slotFinished();
}

void QGSAssetBuilder::slotDownloadTaskDownloadProgress(qint64 bytesReceived, qint64 bytesTotal, QGSTask * task)
{
	emit downloadTaskDownloadProgress(bytesReceived, bytesTotal, dynamic_cast<QGSDownloadTask *>(task));
}

void QGSAssetBuilder::slotDownloadTaskDownloadError(QGSNetworkError error, QGSTask * task)
{
	emit downloadTaskDownloadError(error, dynamic_cast<QGSDownloadTask *>(task));
}

void QGSAssetBuilder::slotDownloadTaskError(QGSTask * task)
{
	slotEraseTask(task);

	emit downloadTaskError(dynamic_cast<QGSDownloadTask *>(task));

	slotFinished();
}

void QGSAssetBuilder::slotEraseTask(QGSTask * task)
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

void QGSAssetBuilder::slotFinished()
{
	if (!mTaskList.size())
	{
		if (mAssetIndexInfo.getVirtual())
		{
			auto && assetObjectMap(mAssetIndexInfo.getAssetObjectMap());
			QDir baseDir(mGameDirectoryPtr->getBaseDir().absolutePath() + SEPARATOR + "assets" + SEPARATOR + "virtual" + SEPARATOR + "legacy");

			for (auto & i : assetObjectMap)
			{
				QSharedPointer<QFile> originalFile (mGameDirectoryPtr->generateAssetObjectFile(i));
				QFile targetFile(baseDir.absolutePath() + SEPARATOR + i.getPath());

				if (targetFile.exists())
				{
					if (!mFileOverride)
					{
						continue;
					}
					if (!targetFile.remove())
					{
						throw QGSExceptionIO(targetFile.fileName());
					}
				}
				else
				{
					if (!baseDir.mkpath(QFileInfo(targetFile).dir().absolutePath()))
					{
						throw QGSExceptionIO(targetFile.fileName());
					}
				}

				if (originalFile->exists() && !QFile::copy(originalFile->fileName(), targetFile.fileName()))
				{
					throw QGSExceptionIO(originalFile->fileName());
				}

			}
		}
		emit finished(this);
	}
}

void QGSAssetBuilder::initDownloadTasks()
{
	initAssetObjectDownloadTaskGenerationTask(initAssetIndexJsonDownloadTaskGenerationTask());
}

QGSAssetIndexJsonDownloadTaskGenerationTask * QGSAssetBuilder::initAssetIndexJsonDownloadTaskGenerationTask()
{
	auto * generationTask(new QGSAssetIndexJsonDownloadTaskGenerationTask(this, mFileOverride));

	QObject::connect(generationTask, &QGSAssetIndexJsonDownloadTaskGenerationTask::finished, this, &QGSAssetBuilder::slotEraseTask);
	QObject::connect(generationTask, &QGSAssetIndexJsonDownloadTaskGenerationTask::finished, this, &QGSAssetBuilder::slotFinished);

	QObject::connect(generationTask, &QGSAssetIndexJsonDownloadTaskGenerationTask::canceled, this, &QGSAssetBuilder::slotEraseTask);
	//QObject::connect(generationTask, &QGSAssetIndexJsonDownloadTaskGenerationTask::canceled, this, &QGSAssetBuilder::slotFinished);

	QObject::connect(generationTask, &QGSAssetIndexJsonDownloadTaskGenerationTask::error, this, &QGSAssetBuilder::slotEraseTask);
	QObject::connect(generationTask, &QGSAssetIndexJsonDownloadTaskGenerationTask::error, this, &QGSAssetBuilder::error);

	mTaskList.push_back(generationTask);
	mTaskDeletedLaterList.push_back(generationTask);
	mThreadPoolManagerPtr->addTaskBack(generationTask);

	return generationTask;
}

QGSAssetObjectDownloadTaskGenerationTask * QGSAssetBuilder::initAssetObjectDownloadTaskGenerationTask(QGSAssetIndexJsonDownloadTaskGenerationTask * jsonDownloadTaskGenerationTask)
{
	auto * generationTask(new QGSAssetObjectDownloadTaskGenerationTask(
		this,
		jsonDownloadTaskGenerationTask->mSharedMutex,
		jsonDownloadTaskGenerationTask->mAssetIndexJsonDownloadTaskEnded,
		mFileOverride));

	QObject::connect(generationTask, &QGSAssetObjectDownloadTaskGenerationTask::finished, this, &QGSAssetBuilder::slotEraseTask);
	QObject::connect(generationTask, &QGSAssetObjectDownloadTaskGenerationTask::finished, this, &QGSAssetBuilder::slotFinished);

	QObject::connect(generationTask, &QGSAssetObjectDownloadTaskGenerationTask::canceled, this, &QGSAssetBuilder::slotEraseTask);
	//QObject::connect(generationTask, &QGSAssetObjectDownloadTaskGenerationTask::canceled, this, &QGSAssetBuilder::slotFinished);

	QObject::connect(generationTask, &QGSAssetObjectDownloadTaskGenerationTask::error, this, &QGSAssetBuilder::slotEraseTask);
	QObject::connect(generationTask, &QGSAssetObjectDownloadTaskGenerationTask::error, this, &QGSAssetBuilder::error);

	mTaskList.push_back(generationTask);
	mTaskDeletedLaterList.push_back(generationTask);
	mThreadPoolManagerPtr->addTaskBack(generationTask);

	return generationTask;
}
