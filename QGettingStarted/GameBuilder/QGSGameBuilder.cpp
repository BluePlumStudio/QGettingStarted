#include "QGSGameBuilder.h"
#include "../Util/QGSExceptionJsonPraseError.h"
#include "../Util/QGSExceptionVersionNotFound.h"
#include "../Util/QGSExceptionFileIO.h"

QGSGameBuilder::QGSGameBuilder(QGSIDownloadSource * downloadSource, QGSGameDirectory * gameDirectory, QObject * parent)
	:QGSIGameBuilder(downloadSource, gameDirectory, parent), mDownloaderFactoryPtr(new QGSDownloaderFactory{ downloadSource })
{

}


QGSGameBuilder::~QGSGameBuilder()
{

}

bool QGSGameBuilder::start(const GameVersionInfo & gameVersionInfo)
{
	QGSDownloader * downloader{ nullptr };
	downloader = generateGameVersionJsonDownloader(gameVersionInfo);
	mThreadPool.run(downloader);
	downloader->start();
	connect(downloader, &QGSDownloader::finished, &mEventLoop, &QEventLoop::quit);
	mEventLoop.exec();

	downloader = generateGameVersionDownloader(gameVersionInfo);
	mThreadPool.run(downloader);
	downloader->start();

	downloader = generateAssetIndexJsonDownloader(gameVersionInfo);
	mThreadPool.run(downloader);
	downloader->start();
	connect(downloader, &QGSDownloader::finished, &mEventLoop, &QEventLoop::quit);
	mEventLoop.exec();

	auto && downloaderList{ generateLibrarDownloaderList(gameVersionInfo) };
	for (auto & downloader : downloaderList)
	{
		mThreadPool.run(downloader);
		downloader->start();
	}

	QGSAssetIndexInfoFactory assetIndexInfoFactory;
	auto * assetIndexFile{ mGameDirectoryPtr->generateAssetIndexJsonFile(mGameDirectoryPtr->getVersion(gameVersionInfo.getId()).getAssetIndex()) };
	assetIndexFile->open(QIODevice::ReadOnly);
	downloaderList = generateAssetObjectDownloaderList(assetIndexInfoFactory.createAssetIndexInfo(assetIndexFile->readAll()));
	for (auto & downloader : downloaderList)
	{
		mThreadPool.run(downloader);
		downloader->start();
	}
	return true;
}

bool QGSGameBuilder::cancel()
{
	return false;
}

QGSDownloader * QGSGameBuilder::generateGameVersionJsonDownloader(const GameVersionInfo & gameVersionInfo)
{
	QGSDownloader * downloader{ nullptr };

	downloader = mDownloaderFactoryPtr->generateGameVersionJsonDownloader(gameVersionInfo, *mGameDirectoryPtr);
	if (!downloader)
	{
		slotError("'generateGameVersionJsonDownloader' start failure!");
		return nullptr;
	}

	QObject::connect(downloader, &QGSDownloader::downloadProgress, this, &QGSGameBuilder::slotDownloadProgress);
	QObject::connect(downloader, &QGSDownloader::finished, this, &QGSGameBuilder::slotDownloadFinished);
	QObject::connect(downloader, &QGSDownloader::error, this, &QGSGameBuilder::slotDownloadError);
	QObject::connect(downloader, &QGSDownloader::timeout, this, &QGSGameBuilder::slotDownloadTimeout);
	/*
	QObject::connect(downloader, &QGSDownloader::finished, [=]()
	{
		downloadGameVersionJar(gameVersionInfo);
		downloadLibraries(gameVersionInfo);
	});
	*/
	return downloader;
}

QGSDownloader * QGSGameBuilder::generateGameVersionDownloader(const GameVersionInfo & gameVersionInfo)
{
	QGSDownloader * downloader{ nullptr };

	try
	{
		auto & version{ mGameDirectoryPtr->getVersion(gameVersionInfo.getId()) };
		downloader = mDownloaderFactoryPtr->generateGameVersionDownloader(version, *mGameDirectoryPtr, "client");
		if (!downloader)
		{
			slotError("'generateGameVersionDownloader' start failure!");
			return nullptr;
		}
	}
	catch (const QGSExceptionVersionNotFound & exception)
	{
		slotError("'downloadGameVersion' version not found!");
		downloader->deleteLater();
		return nullptr;
	}
	catch (const QGSExceptionFileIO & exception)
	{
		slotError("'downloadGameVersion' file IO error!");
		downloader->deleteLater();
		return nullptr;
	}
	catch (const QGSExceptionJsonPraseError & exception)
	{
		slotError("'downloadGameVersion' json prase error!");
		downloader->deleteLater();
		return nullptr;
	}
	catch (...)
	{
		slotError("'downloadGameVersion' unknown error!");
		downloader->deleteLater();
		return nullptr;
	}

	QObject::connect(downloader, &QGSDownloader::downloadProgress, this, &QGSGameBuilder::slotDownloadProgress);
	QObject::connect(downloader, &QGSDownloader::finished, this, &QGSGameBuilder::slotDownloadFinished);
	QObject::connect(downloader, &QGSDownloader::error, this, &QGSGameBuilder::slotDownloadError);
	QObject::connect(downloader, &QGSDownloader::timeout, this, &QGSGameBuilder::slotDownloadTimeout);
	/*
	QObject::connect(downloader, &QGSDownloader::finished, &mEventLoop, &QEventLoop::quit);
	mEventLoop.exec();
		*/
	return downloader;
}

