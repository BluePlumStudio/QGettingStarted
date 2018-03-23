#include "QGSGameBuilder.h"
#include "../Util/QGSExceptionJsonPraseError.h"
#include "../Util/QGSExceptionVersionNotFound.h"
#include "../Util/QGSExceptionFileIO.h"
#include "../Util/QGSExceptionInvalidValue.h"

QGSGameBuilder::QGSGameBuilder(QGSGameVersionInfo & versionInfo, QGSGameDirectory * gameDirectory, QGSDownloadTaskFactory * downloadTaskFactory)
	:mVersionInfo(versionInfo), mGameDirectoryPtr(gameDirectory), mDownloadTaskFactoryPtr(downloadTaskFactory), mFileOverride(true)
{
	if (!mGameDirectoryPtr || !mDownloadTaskFactoryPtr)
	{
		throw QGSExceptionInvalidValue();
	}
}

QGSGameBuilder::~QGSGameBuilder()
{
	QMutexLocker mutexLocker{ &mMutex };
	
	for (auto & task : mDownloadTaskList)
	{
		task->deleteLater();
	}
}

bool QGSGameBuilder::isFileOverride()
{
	return mFileOverride;
}

QGSGameBuilder & QGSGameBuilder::setFileOverride(const bool fileOverride)
{
	mFileOverride = fileOverride;
	return *this;
}

void QGSGameBuilder::templateStart(QGSTask * task)
{
	QMutexLocker mutexLocker{ &mMutex };

	emit started(this);

	if (mDownloadTaskList.size())
	{
		for (auto & downloadTask : mDownloadTaskList)
		{
			downloadTask->start();
		}
	}
	else
	{
		QObject::connect(initGameVersionJsonDownloadTask(), &QGSDownloadTask::finished, [=]()
		{
			if (initGameVersionDownloadTask() && initLibraryDownloadTask())
			{

			}
		});
	}
}

void QGSGameBuilder::templateStop(QGSTask * task)
{
	QMutexLocker mutexLocker{ &mMutex };

	for (auto & downloadTask : mDownloadTaskList)
	{
		downloadTask->stop();
	}
}

void QGSGameBuilder::templateCancel(QGSTask * task)
{
	QMutexLocker mutexLocker{ &mMutex };

	for (auto & downloadTask : mDownloadTaskList)
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
	
	if (mDownloadTaskList.isEmpty())
	{
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

QGSDownloadTask * QGSGameBuilder::initGameVersionJsonDownloadTask()
{
	QGSDownloadTask * downloadTask{ nullptr };

	downloadTask = mDownloadTaskFactoryPtr->generateGameVersionJsonDownloadTask(mVersionInfo, *mGameDirectoryPtr);
	if (!downloadTask)
	{
		emit error(this);
		emit downloadTaskDownloadError(QGSNetworkError{ QNetworkReply::NetworkError::NoError, "Generating game version json download task failed!" },
			downloadTask);

		return nullptr;
	}
	downloadTask->setTaskQueueBlock(true);
	mDownloadTaskList.push_back(downloadTask);
	QObject::connect(downloadTask, &QGSDownloadTask::started, this, &QGSGameBuilder::downloadTaskStarted);
	QObject::connect(downloadTask, &QGSDownloadTask::finished, this, &QGSGameBuilder::downloadTaskFinished);
	QObject::connect(downloadTask, &QGSDownloadTask::stoped, this, &QGSGameBuilder::downloadTaskStoped);
	QObject::connect(downloadTask, &QGSDownloadTask::canceled, this, &QGSGameBuilder::downloadTaskCanceled);
	QObject::connect(downloadTask, &QGSDownloadTask::downloadError, this, &QGSGameBuilder::downloadTaskDownloadError);
	QObject::connect(downloadTask, &QGSDownloadTask::error, this, &QGSGameBuilder::downloadTaskError);
	QObject::connect(downloadTask, &QGSDownloadTask::finished, this, &QGSGameBuilder::eraseDownloadTask);
	QGSThreadPool::getGlobalInstance().addTask(downloadTask);

	return downloadTask;
}

bool QGSGameBuilder::initGameVersionDownloadTask()
{
	if (mFileOverride)
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

		return false;
	}
	mDownloadTaskList.push_back(downloadTask);
	QObject::connect(downloadTask, &QGSDownloadTask::started, this, &QGSGameBuilder::downloadTaskStarted);
	QObject::connect(downloadTask, &QGSDownloadTask::finished, this, &QGSGameBuilder::downloadTaskFinished);
	QObject::connect(downloadTask, &QGSDownloadTask::stoped, this, &QGSGameBuilder::downloadTaskStoped);
	QObject::connect(downloadTask, &QGSDownloadTask::canceled, this, &QGSGameBuilder::downloadTaskCanceled);
	QObject::connect(downloadTask, &QGSDownloadTask::downloadError, this, &QGSGameBuilder::downloadTaskDownloadError);
	QObject::connect(downloadTask, &QGSDownloadTask::error, this, &QGSGameBuilder::downloadTaskError);
	QObject::connect(downloadTask, &QGSDownloadTask::finished, this, &QGSGameBuilder::eraseDownloadTask);
	QObject::connect(downloadTask, &QGSDownloadTask::finished, this, &QGSGameBuilder::slotDownloadTaskFinished);
	QGSThreadPool::getGlobalInstance().addTask(downloadTask);

	return true;
}

bool QGSGameBuilder::initLibraryDownloadTask()
{
	auto && libraryList{ mGameDirectoryPtr->getVersion(mVersionInfo).getLibraries() };
	QGSDownloadTask * downloadTask{ nullptr };

	for (auto & i : libraryList)
	{
		if (mFileOverride)
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

			return false;
		}
		mDownloadTaskList.push_back(downloadTask);
		QObject::connect(downloadTask, &QGSDownloadTask::started, this, &QGSGameBuilder::downloadTaskStarted);
		QObject::connect(downloadTask, &QGSDownloadTask::finished, this, &QGSGameBuilder::downloadTaskFinished);
		QObject::connect(downloadTask, &QGSDownloadTask::stoped, this, &QGSGameBuilder::downloadTaskStoped);
		QObject::connect(downloadTask, &QGSDownloadTask::canceled, this, &QGSGameBuilder::downloadTaskCanceled);
		QObject::connect(downloadTask, &QGSDownloadTask::downloadError, this, &QGSGameBuilder::downloadTaskDownloadError);
		QObject::connect(downloadTask, &QGSDownloadTask::error, this, &QGSGameBuilder::downloadTaskError);
		QObject::connect(downloadTask, &QGSDownloadTask::finished, this, &QGSGameBuilder::eraseDownloadTask);
		QObject::connect(downloadTask, &QGSDownloadTask::finished, this, &QGSGameBuilder::slotDownloadTaskFinished);
		QGSThreadPool::getGlobalInstance().addTask(downloadTask);
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
	auto * task{ dynamic_cast<QGSDownloadTask *>(downloadTask) };
	mDownloadTaskList.removeAt(mDownloadTaskList.indexOf(task));
}
