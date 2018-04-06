#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include "QGSForgeBuilder.h"
#include "../Util/QGSFileTools.h"
#include "../Util/QGSExceptionJsonPraseError.h"
#include "../Util/QGSExceptionVersionNotFound.h"
#include "../Util/QGSExceptionIO.h"
#include "../Util/QGSExceptionInvalidValue.h"

static const QString SEPARATOR = QGSOperatingSystem::getInstance().getSeperator();

QGSForgeBuilder::QGSForgeBuilder(QGSForgeVersionInfo & versionInfo, QGSGameDirectory * gameDirectory, QGSDownloadTaskFactory * downloadTaskFactory, QObject * parent)
	:QGSIBuilder(parent), mVersionInfo(versionInfo), mGameDirectoryPtr(gameDirectory), mDownloadTaskFactoryPtr(downloadTaskFactory), mForgeDownloadTask(nullptr), mFileOverride(false)
{
	if (!mGameDirectoryPtr || !mDownloadTaskFactoryPtr)
	{
		throw QGSExceptionInvalidValue();
	}
}

QGSForgeBuilder::~QGSForgeBuilder()
{

	if (mForgeDownloadTask)
	{
		mForgeDownloadTask->deleteLater();
		mForgeDownloadTask = nullptr;
	}
}

bool QGSForgeBuilder::isFileOverride()
{
	QMutexLocker mutexLocker(&mMutex);

	return mFileOverride;
}

QGSForgeBuilder & QGSForgeBuilder::setFileOverride(const bool fileOverride)
{
	QMutexLocker mutexLocker(&mMutex);

	mFileOverride = fileOverride;
	return *this;
}

int QGSForgeBuilder::getTaskListSize()
{
	QMutexLocker mutexLocker(&mMutex);

	return mTaskList.size();
}

void QGSForgeBuilder::templateStart(QGSTask * task)
{
	emit started(this);
	
	if (mTaskList.size())
	{
		for (auto & downloadTask : mTaskList)
		{
			downloadTask->start();
		}

		return;
	}

	if (!initDownloadDirectory())
	{
		return;
	}

	if (!mFileOverride)
	{
		if (mForgeInstallerFile.exists())
		{
			if (!installForge())
			{
				emit error(this);
				emit installationError(this);

				return;
			}

			if (!initLibraryDownloadTasks());
			slotFinished(nullptr);

			return;

		}
	}

	initForgeDownloadTask();

	if (mForgeDownloadTask)
	{
		QObject::connect(mForgeDownloadTask, &QGSDownloadTask::finished, this, [=]()
		{
			mForgeDownloadTask->deleteLater();
			mForgeDownloadTask = nullptr;

			if (!installForge())
			{
				emit error(this);
				emit installationError(this);

				return;
			}

			if (!initLibraryDownloadTasks());
			slotFinished(nullptr);

		});
	}

}

void QGSForgeBuilder::templateStop(QGSTask * task)
{
	QMutexLocker mutexLocker(&mMutex);

	mForgeDownloadTask->cancel();

	for (auto & downloadTask : mTaskList)
	{
		downloadTask->stop();
	}

	emit stoped(this);
}

void QGSForgeBuilder::templateCancel(QGSTask * task)
{
	QMutexLocker mutexLocker(&mMutex);

	mForgeDownloadTask->cancel();

	for (auto & downloadTask : mTaskList)
	{
		downloadTask->cancel();
	}

	if (mForgeDownloadTask)
	{
		mForgeDownloadTask->deleteLater();
		mForgeDownloadTask = nullptr;
	}

	emit canceled(this);
}

void QGSForgeBuilder::slotDownloadTaskStarted(QGSTask * task)
{
	auto * downloadTask(dynamic_cast<QGSDownloadTask *>(task));
	auto && downloadInfo(downloadTask->getDownloadInfo());

	emit downloadTaskStarted(downloadInfo);
}

void QGSForgeBuilder::slotDownloadTaskFinished(QGSTask * task)
{
	auto * downloadTask(dynamic_cast<QGSDownloadTask *>(task));
	auto && downloadInfo(downloadTask->getDownloadInfo());

	emit downloadTaskFinished(downloadInfo);

	QMutexLocker mutexLocker(&mMutex);
	slotFinished(downloadTask);
	mutexLocker.unlock();
}

void QGSForgeBuilder::slotDownloadTaskStoped(QGSTask * task)
{
	auto * downloadTask(dynamic_cast<QGSDownloadTask *>(task));
	auto && downloadInfo(downloadTask->getDownloadInfo());

	emit downloadTaskStoped(downloadInfo);
}

void QGSForgeBuilder::slotDownloadTaskCanceled(QGSTask * task)
{
	auto * downloadTask(dynamic_cast<QGSDownloadTask *>(task));
	auto && downloadInfo(downloadTask->getDownloadInfo());

	emit downloadTaskCanceled(downloadInfo);

	QMutexLocker mutexLocker(&mMutex);
	slotFinished(downloadTask);
	mutexLocker.unlock();
}

