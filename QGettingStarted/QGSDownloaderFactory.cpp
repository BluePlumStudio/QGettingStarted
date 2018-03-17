#include "QGSDownloaderFactory.h"
#include "Util/QGSExceptionInvalidValue.h"

QGSDownloaderFactory::QGSDownloaderFactory(QGSIDownloadSource * downloadSource, const QNetworkProxy & proxy)
	:mDownloadSourcePtr(downloadSource), mProxy(proxy)
{
	if (!downloadSource)
	{
		throw QGSExceptionInvalidValue();
	}
}

QGSDownloaderFactory::~QGSDownloaderFactory()
{
}

QGSDownloader * QGSDownloaderFactory::generateDownloader(QFile * targetFile, DownloadInfo & downloadInfo)
{
	if (!targetFile)
	{
		return nullptr;
	}

	return new QGSDownloader{ targetFile,downloadInfo,mProxy };
}


QGSDownloader * QGSDownloaderFactory::generateGameVersionInfoJsonDownloader(QFile * targetFile, DownloadInfo & downloadInfo)
{
	if (!targetFile)
	{
		return nullptr;
	}

	auto && url{ mDownloadSourcePtr->generateGameVersionInfoJsonUrl() };
	downloadInfo.setUrl(url);
	return generateDownloader(targetFile, downloadInfo);
}

QGSDownloader * QGSDownloaderFactory::generateForgeVersionInfoJsonDownloader(QFile * targetFile, int offset, int limit, DownloadInfo & downloadInfo)
{
	if (!targetFile)
	{
		return nullptr;
	}

	auto && url{ mDownloadSourcePtr->generateForgeVersionInfoJsonUrl(offset,limit) };
	downloadInfo.setUrl(url);
	return generateDownloader(targetFile, downloadInfo);
}

QGSDownloader * QGSDownloaderFactory::generateLiteLoaderVersionInfoJsonDownloader(QFile * targetFile, DownloadInfo & downloadInfo)
{
	if (!targetFile)
	{
		return nullptr;
	}

	auto && url{ mDownloadSourcePtr->generateLiteLoaderVersionInfoJsonUrl() };
	downloadInfo.setUrl(url);
	return generateDownloader(targetFile, downloadInfo);
}

QGSDownloader * QGSDownloaderFactory::generateOptifineVersionInfoJsonDownloader(QFile * targetFile, DownloadInfo & downloadInfo)
{
	if (!targetFile)
	{
		return nullptr;
	}

	auto && url{ mDownloadSourcePtr->generateOptifineVersionInfoJsonUrl() };
	downloadInfo.setUrl(url);
	return generateDownloader(targetFile, downloadInfo);
}

QGSDownloader * QGSDownloaderFactory::generateLoggingDownloader(QFile * targetFile, const Logging & logging, DownloadInfo & downloadInfo)
{
	if (!targetFile)
	{
		return nullptr;
	}

	auto && url{ mDownloadSourcePtr->generateLoggingUrl(logging) };
	downloadInfo.setUrl(url);
	return generateDownloader(targetFile, downloadInfo);
}

QGSDownloaderGameVersionJson * QGSDownloaderFactory::generateGameVersionJsonDownloader(const GameVersionInfo & versionInfo, QGSGameDirectory & gameDirectory, DownloadInfo & downloadInfo)
{
	if (versionInfo.getUrl().isEmpty() || versionInfo.getId().isEmpty())
	{
		return nullptr;
	}

	downloadInfo.setUrl(mDownloadSourcePtr->generateGameVersionJsonUrl(versionInfo));
	return new QGSDownloaderGameVersionJson{ gameDirectory.generateGameVersionJsonFile(versionInfo.getId()), downloadInfo,mProxy };
}


QGSDownloaderLibrary * QGSDownloaderFactory::generateLibraryDownloader(const Library & library, QGSGameDirectory & gameDirectory, DownloadInfo & downloadInfo)
{
	if (library.getName().isEmpty() || library.getVersion().isEmpty() || library.getPackage().isEmpty())
	{
		return nullptr;
	}

	downloadInfo.setUrl(mDownloadSourcePtr->generateLibraryUrl(library));
	return new QGSDownloaderLibrary{ gameDirectory.generateLibraryFile(library),downloadInfo,mProxy };
}


