#include "QGSDownloadSourceOfficial.h"

QGSDownloadSourceOfficial::QGSDownloadSourceOfficial(QObject *parent)
	: QGSIDownloadSource(parent)
{
	mApiUrlMap.insert(ApiName::FORGE, QUrl{ "https://files.minecraftforge.net" });
	mApiUrlMap.insert(ApiName::LITELOADER, QUrl{ "https://bmclapi2.bangbang93.com" });
	mApiUrlMap.insert(ApiName::OPTIFINE, QUrl{ "https://bmclapi2.bangbang93.com" });
	mApiUrlMap.insert(ApiName::UNKNOWN, QUrl{ "https://bmclapi2.bangbang93.com" });
}

QGSDownloadSourceOfficial::~QGSDownloadSourceOfficial()
{

}

QUrl QGSDownloadSourceOfficial::getLibraryUrlBase(QUrl & originUrl)
{
	return originUrl = QUrl{ originUrl.toString().replace(originUrl.host(),"libraries.minecraft.net") };
}

QUrl QGSDownloadSourceOfficial::getVersionManifestUrl()
{
	return QUrl{ "https://launchermeta.mojang.com/mc/game/version_manifest.json" };
}

QUrl QGSDownloadSourceOfficial::getVersionUrlBase(QUrl & originUrl)
{
	return originUrl = QUrl{ originUrl.toString().replace(originUrl.host(),"launcher.mojang.com") };
}

QUrl QGSDownloadSourceOfficial::getAssetIndexUrlBase(QUrl & originUrl)
{
	return originUrl = QUrl{ originUrl.toString().replace(originUrl.host(),"launchermeta.mojang.com") };
}

QUrl QGSDownloadSourceOfficial::getAssetUrlBase(QUrl & originUrl)
{
	return originUrl = QUrl{ originUrl.toString().replace(originUrl.host(),"resources.download.minecraft.net") };
}

QUrl QGSDownloadSourceOfficial::getApiUrlBase(const QString & apiName)
{
	if (mApiUrlMap.contains(apiName))
	{
		return mApiUrlMap[apiName];
	}
	else
	{
		return mApiUrlMap[ApiName::UNKNOWN];
	}
}
