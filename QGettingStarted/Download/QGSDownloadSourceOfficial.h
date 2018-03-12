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

	virtual QUrl getLibraryUrlBase(QUrl & originUrl)override;

	virtual QUrl getVersionManifestUrl()override;

	virtual QUrl getVersionUrlBase(QUrl & originUrl)override;

	virtual QUrl getAssetIndexUrlBase(QUrl & originUrl)override;

	virtual QUrl getAssetUrlBase(QUrl & originUrl)override;

	virtual QUrl getApiUrlBase(const QString & apiName)override;
private:
	QMap<QString, QUrl> mApiUrlMap;
};