QGSDownloaderGameVersion * QGSDownloaderFactory::generateGameVersionDownloader(const GameVersion & version, QGSGameDirectory & gameDirectory, const QString & category, DownloadInfo & downloadInfo)
{
	auto && versionDownloads{ version.getDownloads() };

	if (category.isEmpty()
		|| versionDownloads.isEmpty()
		|| !versionDownloads.contains(category)
		|| versionDownloads.value(category).getUrl().isEmpty())
	{
		return nullptr;
	}

	downloadInfo.setUrl(mDownloadSourcePtr->generateGameVersionUrl(version, category));
	return new QGSDownloaderGameVersion{ gameDirectory.generateGameVersionJarFile(version.getId()),downloadInfo,mProxy };
}

QGSDownloaderAssetIndexJson * QGSDownloaderFactory::generateAssetIndexJsonDownloader(const AssetIndex & assetIndex, QGSGameDirectory & gameDirectory, DownloadInfo & downloadInfo)
{
	if (assetIndex.getUrl().isEmpty())
	{
		return nullptr;
	}

	downloadInfo.setUrl(mDownloadSourcePtr->generateAssetIndexJsonUrl(assetIndex));
	return new QGSDownloaderAssetIndexJson{ gameDirectory.generateAssetIndexJsonFile(assetIndex),downloadInfo,mProxy };
}

QGSDownloaderAssetObject * QGSDownloaderFactory::generateAssetObjectDownloader(const AssetObject & assetObject, QGSGameDirectory & gameDirectory, DownloadInfo & downloadInfo)
{
	if (assetObject.getHash().isEmpty())
	{
		return nullptr;
	}

	downloadInfo.setUrl(mDownloadSourcePtr->generateAssetObjectUrl(assetObject));
	return new QGSDownloaderAssetObject{ gameDirectory.generateAssetObjectFile(assetObject),downloadInfo,mProxy };
}


QGSDownloaderForge * QGSDownloaderFactory::generateForgeDownloader(QFile * targetFile,
	const QString & mcversion, 
	const QString & version, 
	const QString & category, 
	const QString & format, 
	const QString & branch, 
	DownloadInfo & downloadInfo)
{
	if (!targetFile || mcversion.isEmpty() || version.isEmpty() || category.isEmpty() || format.isEmpty())
	{
		return nullptr;
	}

	downloadInfo.setUrl(mDownloadSourcePtr->generateForgeUrl(mcversion, version, category, format, branch));
	return new QGSDownloaderForge{ targetFile,downloadInfo,mProxy };
}


QGSDownloaderLiteLoader * QGSDownloaderFactory::generateLiteLoaderDownloader(QFile * targetFile, const QString & mcversion, const QString & version, const QString & category, DownloadInfo & downloadInfo)
{
	/* universial
	手工拼接`/maven/com/mumfrey/liteloader/${mcversion}/liteloader-${version}.jar`进行下载
	但是SNAPSHOT版需要按照`/maven/com/mumfrey/liteloader/${version}/liteloader-${version}.jar`进行拼接
	*/
	if (!targetFile || version.isEmpty())
	{
		return nullptr;
	}

	downloadInfo.setUrl(mDownloadSourcePtr->generateLiteLoaderUrl(mcversion, version, category));
	return new QGSDownloaderLiteLoader{ targetFile,downloadInfo,mProxy };
}


QGSDownloaderOptifine * QGSDownloaderFactory::generateOptifineDownloader(QFile * targetFile, const QString & mcversion, const QString & type, const QString & patch, DownloadInfo & downloadInfo)
{
	if (!targetFile || mcversion.isEmpty() || type.isEmpty() || patch.isEmpty())
	{
		return nullptr;
	}

	downloadInfo.setUrl(mDownloadSourcePtr->generateOptifineUrl(mcversion, type, patch));
	return new QGSDownloaderOptifine{ targetFile,downloadInfo,mProxy };
}