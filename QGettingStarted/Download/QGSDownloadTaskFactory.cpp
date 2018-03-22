#include "QGSDownloadTaskFactory.h"
#include "Util/QGSExceptionInvalidValue.h"

QGSDownloadTaskFactory::QGSDownloadTaskFactory(QGSIDownloadSource * downloadSource, const QNetworkProxy & proxy)
	:mDownloadSourcePtr(downloadSource), mProxy(proxy)
{
	if (!downloadSource)
	{
		throw QGSExceptionInvalidValue();
	}
}

QGSDownloadTaskFactory::~QGSDownloadTaskFactory()
{
}

QGSDownloadTask * QGSDownloadTaskFactory::generateDownloadTask(QFile * targetFile, DownloadInfo & downloadInfo)
{
	if (!targetFile)
	{
		return nullptr;
	}

	return new QGSDownloadTask{ targetFile,downloadInfo,mProxy };
}


QGSDownloadTask * QGSDownloadTaskFactory::generateGameVersionInfoJsonDownloadTask(QFile * targetFile, DownloadInfo & downloadInfo)
{
	if (!targetFile)
	{
		return nullptr;
	}

	auto && url{ mDownloadSourcePtr->generateGameVersionInfoJsonUrl() };
	downloadInfo.setUrl(url);
	return generateDownloadTask(targetFile, downloadInfo);
}

QGSDownloadTask * QGSDownloadTaskFactory::generateForgeVersionInfoJsonDownloadTask(QFile * targetFile, int offset, int limit, DownloadInfo & downloadInfo)
{
	if (!targetFile)
	{
		return nullptr;
	}

	auto && url{ mDownloadSourcePtr->generateForgeVersionInfoJsonUrl(offset,limit) };
	downloadInfo.setUrl(url);
	return generateDownloadTask(targetFile, downloadInfo);
}

QGSDownloadTask * QGSDownloadTaskFactory::generateLiteLoaderVersionInfoJsonDownloadTask(QFile * targetFile, DownloadInfo & downloadInfo)
{
	if (!targetFile)
	{
		return nullptr;
	}

	auto && url{ mDownloadSourcePtr->generateLiteLoaderVersionInfoJsonUrl() };
	downloadInfo.setUrl(url);
	return generateDownloadTask(targetFile, downloadInfo);
}

QGSDownloadTask * QGSDownloadTaskFactory::generateOptifineVersionInfoJsonDownloadTask(QFile * targetFile, DownloadInfo & downloadInfo)
{
	if (!targetFile)
	{
		return nullptr;
	}

	auto && url{ mDownloadSourcePtr->generateOptifineVersionInfoJsonUrl() };
	downloadInfo.setUrl(url);
	return generateDownloadTask(targetFile, downloadInfo);
}

QGSDownloadTask * QGSDownloadTaskFactory::generateLoggingDownloadTask(QFile * targetFile, const QGSLogging & logging, DownloadInfo & downloadInfo)
{
	if (!targetFile)
	{
		return nullptr;
	}

	auto && url{ mDownloadSourcePtr->generateLoggingUrl(logging) };
	downloadInfo.setUrl(url);
	return generateDownloadTask(targetFile, downloadInfo);
}

QGSGameVersionJsonDownloadTask * QGSDownloadTaskFactory::generateGameVersionJsonDownloadTask(const QGSGameVersionInfo & versionInfo, QGSGameDirectory & gameDirectory, DownloadInfo & downloadInfo)
{
	if (versionInfo.getUrl().isEmpty() || versionInfo.getId().isEmpty())
	{
		return nullptr;
	}

	downloadInfo.setUrl(mDownloadSourcePtr->generateGameVersionJsonUrl(versionInfo));
	return new QGSGameVersionJsonDownloadTask{ gameDirectory.generateGameVersionJsonFile(versionInfo.getId()), downloadInfo,mProxy };
}


QGSLibraryDownloadTask * QGSDownloadTaskFactory::generateLibraryDownloadTask(const QGSLibrary & library, QGSGameDirectory & gameDirectory, DownloadInfo & downloadInfo)
{
	if (library.getName().isEmpty() || library.getVersion().isEmpty() || library.getPackage().isEmpty())
	{
		return nullptr;
	}

	downloadInfo.setUrl(mDownloadSourcePtr->generateLibraryUrl(library));
	return new QGSLibraryDownloadTask{ gameDirectory.generateLibraryFile(library),downloadInfo,mProxy };
}


QGSGameVersionDownloadTask * QGSDownloadTaskFactory::generateGameVersionDownloadTask(const QGSGameVersion & version, QGSGameDirectory & gameDirectory, const QString & category, DownloadInfo & downloadInfo)
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
	return new QGSGameVersionDownloadTask{ gameDirectory.generateGameVersionJarFile(version.getId()),downloadInfo,mProxy };
}

QGSAssetIndexJsonDownloadTask * QGSDownloadTaskFactory::generateAssetIndexJsonDownloadTask(const QGSAssetIndex & assetIndex, QGSGameDirectory & gameDirectory, DownloadInfo & downloadInfo)
{
	if (assetIndex.getUrl().isEmpty())
	{
		return nullptr;
	}

	downloadInfo.setUrl(mDownloadSourcePtr->generateAssetIndexJsonUrl(assetIndex));
	return new QGSAssetIndexJsonDownloadTask{ gameDirectory.generateAssetIndexJsonFile(assetIndex),downloadInfo,mProxy };
}

QGSAssetObjectDownloadTask * QGSDownloadTaskFactory::generateAssetObjectDownloadTask(const QGSAssetObject & assetObject, QGSGameDirectory & gameDirectory, DownloadInfo & downloadInfo)
{
	if (assetObject.getHash().isEmpty())
	{
		return nullptr;
	}

	downloadInfo.setUrl(mDownloadSourcePtr->generateAssetObjectUrl(assetObject));
	return new QGSAssetObjectDownloadTask{ gameDirectory.generateAssetObjectFile(assetObject),downloadInfo,mProxy };
}


QGSForgeDownloadTask * QGSDownloadTaskFactory::generateForgeDownloadTask(QFile * targetFile,
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
	return new QGSForgeDownloadTask{ targetFile,downloadInfo,mProxy };
}


QGSLiteLoaderDownloadTask * QGSDownloadTaskFactory::generateLiteLoaderDownloadTask(QFile * targetFile, const QString & mcversion, const QString & version, const QString & category, DownloadInfo & downloadInfo)
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
	return new QGSLiteLoaderDownloadTask{ targetFile,downloadInfo,mProxy };
}


QGSOptifineDownloadTask * QGSDownloadTaskFactory::generateOptifineDownloadTask(QFile * targetFile, const QString & mcversion, const QString & type, const QString & patch, DownloadInfo & downloadInfo)
{
	if (!targetFile || mcversion.isEmpty() || type.isEmpty() || patch.isEmpty())
	{
		return nullptr;
	}

	downloadInfo.setUrl(mDownloadSourcePtr->generateOptifineUrl(mcversion, type, patch));
	return new QGSOptifineDownloadTask{ targetFile,downloadInfo,mProxy };
}