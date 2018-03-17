#include <QDebug>

#include "QGSDownloadSourceOfficial.h"
#include "Launcher/QGSGameDirectory.h"

QGSDownloadSourceOfficial::QGSDownloadSourceOfficial(QObject *parent)
	: QGSIDownloadSource(parent)
{

}

QGSDownloadSourceOfficial::~QGSDownloadSourceOfficial()
{

}

QUrl QGSDownloadSourceOfficial::generateGameVersionInfoJsonUrl()
{
	return QUrl{ "https://launchermeta.mojang.com/mc/game/version_manifest.json" };
}

QUrl QGSDownloadSourceOfficial::generateForgeVersionInfoJsonUrl(int offset, int limit)
{
	return QUrl{ "http://files.minecraftforge.net/maven/net/minecraftforge/forge/json" };
}

QUrl QGSDownloadSourceOfficial::generateLiteLoaderVersionInfoJsonUrl()
{
	return QUrl{ "http://dl.liteloader.com/versions/versions.json" };
}

QUrl QGSDownloadSourceOfficial::generateOptifineVersionInfoJsonUrl()
{
	return QUrl{ "https://bmclapi2.bangbang93.com/optifine/versionList" };
}

QUrl QGSDownloadSourceOfficial::generateLoggingUrl(const Logging & logging)
{
	return logging.getFile().getUrl();
}

QUrl QGSDownloadSourceOfficial::generateGameVersionJsonUrl(const GameVersionInfo & versionInfo)
{
	return versionInfo.getUrl();
}

QUrl QGSDownloadSourceOfficial::generateLibraryUrl(const Library & library)
{
	QString urlStr{ "https://libraries.minecraft.net/" };

	auto && url{ library.getUrl() };
	if (url.isValid())
	{
		urlStr = url.toString();
	}

	return QUrl{ QString(urlStr + QGSGameDirectory::praseLibraryName(library).replace("\\","/")) };
}

QUrl QGSDownloadSourceOfficial::generateGameVersionUrl(const GameVersion & version, const QString & category)
{
	return version.getDownloads().value(category).getUrl();
}

QUrl QGSDownloadSourceOfficial::generateAssetIndexJsonUrl(const AssetIndex & assetIndex)
{
	return assetIndex.getUrl();
}

QUrl QGSDownloadSourceOfficial::generateAssetObjectUrl(const AssetObject & assetObject)
{
	//http://resources.download.minecraft.net/<first 2 hex letters of hash>/<whole hash>
	auto && hash{ assetObject.getHash() };
	return QUrl{
		QString{"https://resources.download.minecraft.net/%1/%2"}.arg(hash.left(2)).arg(hash)
	};
}

QUrl QGSDownloadSourceOfficial::generateForgeUrl(const QString & mcversion, const QString & version, const QString & category, const QString & format, const QString & branch)
{
	return QUrl{
		QString("https://files.minecraftforge.net/maven/net/minecraftforge/forge/%1-%2%3/forge-%4-%5%6-%7.%8")
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

QUrl QGSDownloadSourceOfficial::generateLiteLoaderUrl(QString mcversion, QString version, const QString & category)
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
				QString{ "%1/lastSuccessfulBuild/artifact/build/libs/liteloader-installer-%2.jar" }.arg(mcversion).arg(version)
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
				QString{ "http://dl.liteloader.com/redist/%1/liteloader-installer-%2.jar" }.arg(mcversion).arg(version)
			};
		}
	}
	else
	{
		return QUrl{
			QString("http://dl.liteloader.com/versions/com/mumfrey/liteloader/%1/liteloader-%2.jar")
			.arg(version.contains("SNAPSHOT") ? version : mcversion)
			.arg(version)
		};
	}
}

QUrl QGSDownloadSourceOfficial::generateOptifineUrl(const QString & mcversion, const QString & type, const QString & patch)
{
	return QUrl{
		QString("https://bmclapi2.bangbang93.com/optifine/%1/%2/%3")
		.arg(mcversion)
		.arg(type)
		.arg(patch)
	};
}
