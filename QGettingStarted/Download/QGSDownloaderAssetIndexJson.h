#pragma once

#include "QGSDownloader.h"

class QGSDownloaderAssetIndexJson : public QGSDownloader
{
	Q_OBJECT

public:
	QGSDownloaderAssetIndexJson(QFile * targetFile, const DownloadInfo & downloadInfo, const QNetworkProxy & proxy = QNetworkProxy::NoProxy, QObject *parent = nullptr);

	QGSDownloaderAssetIndexJson(const QGSDownloaderAssetIndexJson & right) = delete;

	QGSDownloaderAssetIndexJson(QGSDownloaderAssetIndexJson && right) = delete;

	QGSDownloaderAssetIndexJson & operator=(const QGSDownloaderAssetIndexJson & right) = delete;

	QGSDownloaderAssetIndexJson & operator=(QGSDownloaderAssetIndexJson && right) = delete;

	virtual ~QGSDownloaderAssetIndexJson();
};
