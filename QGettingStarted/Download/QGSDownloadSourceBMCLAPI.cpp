#include <QDebug>

#include "QGSDownloadSourceBMCLAPI.h"
#include "Launcher/QGSGameDirectory.h"

QGSDownloadSourceBMCLAPI::QGSDownloadSourceBMCLAPI(QObject *parent)
	: QGSIDownloadSource(parent)
{

}

QGSDownloadSourceBMCLAPI::~QGSDownloadSourceBMCLAPI()
{

}

QUrl QGSDownloadSourceBMCLAPI::generateGameVersionInfoJsonUrl()
{
	return QUrl{ "https://bmclapi2.bangbang93.com/mc/game/version_manifest.json" };
}

QUrl QGSDownloadSourceBMCLAPI::generateForgeVersionInfoJsonUrl(int offset, int limit)
{
	return QUrl{ QString{"https://bmclapi2.bangbang93.com/forge/list/%1/%2"}.arg(offset).arg(limit) };
}

QUrl QGSDownloadSourceBMCLAPI::generateLiteLoaderVersionInfoJsonUrl()
{
	//BMCLAPI Bug:Unexpected end of json
	//https://bmclapi2.bangbang93.com/maven/com/mumfrey/liteloader/versions.json
	return QUrl{ "http://dl.liteloader.com/versions/versions.json" };
}

QUrl QGSDownloadSourceBMCLAPI::generateOptifineVersionInfoJsonUrl()
{
	return QUrl{ "https://bmclapi2.bangbang93.com/optifine/versionList" };
}

QUrl QGSDownloadSourceBMCLAPI::generateLoggingUrl(const Logging & logging)
{
	return logging.getFile().getUrl();
}

QUrl QGSDownloadSourceBMCLAPI::generateGameVersionJsonUrl(const GameVersionInfo & versionInfo)
{
	QUrl ret{ versionInfo.getUrl() };
	return QUrl{ ret.toString().replace(ret.host(),"bmclapi2.bangbang93.com") };
}

QUrl QGSDownloadSourceBMCLAPI::generateLibraryUrl(const Library & library)
{
	QString urlStr{ "https://bmclapi2.bangbang93.com/libraries/" };

	auto && url{ library.getUrl() };
	if (!url.isEmpty() && url.isValid())
	{
		urlStr = url.toString();
	}
	return QUrl{ QString(urlStr + QGSGameDirectory::praseLibraryName(library).replace("\\","/")) };
}

QUrl QGSDownloadSourceBMCLAPI::generateGameVersionUrl(const GameVersion & version, const QString & category)
{
	QUrl url{ version.getDownloads().value(category).getUrl() };
	if (url.isValid())
	{
		return QUrl{ url.toString().replace(url.host(),"bmclapi2.bangbang93.com") };
	}
	else
	{
		return QUrl{ QString{"https://bmclapi2.bangbang93.com/version/%1/%2"}.arg(version.getId()).arg(category) };
	}
}

QUrl QGSDownloadSourceBMCLAPI::generateAssetIndexJsonUrl(const AssetIndex & assetIndex)
{
	QUrl ret{ assetIndex.getUrl() };
	return QUrl{ ret.toString().replace(ret.host(),"bmclapi2.bangbang93.com") };
}

QUrl QGSDownloadSourceBMCLAPI::generateAssetObjectUrl(const AssetObject & assetObject)
{
	auto && hash{ assetObject.getHash() };
	return QUrl{
		QString{ "https://bmclapi2.bangbang93.com/%1/%2" }.arg(hash.left(2)).arg(hash)
	};
}

QUrl QGSDownloadSourceBMCLAPI::generateForgeUrl(const QString & mcversion, const QString & version, const QString & category, const QString & format, const QString & branch)
{
	return QUrl {
		QString("https://bmclapi2.bangbang93.com/maven/net/minecraftforge/forge/%1-%2%3/forge-%4-%5%6-%7.%8")
		.arg(mcversion)
		.arg(version)
		.arg(branch.isEmpty() ? "" : QString("(branch?%1:'')").arg(branch))
		.arg(mcversion)
		.arg(version)
		.arg(branch.isEmpty() ? "" : QString("(branch?%1:'')").arg(branch))
		.arg(category)
		.arg(format)
	};
}

QUrl QGSDownloadSourceBMCLAPI::generateLiteLoaderUrl(QString mcversion, QString version, const QString & category)
{
	if (category.contains("installer"))
	{
		version.replace("_", "-");
		if (version.contains("SNAPSHOT"))
		{
			//example:1.11.2-SNAPSHOT
			if (version.count("-") == 1)
			{
				version.insert(version.indexOf("-"), "-00");
			}
			return QUrl{
				"http://jenkins.liteloader.com/job/LiteLoaderInstaller%20" +
				QString{"%1/lastSuccessfulBuild/artifact/build/libs/liteloader-installer-%2.jar"}.arg(mcversion).arg(version)
			};
		}
		else
		{
			//example:1.9.4
			if (!version.contains("-"))
			{
				version.append("-00");
			}
			return QUrl{
				QString{"http://dl.liteloader.com/redist/%1/liteloader-installer-%2.jar"}.arg(mcversion).arg(version)
			};
		}
	}
	else
	{
		return QUrl{
			QString("https://bmclapi2.bangbang93.com/maven/com/mumfrey/liteloader/%1/liteloader-%2.jar")
			.arg(version.contains("SNAPSHOT") ? version : mcversion)
			.arg(version)
		};
	}
}

QUrl QGSDownloadSourceBMCLAPI::generateOptifineUrl(const QString & mcversion, const QString & type, const QString & patch)
{
	return QUrl {
		QString("https://bmclapi2.bangbang93.com/optifine/%1/%2/%3")
		.arg(mcversion)
		.arg(type)
		.arg(patch)
	};
}
