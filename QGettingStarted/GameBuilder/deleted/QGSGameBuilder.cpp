#include "QGSGameBuilder.h"
#include "../Util/QGSExceptionJsonPraseError.h"
#include "../Util/QGSExceptionVersionNotFound.h"
#include "../Util/QGSExceptionFileIO.h"

QGSGameBuilder::QGSGameBuilder(QGSIDownloadSource * downloadSource, QGSGameDirectory * gameDirectory, QObject * parent)
	:QGSIGameBuilder(downloadSource, gameDirectory, parent), mDownloadTaskFactoryPtr(new QGSDownloadTaskFactory{ downloadSource })
{

}


QGSGameBuilder::~QGSGameBuilder()
{

}

bool QGSGameBuilder::start(const GameVersionInfo & gameVersionInfo)
{

	return true;
}

bool QGSGameBuilder::cancel()
{
	return false;
}

QGSDownloadTask * QGSGameBuilder::generateGameVersionJsonDownloadTask(const GameVersionInfo & gameVersionInfo)
{
	QGSDownloadTask * downloadTask{ nullptr };

	downloadTask = mDownloadTaskFactoryPtr->generateGameVersionJsonDownloadTask(gameVersionInfo, *mGameDirectoryPtr);
	if (!downloadTask)
	{
		slotError("'generateGameVersionJsonDownloadTask' start failure!");
		return nullptr;
	}

	QObject::connect(downloadTask, &QGSDownloadTask::downloadProgress, this, &QGSGameBuilder::slotDownloadProgress);
	QObject::connect(downloadTask, &QGSDownloadTask::finished, this, &QGSGameBuilder::slotDownloadFinished);
	QObject::connect(downloadTask, &QGSDownloadTask::error, this, &QGSGameBuilder::slotDownloadError);
	QObject::connect(downloadTask, &QGSDownloadTask::timeout, this, &QGSGameBuilder::slotDownloadTimeout);
	/*
	QObject::connect(downloadTask, &QGSDownloadTask::finished, [=]()
	{
		downloadGameVersionJar(gameVersionInfo);
		downloadLibraries(gameVersionInfo);
	});
	*/
	return downloadTask;
}

QGSDownloadTask * QGSGameBuilder::generateGameVersionDownloadTask(const GameVersionInfo & gameVersionInfo)
{
	QGSDownloadTask * downloadTask{ nullptr };

	try
	{
		auto & version{ mGameDirectoryPtr->getVersion(gameVersionInfo.getId()) };
		downloadTask = mDownloadTaskFactoryPtr->generateGameVersionDownloadTask(version, *mGameDirectoryPtr, "client");
		if (!downloadTask)
		{
			slotError("'generateGameVersionDownloadTask' start failure!");
			return nullptr;
		}
	}
	catch (const QGSExceptionVersionNotFound & exception)
	{
		slotError("'downloadGameVersion' version not found!");
		downloadTask->deleteLater();
		return nullptr;
	}
	catch (const QGSExceptionFileIO & exception)
	{
		slotError("'downloadGameVersion' file IO error!");
		downloadTask->deleteLater();
		return nullptr;
	}
	catch (const QGSExceptionJsonPraseError & exception)
	{
		slotError("'downloadGameVersion' json prase error!");
		downloadTask->deleteLater();
		return nullptr;
	}
	catch (...)
	{
		slotError("'downloadGameVersion' unknown error!");
		downloadTask->deleteLater();
		return nullptr;
	}

	QObject::connect(downloadTask, &QGSDownloadTask::downloadProgress, this, &QGSGameBuilder::slotDownloadProgress);
	QObject::connect(downloadTask, &QGSDownloadTask::finished, this, &QGSGameBuilder::slotDownloadFinished);
	QObject::connect(downloadTask, &QGSDownloadTask::error, this, &QGSGameBuilder::slotDownloadError);
	QObject::connect(downloadTask, &QGSDownloadTask::timeout, this, &QGSGameBuilder::slotDownloadTimeout);
	/*
	QObject::connect(downloadTask, &QGSDownloadTask::finished, &mEventLoop, &QEventLoop::quit);
	mEventLoop.exec();
		*/
	return downloadTask;
}

QList<QGSDownloadTask *> QGSGameBuilder::generateLibrarDownloadTaskList(const GameVersionInfo & gameVersionInfo)
{
	QList<QGSDownloadTask *> ret;
	QGSDownloadTask * downloadTask{ nullptr };

	auto && libraryList{ mGameDirectoryPtr->getVersion(gameVersionInfo.getId()).getLibraries() };
	for (auto & library : libraryList)
	{
		downloadTask = mDownloadTaskFactoryPtr->generateLibraryDownloadTask(library, *mGameDirectoryPtr);
		if (!downloadTask)
		{
			slotError("'generateLibraryDownloadTask' start failure!");
			return ret;
		}

		QObject::connect(downloadTask, &QGSDownloadTask::downloadProgress, this, &QGSGameBuilder::slotDownloadProgress);
		QObject::connect(downloadTask, &QGSDownloadTask::finished, this, &QGSGameBuilder::slotDownloadFinished);
		QObject::connect(downloadTask, &QGSDownloadTask::error, this, &QGSGameBuilder::slotDownloadError);
		QObject::connect(downloadTask, &QGSDownloadTask::timeout, this, &QGSGameBuilder::slotDownloadTimeout);
		ret.push_back(downloadTask);
	}

	return ret;
}

