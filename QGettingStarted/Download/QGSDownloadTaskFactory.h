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

class QGSDownloadTaskFactory :public QObject
{
	Q_OBJECT

public:
	QGSDownloadTaskFactory(QGSIDownloadSource * downloadSource, const QNetworkProxy & proxy = QNetworkProxy::NoProxy, QObject * parent = nullptr);

	QGSDownloadTaskFactory(const QGSDownloadTaskFactory & right) = delete;

	QGSDownloadTaskFactory(QGSDownloadTaskFactory && right) = delete;

	QGSDownloadTaskFactory & operator=(const QGSDownloadTaskFactory & right) = delete;

	QGSDownloadTaskFactory & operator=(QGSDownloadTaskFactory && right) = delete;

	virtual ~QGSDownloadTaskFactory();

	QGSDownloadTaskFactory & setConnectionCount(const int connectionCount = QGSDownloadTask::DefaultConnectionCount);

	int getConnectionCount()const;

	QGSDownloadTaskFactory & setLargeFileSize(const quint64 bytes);

	QGSDownloadTaskFactory & setSmallFileSize(const quint64 bytes);

	QGSDownloadTask * generateDownloadTask(QFile * targetFile, QGSDownloadInfo downloadInfo);
	/**/
	QGSDownloadTask * generateGameVersionInfoJsonDownloadTask(QFile * targetFile);

	QGSDownloadTask * generateForgeVersionInfoJsonDownloadTask(QFile * targetFile, int offset = 1, int limit = 0);

	QGSDownloadTask * generateLiteLoaderVersionInfoJsonDownloadTask(QFile * targetFile);

	QGSDownloadTask * generateOptifineVersionInfoJsonDownloadTask(QFile * targetFile);
	/**/
	QGSDownloadTask * generateLoggingDownloadTask(QFile * targetFile, const QGSLogging & logging);

	QGSGameVersionJsonDownloadTask * generateGameVersionJsonDownloadTask(const QGSGameVersionInfo & versionInfo, QGSGameDirectory & gameDirectory);

	QGSLibraryDownloadTask * generateLibraryDownloadTask(const QGSLibrary & library, QGSGameDirectory & gameDirectory);

	QGSGameVersionDownloadTask * generateGameVersionDownloadTask(const QGSGameVersion & version, QGSGameDirectory & gameDirectory, const QString & category = "client");

	QGSAssetIndexJsonDownloadTask * generateAssetIndexJsonDownloadTask(const QGSAssetIndex & assetIndex, QGSGameDirectory & gameDirectory);

	QGSAssetObjectDownloadTask * generateAssetObjectDownloadTask(const QGSAssetObject & assetObject, QGSGameDirectory & gameDirectory);
	/**/
	QGSForgeDownloadTask * generateForgeDownloadTask(QFile * targetFile, const QString & mcversion, const QString & version, const QString & category, const QString & format, const QString & branch = "");

	QGSLiteLoaderDownloadTask * generateLiteLoaderDownloadTask(QFile * targetFile, const QString & mcversion, const QString & version, const QString & category = "universal");

	QGSOptifineDownloadTask * generateOptifineDownloadTask(QFile * targetFile, const QString & mcversion, const QString & type, const QString & patch);
private:
	QGSIDownloadSource * mDownloadSourcePtr;
	QNetworkProxy mProxy;
	int mConnectionCount;
};

/**/



