#include "QGSDownloadTaskFactory.h"
#include "Util/QGSExceptionInvalidValue.h"

QGSDownloadTaskFactory::QGSDownloadTaskFactory(QGSIDownloadSource * downloadSource, const QNetworkProxy & proxy, QObject * parent)
	:QObject(parent), mDownloadSourcePtr(downloadSource), mConnectionCount(DownloadTask::DEFAULT_CONNECTION_COUNT), mProxy(proxy)
{
	if (!downloadSource)
	{
		throw QGSExceptionInvalidValue();
	}
}

QGSDownloadTaskFactory::~QGSDownloadTaskFactory()
{
}

QGSDownloadTaskFactory & QGSDownloadTaskFactory::setConnectionCount(const int connectionCount)
{
	mConnectionCount = connectionCount;
	return *this;
}

int QGSDownloadTaskFactory::getConnectionCount() const
{
	return mConnectionCount;
}

QGSDownloadTask * QGSDownloadTaskFactory::generateDownloadTask(QFile * targetFile, QGSDownloadInfo downloadInfo)
{
	if (!targetFile)
	{
		return nullptr;
	}

	return new QGSDownloadTask(targetFile, downloadInfo, mConnectionCount, mProxy);
}

QGSDownloadTask * QGSDownloadTaskFactory::generateGameVersionInfoJsonDownloadTask(QFile * targetFile)
{
	if (!targetFile)
	{
		return nullptr;
	}

	auto && url(mDownloadSourcePtr->generateGameVersionInfoJsonUrl());

	QGSDownloadInfo downloadInfo;
	downloadInfo.setUrl(url);
	return generateDownloadTask(targetFile, downloadInfo);
}

QGSDownloadTask * QGSDownloadTaskFactory::generateForgeVersionInfoJsonDownloadTask(QFile * targetFile, int offset, int limit)
{
	if (!targetFile)
	{
		return nullptr;
	}

	auto && url(mDownloadSourcePtr->generateForgeVersionInfoJsonUrl(offset,limit));

	QGSDownloadInfo downloadInfo;
	downloadInfo.setUrl(url);
	return generateDownloadTask(targetFile, downloadInfo);
}

QGSDownloadTask * QGSDownloadTaskFactory::generateLiteLoaderVersionInfoJsonDownloadTask(QFile * targetFile)
{
	if (!targetFile)
	{
		return nullptr;
	}

	auto && url(mDownloadSourcePtr->generateLiteLoaderVersionInfoJsonUrl());

	QGSDownloadInfo downloadInfo;
	downloadInfo.setUrl(url);
	return generateDownloadTask(targetFile, downloadInfo);
}

QGSDownloadTask * QGSDownloadTaskFactory::generateOptifineVersionInfoJsonDownloadTask(QFile * targetFile)
{
	if (!targetFile)
	{
		return nullptr;
	}

	auto && url(mDownloadSourcePtr->generateOptifineVersionInfoJsonUrl());

	QGSDownloadInfo downloadInfo;
	downloadInfo.setUrl(url);
	return generateDownloadTask(targetFile, downloadInfo);
}

QGSDownloadTask * QGSDownloadTaskFactory::generateLoggingDownloadTask(QFile * targetFile, const QGSLogging & logging)
{
	if (!targetFile)
	{
		return nullptr;
	}

	auto && url(mDownloadSourcePtr->generateLoggingUrl(logging));

	QGSDownloadInfo downloadInfo;
	downloadInfo.setUrl(url);
	return generateDownloadTask(targetFile, downloadInfo);
}

QGSGameVersionJsonDownloadTask * QGSDownloadTaskFactory::generateGameVersionJsonDownloadTask(const QGSGameVersionInfo & versionInfo, QGSGameDirectory & gameDirectory)
{
	if (versionInfo.getUrl().isEmpty() || versionInfo.getId().isEmpty())
	{
		return nullptr;
	}

	QGSDownloadInfo downloadInfo;
	downloadInfo.setUrl(mDownloadSourcePtr->generateGameVersionJsonUrl(versionInfo));
	return new QGSGameVersionJsonDownloadTask(gameDirectory.generateGameVersionJsonFile(versionInfo.getId()), downloadInfo,mConnectionCount,mProxy);
}


