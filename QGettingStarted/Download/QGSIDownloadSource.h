#pragma once

#include <QObject>
#include <QString>
#include <QUrl>

#include "GameVersion/QGSGameVersion.h"
#include "GameVersion/QGSGameVersionInfoList.h"

namespace ApiName
{
	static const QString Forge{ "forge" };
	static const QString LiteLoader{ "liteloader" };
	static const QString Optifine{ "optifine" };
	static const QString Unknown{ "unknown" };
}

class QGSIDownloadSource : public QObject
{
	Q_OBJECT

public:
	QGSIDownloadSource(QObject *parent = nullptr);

	QGSIDownloadSource(const QGSIDownloadSource & right) = delete;

	QGSIDownloadSource(QGSIDownloadSource && right) = delete;

	QGSIDownloadSource & operator=(const QGSIDownloadSource & right) = delete;

	QGSIDownloadSource & operator=(QGSIDownloadSource && right) = delete;

	virtual ~QGSIDownloadSource();

	virtual QUrl generateGameVersionInfoJsonUrl() = 0;
	virtual QUrl generateForgeVersionInfoJsonUrl(int offset = 1, int limit = 0) = 0;
	virtual QUrl generateLiteLoaderVersionInfoJsonUrl() = 0;
	virtual QUrl generateOptifineVersionInfoJsonUrl() = 0;
	virtual QUrl generateLoggingUrl(const QGSLogging & logging) = 0;
	virtual QUrl generateGameVersionJsonUrl(const QGSGameVersionInfo & versionInfo) = 0;
	virtual QUrl generateLibraryUrl(const QGSLibrary & library) = 0;
	virtual QUrl generateGameVersionUrl(const QGSGameVersion & version, const QString & category) = 0;
	virtual QUrl generateAssetIndexJsonUrl(const QGSAssetIndex & assetIndex) = 0;
	virtual QUrl generateAssetObjectUrl(const QGSAssetObject & assetObject) = 0;
	virtual QUrl generateForgeUrl(const QString & mcversion, const QString & version, const QString & category, const QString & format, const QString & branch = "") = 0;
	virtual QUrl generateLiteLoaderUrl(QString mcversion, QString version, const QString & category) = 0;
	virtual QUrl generateOptifineUrl(const QString & mcversion, const QString & type, const QString & patch) = 0;

};
