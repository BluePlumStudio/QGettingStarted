#pragma once

#include <QString>
#include <QUrl>
#include <QObject>
#include <QFileInfo>

#include "QGSDownloader.h"
#include "QGSIDownloadSource.h"
#include "QGSDownloadSourceBMCLAPI.h"

template<class T = QGSDownloadSourceBMCLAPI>
class QGSDownloadManager
{
public:
	QGSDownloadManager()
	{

	}

	QGSDownloadManager(const QGSDownloadManager & right) = delete;

	QGSDownloadManager(QGSDownloadManager && right) = delete;

	QGSDownloadManager & operator=(const QGSDownloadManager & right) = delete;

	QGSDownloadManager & operator=(QGSDownloadManager && right) = delete;

	virtual ~QGSDownloadManager()
	{

	}

	QGSDownloader * generateLibraryDownloader(const Library & library, DownloadInfo & downloadInfo = DownloadInfo())
	{
		if (library.getName().isEmpty() || library.getVersion().isEmpty() || library.getPackage().isEmpty())
		{
			return nullptr;
		}

		QUrl url{
			QString(mDownloadSource.getLibraryUrlBase().toString() + "/" + QGSGameDirectory::praseLibraryName(library).replace("\\","/"))
		};

		downloadInfo.setUrl(url);
		return new QGSDownloader{ downloadInfo };
	}

	QGSDownloader * generateVersionDownloader(const QString & mcversion, const QString & category, DownloadInfo & downloadInfo = DownloadInfo())
	{
		if (mcversion.isEmpty() || category.isEmpty())
		{
			return nullptr;
		}

		QUrl url{
			QString(mDownloadSource.getApiUrlBase(ApiName::LITELOADER).toString() + "/version/%1/%2")
			.arg(mcversion)
			.arg(category)
		};

		downloadInfo.setUrl(url);
		return new QGSDownloader{ downloadInfo };
	}

	QGSDownloader * generateForgeDownloader(const QString & mcversion, const QString & version, const QString & category, const QString & format, const QString & branch = "", DownloadInfo & downloadInfo = DownloadInfo())
	{
		if (mcversion.isEmpty() || version.isEmpty() || category.isEmpty() || format.isEmpty())
		{
			return nullptr;
		}

		QUrl url{
			QString(mDownloadSource.getApiUrlBase(ApiName::FORGE).toString() + "/maven/net/minecraftforge/forge/%1-%2%3/forge-%4-%5%6-%7.%8")
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

	QGSDownloader * generateLiteLoaderDownloader(const QString & version, const QString & mcversion, DownloadInfo & downloadInfo = DownloadInfo())
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
			QString(mDownloadSource.getApiUrlBase(ApiName::LITELOADER).toString() + "/maven/com/mumfrey/liteloader/%1/liteloader-%2.jar")
				.arg(version.contains("SNAPSHOT") ? version : mcversion)
				.arg(version)
		};

		downloadInfo.setUrl(url);
		return new QGSDownloader{ downloadInfo };
	}

	QGSDownloader * generateOptifineDownloader(const QString & mcversion, const QString & type, const QString & patch, DownloadInfo & downloadInfo = DownloadInfo())
	{
		if (mcversion.isEmpty() || type.isEmpty() || patch.isEmpty())
		{
			return nullptr;
		}

		QUrl url{
			QString(mDownloadSource.getApiUrlBase(ApiName::OPTIFINE).toString() + "/optifine/%1/%2/%3")
			.arg(mcversion)
			.arg(type)
			.arg(patch)
		};

		downloadInfo.setUrl(url);
		return new QGSDownloader{ downloadInfo };
	}
private:
	T mDownloadSource;
};
