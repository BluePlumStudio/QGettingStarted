#pragma once

#include <QMap>

#include "QGSIDownloadSource.h"

class QGSDownloadSourceOfficial : public QGSIDownloadSource
{
	Q_OBJECT

public:
	QGSDownloadSourceOfficial(QObject *parent = nullptr);

	QGSDownloadSourceOfficial(const QGSDownloadSourceOfficial & right) = delete;

	QGSDownloadSourceOfficial(QGSDownloadSourceOfficial && right) = delete;

	QGSDownloadSourceOfficial & operator=(const QGSDownloadSourceOfficial & right) = delete;

	QGSDownloadSourceOfficial & operator=(QGSDownloadSourceOfficial && right) = delete;

	virtual ~QGSDownloadSourceOfficial();

	virtual QUrl generateGameVersionInfoJsonUrl()override;
	virtual QUrl generateForgeVersionInfoJsonUrl(int offset = 1, int limit = 0)override;
	virtual QUrl generateLiteLoaderVersionInfoJsonUrl()override;
	virtual QUrl generateOptifineVersionInfoJsonUrl()override;
	virtual QUrl generateLoggingUrl(const Logging & logging)override;
	virtual QUrl generateGameVersionJsonUrl(const GameVersionInfo & versionInfo)override;
	virtual QUrl generateLibraryUrl(const Library & library)override;
	virtual QUrl generateGameVersionUrl(const GameVersion & version, const QString & category)override;
	virtual QUrl generateAssetIndexJsonUrl(const AssetIndex & assetIndex)override;
	virtual QUrl generateAssetObjectUrl(const AssetObject & assetObject)override;
	virtual QUrl generateForgeUrl(const QString & mcversion, const QString & version, const QString & category, const QString & format, const QString & branch = "")override;
	virtual QUrl generateLiteLoaderUrl(QString mcversion, QString version, const QString & category)override;
	virtual QUrl generateOptifineUrl(const QString & mcversion, const QString & type, const QString & patch)override;

private:
};