QList<QGSDownloader *> QGSGameBuilder::generateLibrarDownloaderList(const GameVersionInfo & gameVersionInfo)
{
	QList<QGSDownloader *> ret;
	QGSDownloader * downloader{ nullptr };

	auto && libraryList{ mGameDirectoryPtr->getVersion(gameVersionInfo.getId()).getLibraries() };
	for (auto & library : libraryList)
	{
		downloader = mDownloaderFactoryPtr->generateLibraryDownloader(library, *mGameDirectoryPtr);
		if (!downloader)
		{
			slotError("'generateLibraryDownloader' start failure!");
			return ret;
		}

		QObject::connect(downloader, &QGSDownloader::downloadProgress, this, &QGSGameBuilder::slotDownloadProgress);
		QObject::connect(downloader, &QGSDownloader::finished, this, &QGSGameBuilder::slotDownloadFinished);
		QObject::connect(downloader, &QGSDownloader::error, this, &QGSGameBuilder::slotDownloadError);
		QObject::connect(downloader, &QGSDownloader::timeout, this, &QGSGameBuilder::slotDownloadTimeout);
		ret.push_back(downloader);
	}

	return ret;
}

QGSDownloader * QGSGameBuilder::generateAssetIndexJsonDownloader(const GameVersionInfo & gameVersionInfo)
{
	QGSDownloader * downloader{ nullptr };

	downloader = mDownloaderFactoryPtr->generateAssetIndexJsonDownloader(mGameDirectoryPtr->getVersion(gameVersionInfo.getId()).getAssetIndex(), *mGameDirectoryPtr);
	if (!downloader)
	{
		slotError("'generateAssetIndexJsonDownloader' start failure!");
		return nullptr;
	}

	QObject::connect(downloader, &QGSDownloader::downloadProgress, this, &QGSGameBuilder::slotDownloadProgress);
	QObject::connect(downloader, &QGSDownloader::finished, this, &QGSGameBuilder::slotDownloadFinished);
	QObject::connect(downloader, &QGSDownloader::error, this, &QGSGameBuilder::slotDownloadError);
	QObject::connect(downloader, &QGSDownloader::timeout, this, &QGSGameBuilder::slotDownloadTimeout);
	/*
	QObject::connect(downloader, &QGSDownloader::finished, [=]()
	{
		AssetIndexInfo assetIndexInfo;
		QGSAssetIndexInfoFactory versionInfoFactory;
		if (!downloader->getTargetFile()->open(QIODevice::ReadOnly))
		{
			slotError("'downloadAssetIndex' file IO error!");
		}

		try
		{
			assetIndexInfo = versionInfoFactory.createAssetIndexInfo(downloader->getTargetFile()->readAll());
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
	return downloader;
}

QList<QGSDownloader *>  QGSGameBuilder::generateAssetObjectDownloaderList(const AssetIndexInfo & assetIndexInfo)
{
	QList<QGSDownloader *> ret;
	QGSDownloader * downloader{ nullptr };

	auto && assetObjectMap{ assetIndexInfo.getAssetObjectMap() };
	for (auto & i : assetObjectMap)
	{
		downloader = mDownloaderFactoryPtr->generateAssetObjectDownloader(i, *mGameDirectoryPtr);
		if (!downloader)
		{
			slotError("'generateAssetObjectDownloader' start failure!");
			return ret;
		}

		QObject::connect(downloader, &QGSDownloader::downloadProgress, this, &QGSGameBuilder::slotDownloadProgress);
		QObject::connect(downloader, &QGSDownloader::finished, this, &QGSGameBuilder::slotDownloadFinished);
		QObject::connect(downloader, &QGSDownloader::error, this, &QGSGameBuilder::slotDownloadError);
		QObject::connect(downloader, &QGSDownloader::timeout, this, &QGSGameBuilder::slotDownloadTimeout);
		ret.push_back(downloader);
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

void QGSGameBuilder::slotDownloadError(QGSDownloader::Error error, const DownloadInfo downloadInfo)
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
