#pragma once

#include <QString>
#include <QUrl>
#include <QObject>
#include <QFileInfo>

#include "QGSDownloadTask.h"
#include "QGSGameVersionJsonDownloadTask.h"
#include "QGSAssetObjectDownloadTask.h"
#include "QGSLibraryDownloadTask.h"
#include "QGSGameVersionDownloadTask.h"
#include "QGSAssetIndexJsonDownloadTask.h"
#include "QGSForgeDownloadTask.h"
#include "QGSLiteLoaderDownloadTask.h"
#include "QGSOptifineDownloadTask.h"
#include "QGSIDownloadSource.h"
#include "../GameVersion/QGSGameVersion.h"
#include "../Launcher/QGSGameDirectory.h"
#include "../GameVersion/QGSGameVersionInfoList.h"

class QGSDownloadTaskFactory
{
public:
	QGSDownloadTaskFactory(QGSIDownloadSource * downloadSource, const QNetworkProxy & proxy = QNetworkProxy::NoProxy);

	QGSDownloadTaskFactory(const QGSDownloadTaskFactory & right) = delete;

	QGSDownloadTaskFactory(QGSDownloadTaskFactory && right) = delete;

	QGSDownloadTaskFactory & operator=(const QGSDownloadTaskFactory & right) = delete;

	QGSDownloadTaskFactory & operator=(QGSDownloadTaskFactory && right) = delete;

	virtual ~QGSDownloadTaskFactory();

	QGSDownloadTask * generateDownloadTask(QFile * targetFile, DownloadInfo & downloadInfo = DownloadInfo());
	/**/
	QGSDownloadTask * generateGameVersionInfoJsonDownloadTask(QFile * targetFile, DownloadInfo & downloadInfo = DownloadInfo());

	QGSDownloadTask * generateForgeVersionInfoJsonDownloadTask(QFile * targetFile, int offset = 1, int limit = 0, DownloadInfo & downloadInfo = DownloadInfo());

	QGSDownloadTask * generateLiteLoaderVersionInfoJsonDownloadTask(QFile * targetFile, DownloadInfo & downloadInfo = DownloadInfo());

	QGSDownloadTask * generateOptifineVersionInfoJsonDownloadTask(QFile * targetFile, DownloadInfo & downloadInfo = DownloadInfo());
	/**/
	QGSDownloadTask * generateLoggingDownloadTask(QFile * targetFile, const QGSLogging & logging, DownloadInfo & downloadInfo = DownloadInfo());

	QGSGameVersionJsonDownloadTask * generateGameVersionJsonDownloadTask(const QGSGameVersionInfo & versionInfo, QGSGameDirectory & gameDirectory, DownloadInfo & downloadInfo = DownloadInfo());

	QGSLibraryDownloadTask * generateLibraryDownloadTask(const QGSLibrary & library, QGSGameDirectory & gameDirectory, DownloadInfo & downloadInfo = DownloadInfo());

	QGSGameVersionDownloadTask * generateGameVersionDownloadTask(const QGSGameVersion & version, QGSGameDirectory & gameDirectory, const QString & category = "client", DownloadInfo & downloadInfo = DownloadInfo());

	QGSAssetIndexJsonDownloadTask * generateAssetIndexJsonDownloadTask(const QGSAssetIndex & assetIndex, QGSGameDirectory & gameDirectory, DownloadInfo & downloadInfo = DownloadInfo());

	QGSAssetObjectDownloadTask * generateAssetObjectDownloadTask(const QGSAssetObject & assetObject, QGSGameDirectory & gameDirectory, DownloadInfo & downloadInfo = DownloadInfo());
	/**/
	QGSForgeDownloadTask * generateForgeDownloadTask(QFile * targetFile, const QString & mcversion, const QString & version, const QString & category, const QString & format, const QString & branch = "", DownloadInfo & downloadInfo = DownloadInfo());

	QGSLiteLoaderDownloadTask * generateLiteLoaderDownloadTask(QFile * targetFile, const QString & mcversion, const QString & version, const QString & category = "universial", DownloadInfo & downloadInfo = DownloadInfo());

	QGSOptifineDownloadTask * generateOptifineDownloadTask(QFile * targetFile, const QString & mcversion, const QString & type, const QString & patch, DownloadInfo & downloadInfo = DownloadInfo());
private:
	QGSIDownloadSource * mDownloadSourcePtr;
	QNetworkProxy mProxy;
};

/**/



