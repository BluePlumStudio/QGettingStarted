#pragma once

#include <QMap>

#include "QGSIDownloadSource.h"

class QGSDownloadSourceBMCLAPI : public QGSIDownloadSource
{
	Q_OBJECT

public:
	QGSDownloadSourceBMCLAPI(QObject *parent = nullptr);

	QGSDownloadSourceBMCLAPI(const QGSDownloadSourceBMCLAPI & right) = delete;

	QGSDownloadSourceBMCLAPI(QGSDownloadSourceBMCLAPI && right) = delete;

	QGSDownloadSourceBMCLAPI & operator=(const QGSDownloadSourceBMCLAPI & right) = delete;

	QGSDownloadSourceBMCLAPI & operator=(QGSDownloadSourceBMCLAPI && right) = delete;

	virtual ~QGSDownloadSourceBMCLAPI();

	virtual QUrl getLibraryUrlBase()override;

	virtual QUrl getVersionManifestUrl()override;

	virtual QUrl getVersionUrlBase()override;

	virtual QUrl getAssetIndexUrlBase()override;

	virtual QUrl getAssetUrlBase()override;

	virtual QUrl getApiUrlBase(const QString & apiName)override;
private:
	QMap<QString, QUrl> mApiUrlMap;
};
