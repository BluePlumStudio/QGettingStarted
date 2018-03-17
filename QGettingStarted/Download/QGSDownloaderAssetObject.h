#pragma once

#include "QGSDownloader.h"

class QGSDownloaderAssetObject : public QGSDownloader
{
	Q_OBJECT

public:
	QGSDownloaderAssetObject(QFile * targetFile, const DownloadInfo & downloadInfo, const QNetworkProxy & proxy = QNetworkProxy::NoProxy, QObject *parent = nullptr);

	QGSDownloaderAssetObject(const QGSDownloaderAssetObject & right) = delete;

	QGSDownloaderAssetObject(QGSDownloaderAssetObject && right) = delete;

	QGSDownloaderAssetObject & operator=(const QGSDownloaderAssetObject & right) = delete;

	QGSDownloaderAssetObject & operator=(QGSDownloaderAssetObject && right) = delete;

	virtual ~QGSDownloaderAssetObject();
};
