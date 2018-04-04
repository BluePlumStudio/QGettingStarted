#pragma once

#include <QMap>

#include "QGSIDownloadSource.h"

class QGSOfficialDownloadSource : public QGSIDownloadSource
{
	Q_OBJECT

public:
	QGSOfficialDownloadSource(QObject *parent = nullptr);

	QGSOfficialDownloadSource(const QGSOfficialDownloadSource & right) = delete;

	QGSOfficialDownloadSource(QGSOfficialDownloadSource && right) = delete;

	QGSOfficialDownloadSource & operator=(const QGSOfficialDownloadSource & right) = delete;

	QGSOfficialDownloadSource & operator=(QGSOfficialDownloadSource && right) = delete;

	virtual ~QGSOfficialDownloadSource();

	virtual QUrl generateGameVersionInfoJsonUrl()override;
	virtual QUrl generateForgeVersionInfoJsonUrl(int offset = 1, int limit = 0)override;
	virtual QUrl generateLiteLoaderVersionInfoJsonUrl()override;
	virtual QUrl generateOptifineVersionInfoJsonUrl()override;
	virtual QUrl generateLoggingUrl(const QGSLogging & logging)override;
	virtual QUrl generateGameVersionJsonUrl(const QGSGameVersionInfo & versionInfo)override;
	virtual QUrl generateLibraryUrl(const QGSLibrary & library)override;
	virtual QUrl generateGameVersionUrl(const QGSGameVersion & version, const QString & category)override;
	virtual QUrl generateAssetIndexJsonUrl(const QGSAssetIndex & assetIndex)override;
	virtual QUrl generateAssetObjectUrl(const QGSAssetObject & assetObject)override;
	virtual QUrl generateForgeUrl(const QString & mcversion, const QString & version, const QString & category, const QString & format, const QString & branch = "")override;
	virtual QUrl generateLiteLoaderUrl(QString mcversion, QString version, const QString & category)override;
	virtual QUrl generateOptifineUrl(const QString & mcversion, const QString & type, const QString & patch)override;

private:
};
