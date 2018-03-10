#pragma once

#include <QObject>
#include <QString>
#include <QUrl>

namespace ApiName
{
	static const QString FORGE{ "forge" };
	static const QString LITELOADER{ "liteloader" };
	static const QString OPTIFINE{ "optifine" };
	static const QString UNKNOWN{ "unknown" };
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

	virtual QUrl getLibraryUrlBase() = 0;

	virtual QUrl getVersionManifestUrl() = 0;

	virtual QUrl getVersionUrlBase() = 0;

	virtual QUrl getAssetIndexUrlBase() = 0;

	virtual QUrl getAssetUrlBase() = 0;

	virtual QUrl getApiUrlBase(const QString & apiName) = 0;

};