void QGSForgeBuilder::slotDownloadTaskDownloadError(QGSNetworkError _error, QGSTask * task)
{
	auto * downloadTask(dynamic_cast<QGSDownloadTask *>(task));
	auto && downloadInfo(downloadTask->getDownloadInfo());
	auto && error(_error);

	emit downloadTaskDownloadError(error, downloadInfo);
}

void QGSForgeBuilder::slotDownloadTaskError(QGSTask * task)
{
	auto * downloadTask(dynamic_cast<QGSDownloadTask *>(task));
	auto && downloadInfo(downloadTask->getDownloadInfo());

	emit downloadTaskError(downloadInfo);

	QMutexLocker mutexLocker(&mMutex);
	slotFinished(downloadTask);
	mutexLocker.unlock();
}

void QGSForgeBuilder::slotDownloadTaskDownloadProgress(qint64 bytesReceived, qint64 bytesTotal, QGSTask * task)
{
	auto * downloadTask(dynamic_cast<QGSDownloadTask *>(task));
	auto && downloadInfo(downloadTask->getDownloadInfo());

	emit downloadTaskDownloadProgress(bytesReceived, bytesTotal, downloadInfo);
}

bool QGSForgeBuilder::initDownloadDirectory()
{
	mForgeDir = QDir(mGameDirectoryPtr->getBaseDir().absolutePath() + SEPARATOR + "forge");

	if (!mForgeDir.exists())
	{
		if (!mForgeDir.mkpath("./"))
		{
			//throw QGSExceptionIO(baseDir.absolutePath() + SEPARATOR + "forge");
			emit error(this);
			mLastErrorString = "Failed to make path:"+ mForgeDir.absolutePath();

			return false;
		}
	}

	mForgeInstallerFile.setFileName(mForgeDir.absolutePath() + SEPARATOR + "forge-installer.jar");
	
	return true;
}

QGSDownloadTask * QGSForgeBuilder::initForgeDownloadTask()
{
	QMutexLocker mutexLocker(&mMutex);

	mForgeDownloadTask = mDownloadTaskFactoryPtr->generateForgeDownloadTask(&mForgeInstallerFile, mVersionInfo.getMcversion(), mVersionInfo.getVersion(), "installer", "jar", mVersionInfo.getBranch());
	if (!mForgeDownloadTask)
	{
		emit error(this);
		mLastErrorString = "Failed to generate forge download task!";

		return nullptr;
	}
	mTaskList.push_back(mForgeDownloadTask);
	QObject::connect(mForgeDownloadTask, &QGSDownloadTask::started, this, &QGSForgeBuilder::slotDownloadTaskStarted);
	QObject::connect(mForgeDownloadTask, &QGSDownloadTask::finished, this, &QGSForgeBuilder::slotDownloadTaskFinished);
	QObject::connect(mForgeDownloadTask, &QGSDownloadTask::stoped, this, &QGSForgeBuilder::slotDownloadTaskStoped);
	QObject::connect(mForgeDownloadTask, &QGSDownloadTask::canceled, this, &QGSForgeBuilder::slotDownloadTaskCanceled);
	QObject::connect(mForgeDownloadTask, &QGSDownloadTask::downloadProgress, this, &QGSForgeBuilder::slotDownloadTaskDownloadProgress);
	QObject::connect(mForgeDownloadTask, &QGSDownloadTask::downloadError, this, &QGSForgeBuilder::slotDownloadTaskDownloadError);
	QObject::connect(mForgeDownloadTask, &QGSDownloadTask::error, this, &QGSForgeBuilder::slotDownloadTaskError);
	mThreadPool.addTaskBack(mForgeDownloadTask);

	return mForgeDownloadTask;
}

