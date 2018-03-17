#pragma once

#include <QString>
#include <QUrl>
#include <QObject>
#include <QFileInfo>

#include "QGSDownloader.h"
#include "QGSDownloaderGameVersionJson.h"
#include "QGSDownloaderAssetObject.h"
#include "QGSDownloaderLibrary.h"
#include "QGSDownloaderGameVersion.h"
#include "QGSDownloaderAssetIndexJson.h"
#include "QGSDownloaderForge.h"
#include "QGSDownloaderLiteLoader.h"
#include "QGSDownloaderOptifine.h"
#include "QGSIDownloadSource.h"
#include "../GameVersion/GameVersion.h"
#include "../Launcher/QGSGameDirectory.h"
#include "../GameVersion/GameVersionInfoList.h"

class QGSDownloaderFactory
{
public:
	QGSDownloaderFactory(QGSIDownloadSource * downloadSource, const QNetworkProxy & proxy = QNetworkProxy::NoProxy);

	QGSDownloaderFactory(const QGSDownloaderFactory & right) = delete;

	QGSDownloaderFactory(QGSDownloaderFactory && right) = delete;

	QGSDownloaderFactory & operator=(const QGSDownloaderFactory & right) = delete;

	QGSDownloaderFactory & operator=(QGSDownloaderFactory && right) = delete;

	virtual ~QGSDownloaderFactory();

	QGSDownloader * generateDownloader(QFile * targetFile, DownloadInfo & downloadInfo = DownloadInfo());
	/**/
	QGSDownloader * generateGameVersionInfoJsonDownloader(QFile * targetFile, DownloadInfo & downloadInfo = DownloadInfo());

	QGSDownloader * generateForgeVersionInfoJsonDownloader(QFile * targetFile, int offset = 1, int limit = 0, DownloadInfo & downloadInfo = DownloadInfo());

	QGSDownloader * generateLiteLoaderVersionInfoJsonDownloader(QFile * targetFile, DownloadInfo & downloadInfo = DownloadInfo());

	QGSDownloader * generateOptifineVersionInfoJsonDownloader(QFile * targetFile, DownloadInfo & downloadInfo = DownloadInfo());
	/**/
	QGSDownloader * generateLoggingDownloader(QFile * targetFile, const Logging & logging, DownloadInfo & downloadInfo = DownloadInfo());

	QGSDownloaderGameVersionJson * generateGameVersionJsonDownloader(const GameVersionInfo & versionInfo, QGSGameDirectory & gameDirectory, DownloadInfo & downloadInfo = DownloadInfo());

	QGSDownloaderLibrary * generateLibraryDownloader(const Library & library, QGSGameDirectory & gameDirectory, DownloadInfo & downloadInfo = DownloadInfo());

	QGSDownloaderGameVersion * generateGameVersionDownloader(const GameVersion & version, QGSGameDirectory & gameDirectory, const QString & category = "client", DownloadInfo & downloadInfo = DownloadInfo());

	QGSDownloaderAssetIndexJson * generateAssetIndexJsonDownloader(const AssetIndex & assetIndex, QGSGameDirectory & gameDirectory, DownloadInfo & downloadInfo = DownloadInfo());

	QGSDownloaderAssetObject * generateAssetObjectDownloader(const AssetObject & assetObject, QGSGameDirectory & gameDirectory, DownloadInfo & downloadInfo = DownloadInfo());
	/**/
	QGSDownloaderForge * generateForgeDownloader(QFile * targetFile, const QString & mcversion, const QString & version, const QString & category, const QString & format, const QString & branch = "", DownloadInfo & downloadInfo = DownloadInfo());

	QGSDownloaderLiteLoader * generateLiteLoaderDownloader(QFile * targetFile, const QString & mcversion, const QString & version, const QString & category = "universial", DownloadInfo & downloadInfo = DownloadInfo());

	QGSDownloaderOptifine * generateOptifineDownloader(QFile * targetFile, const QString & mcversion, const QString & type, const QString & patch, DownloadInfo & downloadInfo = DownloadInfo());
private:
	QGSIDownloadSource * mDownloadSourcePtr;
	QNetworkProxy mProxy;
};

/**/



