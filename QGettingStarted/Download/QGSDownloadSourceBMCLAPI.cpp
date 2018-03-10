#include "QGSDownloadSourceBMCLAPI.h"

QGSDownloadSourceBMCLAPI::QGSDownloadSourceBMCLAPI(QObject *parent)
	: QGSIDownloadSource(parent)
{
	mApiUrlMap.insert(ApiName::FORGE, QUrl{ "https://bmclapi2.bangbang93.com" });
	mApiUrlMap.insert(ApiName::LITELOADER, QUrl{ "https://bmclapi2.bangbang93.com" });
	mApiUrlMap.insert(ApiName::OPTIFINE, QUrl{ "https://bmclapi2.bangbang93.com" });
	mApiUrlMap.insert(ApiName::UNKNOWN, QUrl{ "https://bmclapi2.bangbang93.com" });
}

QGSDownloadSourceBMCLAPI::~QGSDownloadSourceBMCLAPI()
{

}

QUrl QGSDownloadSourceBMCLAPI::getLibraryUrlBase()
{
	return QUrl{ "https://bmclapi2.bangbang93.com/libraries" };
}

QUrl QGSDownloadSourceBMCLAPI::getVersionManifestUrl()
{
	return QUrl{ "https://bmclapi2.bangbang93.com/mc/game/version_manifest.json" };
}

QUrl QGSDownloadSourceBMCLAPI::getVersionUrlBase()
{
	return QUrl{ "https://bmclapi2.bangbang93.com/versions" };
}

QUrl QGSDownloadSourceBMCLAPI::getAssetIndexUrlBase()
{
	return QUrl{"https://bmclapi2.bangbang93.com/indexes"};
}

QUrl QGSDownloadSourceBMCLAPI::getAssetUrlBase()
{
	return QUrl{ "https://bmclapi2.bangbang93.com/assets" };
}

QUrl QGSDownloadSourceBMCLAPI::getApiUrlBase(const QString & apiName)
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
