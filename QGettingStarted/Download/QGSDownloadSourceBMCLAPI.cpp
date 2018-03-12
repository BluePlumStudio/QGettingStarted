#include <QDebug>

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

QUrl QGSDownloadSourceBMCLAPI::getLibraryUrlBase(QUrl & originUrl)
{
	return originUrl = QUrl{ originUrl.toString().replace(originUrl.host(),"bmclapi2.bangbang93.com") };
}

QUrl QGSDownloadSourceBMCLAPI::getVersionManifestUrl()
{
	return QUrl{ "https://bmclapi2.bangbang93.com/mc/game/version_manifest.json" };
}

QUrl QGSDownloadSourceBMCLAPI::getVersionUrlBase(QUrl & originUrl)
{
	return originUrl = QUrl{ originUrl.toString().replace(originUrl.host(),"bmclapi2.bangbang93.com") };
}

QUrl QGSDownloadSourceBMCLAPI::getAssetIndexUrlBase(QUrl & originUrl)
{
	return originUrl = QUrl{ originUrl.toString().replace(originUrl.host(),"bmclapi2.bangbang93.com") };
}

QUrl QGSDownloadSourceBMCLAPI::getAssetUrlBase(QUrl & originUrl)
{
	return originUrl = QUrl{ originUrl.toString().replace(originUrl.host(),"bmclapi2.bangbang93.com") };
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