bool QGSForgeBuilder::installForge()
{
	auto && fileNameExtractedList(QGSFileTools::extractDirectory(mForgeInstallerFile.fileName(), mForgeDir.absolutePath()));

	if (fileNameExtractedList.isEmpty())
	{
		return false;
	}

	QFile installProfileJsonFile(mForgeDir.absolutePath() + SEPARATOR + "install_profile.json");
	if (!installProfileJsonFile.open(QIODevice::ReadOnly))
	{
		mLastErrorString = "Failed to open file:" + installProfileJsonFile.fileName();

		return false;
	}
	QJsonParseError jsonPraseError;
	auto && jsonDocument = QJsonDocument::fromJson(installProfileJsonFile.readAll(), &jsonPraseError);
	if (jsonPraseError.error != QJsonParseError::NoError)
	{
		QMutexLocker mutexLocker(&mMutex);

		mLastErrorString = "Failed to prase file:" + installProfileJsonFile.fileName();

		return false;
	}

	auto && jsonObject(jsonDocument.object());
	auto && installObeject(jsonObject.value("install").toObject());
	auto && target(installObeject.value("target").toString());
	auto && filePath(installObeject.value("filePath").toString());
	auto && path(installObeject.value("path").toString());

	path = path.left(path.indexOf(":")).replace(".", SEPARATOR) +
		SEPARATOR +
		path.mid(path.indexOf(":") + 1, path.lastIndexOf(":") - path.indexOf(":") - 1) +
		SEPARATOR +
		path.mid(path.lastIndexOf(":") + 1);

	auto && librariesDir(mGameDirectoryPtr->generateLibrariesDirectory());
	if (!librariesDir.exists("./" + path))
	{
		if (!librariesDir.mkpath("./" + path))
		{
			QMutexLocker mutexLocker(&mMutex);

			mLastErrorString = "Failed to make path:" + librariesDir.absolutePath() + SEPARATOR + path;

			return false;
		}
	}
	QFile universalFile(mForgeDir.absolutePath() + SEPARATOR + filePath);
	auto && newFileName(filePath.remove("-universal"));
	if (!librariesDir.exists("./" + path + SEPARATOR + newFileName))
	{
		QFile::remove(librariesDir.absolutePath() + SEPARATOR + path + SEPARATOR + newFileName);

		if (!universalFile.copy(librariesDir.absolutePath() + SEPARATOR + path + SEPARATOR + newFileName))
		{
			QMutexLocker mutexLocker(&mMutex);

			mLastErrorString = "Failed to copy file:" + librariesDir.absolutePath() + SEPARATOR + path + SEPARATOR + newFileName;

			return false;
		}
	}

	auto && versionsDir(mGameDirectoryPtr->generateVersionsDirectory());
	if (!versionsDir.exists("./" + target))
	{
		if (!versionsDir.mkdir("./" + target))
		{
			QMutexLocker mutexLocker(&mMutex);

			mLastErrorString = "Failed to make path:" + versionsDir.absolutePath();

			return false;
		}
	}
	auto && versionInfoObject(jsonObject.value("versionInfo").toObject());
	QFile versionJsonFile(versionsDir.absolutePath() + SEPARATOR + target + SEPARATOR + target + ".json");
	if (!versionJsonFile.open(QIODevice::WriteOnly | QIODevice::Truncate))
	{
		QMutexLocker mutexLocker(&mMutex);

		mLastErrorString = "Failed to open file:"+ versionJsonFile.fileName();

		return false;
	}
	versionJsonFile.write(QJsonDocument(versionInfoObject).toJson());
	auto * rootVersionFile(mGameDirectoryPtr->generateGameVersionJarFile(mVersionInfo.getMcversion()));
	rootVersionFile->copy(versionsDir.absolutePath() + SEPARATOR + target + SEPARATOR + target + ".jar");

	mVersionId = target;

	return true;
}

bool QGSForgeBuilder::initLibraryDownloadTasks()
{
	QMutexLocker mutexLocker(&mMutex);
	QList<QGSLibrary> libraryList;
	try
	{
		libraryList = mGameDirectoryPtr->getVersion(mVersionId).getLibraries();
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
		QObject::connect(downloadTask, &QGSDownloadTask::started, this, &QGSForgeBuilder::slotDownloadTaskStarted);
		QObject::connect(downloadTask, &QGSDownloadTask::finished, this, &QGSForgeBuilder::slotDownloadTaskFinished);
		QObject::connect(downloadTask, &QGSDownloadTask::stoped, this, &QGSForgeBuilder::slotDownloadTaskStoped);
		QObject::connect(downloadTask, &QGSDownloadTask::canceled, this, &QGSForgeBuilder::slotDownloadTaskCanceled);
		QObject::connect(downloadTask, &QGSDownloadTask::downloadProgress, this, &QGSForgeBuilder::slotDownloadTaskDownloadProgress);
		QObject::connect(downloadTask, &QGSDownloadTask::downloadError, this, &QGSForgeBuilder::slotDownloadTaskDownloadError);
		QObject::connect(downloadTask, &QGSDownloadTask::error, this, &QGSForgeBuilder::slotDownloadTaskError);
		mThreadPool.addTaskBack(downloadTask);
	}

	return true;
}

void QGSForgeBuilder::slotEraseDownloadTask(QGSTask * downloadTask)
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
			if (downloadTask != mForgeDownloadTask)
			{
				downloadTask->deleteLater();

			}
			break;
		}
	}
}

void QGSForgeBuilder::slotFinished(QGSTask * downloadTask)
{
	slotEraseDownloadTask(downloadTask);

	if (!mTaskList.size())
	{
		QGSFileTools::removeDirectory(mForgeDir.absolutePath());
		emit finished(this);
	}
}