QGSLibraryDownloadTask * QGSDownloadTaskFactory::generateLibraryDownloadTask(const QGSLibrary & library, QGSGameDirectory & gameDirectory)
{
	if (library.getName().isEmpty() || library.getVersion().isEmpty() || library.getPackage().isEmpty())
	{
		return nullptr;
	}

	QGSDownloadInfo downloadInfo;
	downloadInfo.setUrl(mDownloadSourcePtr->generateLibraryUrl(library));
	return new QGSLibraryDownloadTask(gameDirectory.generateLibraryFile(library),downloadInfo,mConnectionCount,mProxy);
}


QGSGameVersionDownloadTask * QGSDownloadTaskFactory::generateGameVersionDownloadTask(const QGSGameVersion & version, QGSGameDirectory & gameDirectory, const QString & category)
{
	auto && versionDownloads(version.getDownloads());

	if (category.isEmpty()
		|| versionDownloads.isEmpty()
		|| !versionDownloads.contains(category)
		|| versionDownloads.value(category).getUrl().isEmpty())
	{
		return nullptr;
	}

	QGSDownloadInfo downloadInfo;
	downloadInfo.setUrl(mDownloadSourcePtr->generateGameVersionUrl(version, category));
	return new QGSGameVersionDownloadTask(gameDirectory.generateGameVersionJarFile(version.getId()),downloadInfo,mConnectionCount,mProxy);
}

QGSAssetIndexJsonDownloadTask * QGSDownloadTaskFactory::generateAssetIndexJsonDownloadTask(const QGSAssetIndex & assetIndex, QGSGameDirectory & gameDirectory)
{
	if (assetIndex.getUrl().isEmpty())
	{
		return nullptr;
	}

	QGSDownloadInfo downloadInfo;
	downloadInfo.setUrl(mDownloadSourcePtr->generateAssetIndexJsonUrl(assetIndex));
	return new QGSAssetIndexJsonDownloadTask(gameDirectory.generateAssetIndexJsonFile(assetIndex),downloadInfo,mConnectionCount,mProxy);
}

QGSAssetObjectDownloadTask * QGSDownloadTaskFactory::generateAssetObjectDownloadTask(const QGSAssetObject & assetObject, QGSGameDirectory & gameDirectory)
{
	if (assetObject.getHash().isEmpty())
	{
		return nullptr;
	}

	QGSDownloadInfo downloadInfo;
	downloadInfo.setUrl(mDownloadSourcePtr->generateAssetObjectUrl(assetObject));
	return new QGSAssetObjectDownloadTask(gameDirectory.generateAssetObjectFile(assetObject),downloadInfo,mConnectionCount,mProxy);
}


QGSForgeDownloadTask * QGSDownloadTaskFactory::generateForgeDownloadTask(QFile * targetFile,
	const QString & mcversion, 
	const QString & version, 
	const QString & category, 
	const QString & format, 
	const QString & branch)
{
	if (!targetFile || mcversion.isEmpty() || version.isEmpty() || category.isEmpty() || format.isEmpty())
	{
		return nullptr;
	}

	QGSDownloadInfo downloadInfo;
	downloadInfo.setUrl(mDownloadSourcePtr->generateForgeUrl(mcversion, version, category, format, branch));
	return new QGSForgeDownloadTask(targetFile,downloadInfo,mConnectionCount,mProxy);
}


QGSLiteLoaderDownloadTask * QGSDownloadTaskFactory::generateLiteLoaderDownloadTask(QFile * targetFile, const QString & mcversion, const QString & version, const QString & category)
{
	/* universal
	手工拼接`/maven/com/mumfrey/liteloader/${mcversion}/liteloader-${version}.jar`进行下载
	但是SNAPSHOT版需要按照`/maven/com/mumfrey/liteloader/${version}/liteloader-${version}.jar`进行拼接
	*/
	if (!targetFile || version.isEmpty())
	{
		return nullptr;
	}

	QGSDownloadInfo downloadInfo;
	downloadInfo.setUrl(mDownloadSourcePtr->generateLiteLoaderUrl(mcversion, version, category));
	return new QGSLiteLoaderDownloadTask(targetFile,downloadInfo,mConnectionCount,mProxy);
}


QGSOptifineDownloadTask * QGSDownloadTaskFactory::generateOptifineDownloadTask(QFile * targetFile, const QString & mcversion, const QString & type, const QString & patch)
{
	if (!targetFile || mcversion.isEmpty() || type.isEmpty() || patch.isEmpty())
	{
		return nullptr;
	}

	QGSDownloadInfo downloadInfo;
	downloadInfo.setUrl(mDownloadSourcePtr->generateOptifineUrl(mcversion, type, patch));
	return new QGSOptifineDownloadTask(targetFile,downloadInfo,mConnectionCount,mProxy);
}