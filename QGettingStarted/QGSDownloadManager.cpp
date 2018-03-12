#include "QGSDownloadManager.h"
#include "Util/QGSException.h"

QGSDownloadManager::QGSDownloadManager(QGSIDownloadSource * downloadSource) :mDownloadSourcePtr(downloadSource)
{
	if (!downloadSource)
	{
		throw QGSException();
	}
}

QGSDownloadManager::~QGSDownloadManager()
{
}


QGSDownloader * QGSDownloadManager::generateVersionManifestDownloader(DownloadInfo & downloadInfo)
{
	auto && url{ mDownloadSourcePtr->getVersionManifestUrl() };
	downloadInfo.setUrl(url);
	return new QGSDownloader{ downloadInfo };
}


QGSDownloader * QGSDownloadManager::generateLibraryDownloader(const Library & library, DownloadInfo & downloadInfo)
{
	if (library.getName().isEmpty() || library.getVersion().isEmpty() || library.getPackage().isEmpty())
	{
		return nullptr;
	}

	QUrl url{
		QString("https://libraries.minecraft.net/" + QGSGameDirectory::praseLibraryName(library).replace("\\","/"))
	};

	mDownloadSourcePtr->getLibraryUrlBase(url);
	downloadInfo.setUrl(url);
	return new QGSDownloader{ downloadInfo };
}


QGSDownloader * QGSDownloadManager::generateVersionDownloader(Version & version, const QString & category, DownloadInfo & downloadInfo)
{
	auto && versionDownloads{ version.getDownloads() };

	if (category.isEmpty()
		|| versionDownloads.isEmpty()
		|| !versionDownloads.contains(category)
		|| versionDownloads.value(category).getUrl().isEmpty())
	{
		return nullptr;
	}


	QUrl url{ versionDownloads.value(category).getUrl() };
	mDownloadSourcePtr->getVersionUrlBase(url);
	downloadInfo.setUrl(url);
	return new QGSDownloader{ downloadInfo };
}


QGSDownloader * QGSDownloadManager::generateForgeDownloader(
	const QString & mcversion, const QString & version, const QString & category, const QString & format, const QString & branch, DownloadInfo & downloadInfo)
{
	if (mcversion.isEmpty() || version.isEmpty() || category.isEmpty() || format.isEmpty())
	{
		return nullptr;
	}

	QUrl url{
		QString(mDownloadSourcePtr->getApiUrlBase(ApiName::FORGE).toString() + "/maven/net/minecraftforge/forge/%1-%2%3/forge-%4-%5%6-%7.%8")
		.arg(mcversion)
		.arg(version)
		.arg(branch.isEmpty() ? "" : QString("(branch?%1:'')").arg(branch))
		.arg(mcversion)
		.arg(version)
		.arg(branch.isEmpty() ? "" : QString("(branch?%1:'')").arg(branch))
		.arg(category)
		.arg(format)
	};

	downloadInfo.setUrl(url);
	return new QGSDownloader{ downloadInfo };
}


QGSDownloader * QGSDownloadManager::generateLiteLoaderDownloader(const QString & version, const QString & mcversion, DownloadInfo & downloadInfo)
{
	/*
	手工拼接`/maven/com/mumfrey/liteloader/${mcversion}/liteloader-${version}.jar`进行下载
	但是SNAPSHOT版需要按照`/maven/com/mumfrey/liteloader/${version}/liteloader-${version}.jar`进行拼接
	*/
	if (version.isEmpty())
	{
		return nullptr;
	}

	QUrl url{
		QString(mDownloadSourcePtr->getApiUrlBase(ApiName::LITELOADER).toString() + "/maven/com/mumfrey/liteloader/%1/liteloader-%2.jar")
		.arg(version.contains("SNAPSHOT") ? version : mcversion)
		.arg(version)
	};

	downloadInfo.setUrl(url);
	return new QGSDownloader{ downloadInfo };
}


QGSDownloader * QGSDownloadManager::generateOptifineDownloader(const QString & mcversion, const QString & type, const QString & patch, DownloadInfo & downloadInfo)
{
	if (mcversion.isEmpty() || type.isEmpty() || patch.isEmpty())
	{
		return nullptr;
	}

	QUrl url{
		QString(mDownloadSourcePtr->getApiUrlBase(ApiName::OPTIFINE).toString() + "/optifine/%1/%2/%3")
		.arg(mcversion)
		.arg(type)
		.arg(patch)
	};

	downloadInfo.setUrl(url);
	return new QGSDownloader{ downloadInfo };
}