QGSDownloadTask * QGSGameBuilder::generateAssetIndexJsonDownloadTask(const GameVersionInfo & gameVersionInfo)
{
	QGSDownloadTask * downloadTask{ nullptr };

	downloadTask = mDownloadTaskFactoryPtr->generateAssetIndexJsonDownloadTask(mGameDirectoryPtr->getVersion(gameVersionInfo.getId()).getAssetIndex(), *mGameDirectoryPtr);
	if (!downloadTask)
	{
		slotError("'generateAssetIndexJsonDownloadTask' start failure!");
		return nullptr;
	}

	QObject::connect(downloadTask, &QGSDownloadTask::downloadProgress, this, &QGSGameBuilder::slotDownloadProgress);
	QObject::connect(downloadTask, &QGSDownloadTask::finished, this, &QGSGameBuilder::slotDownloadFinished);
	QObject::connect(downloadTask, &QGSDownloadTask::error, this, &QGSGameBuilder::slotDownloadError);
	QObject::connect(downloadTask, &QGSDownloadTask::timeout, this, &QGSGameBuilder::slotDownloadTimeout);
	/*
	QObject::connect(downloadTask, &QGSDownloadTask::finished, [=]()
	{
		AssetIndexInfo assetIndexInfo;
		QGSAssetIndexInfoFactory versionInfoFactory;
		if (!downloadTask->getTargetFile()->open(QIODevice::ReadOnly))
		{
			slotError("'downloadAssetIndex' file IO error!");
		}

		try
		{
			assetIndexInfo = versionInfoFactory.createAssetIndexInfo(downloadTask->getTargetFile()->readAll());
		}
		catch (const QGSExceptionFileIO & exception)
		{
			slotError("'downloadAssetIndex' file IO error!");
			return;
		}
		catch (const QGSExceptionJsonPraseError & exception)
		{
			slotError("'downloadGameVersion' json prase error!");
			return;
		}
		catch (...)
		{
			slotError("'downloadGameVersion' unknown error!");
			return;
		}

		downloadAssetObjects(assetIndexInfo);
	});
	*/
	return downloadTask;
}

QList<QGSDownloadTask *>  QGSGameBuilder::generateAssetObjectDownloadTaskList(const AssetIndexInfo & assetIndexInfo)
{
	QList<QGSDownloadTask *> ret;
	QGSDownloadTask * downloadTask{ nullptr };

	auto && assetObjectMap{ assetIndexInfo.getAssetObjectMap() };
	for (auto & i : assetObjectMap)
	{
		downloadTask = mDownloadTaskFactoryPtr->generateAssetObjectDownloadTask(i, *mGameDirectoryPtr);
		if (!downloadTask)
		{
			slotError("'generateAssetObjectDownloadTask' start failure!");
			return ret;
		}

		QObject::connect(downloadTask, &QGSDownloadTask::downloadProgress, this, &QGSGameBuilder::slotDownloadProgress);
		QObject::connect(downloadTask, &QGSDownloadTask::finished, this, &QGSGameBuilder::slotDownloadFinished);
		QObject::connect(downloadTask, &QGSDownloadTask::error, this, &QGSGameBuilder::slotDownloadError);
		QObject::connect(downloadTask, &QGSDownloadTask::timeout, this, &QGSGameBuilder::slotDownloadTimeout);
		ret.push_back(downloadTask);
	}

	return ret;
}

/**/

void QGSGameBuilder::slotDownloadStart(const DownloadInfo downloadInfo)
{
	emit downloadStart(downloadInfo);
}

void QGSGameBuilder::slotDownloadProgress(qint64 bytesReceived, qint64 bytesTotal, const DownloadInfo downloadInfo)
{
	emit downloadProgress(bytesReceived, bytesTotal, downloadInfo);
}

void QGSGameBuilder::slotDownloadFinished(const DownloadInfo downloadInfo)
{
	qDebug() << downloadInfo.getUrl();
	emit downloadFinished(downloadInfo);
}

void QGSGameBuilder::slotDownloadTimeout(const DownloadInfo downloadInfo)
{
	cancel();
	emit downloadtimeout(downloadInfo);
}

void QGSGameBuilder::slotDownloadError(QGSDownloadTask::Error error, const DownloadInfo downloadInfo)
{
	cancel();
	emit downloadError(error, downloadInfo);
}

void QGSGameBuilder::slotFinished()
{
	emit finished();
}

void QGSGameBuilder::slotError(const QString errorString)
{
	cancel();
	emit error(errorString);
}
