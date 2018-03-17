#pragma once

#include "QGSDownloader.h"

class QGSDownloaderLiteLoader : public QGSDownloader
{
	Q_OBJECT

public:
	QGSDownloaderLiteLoader(QFile * targetFile, const DownloadInfo & downloadInfo, const QNetworkProxy & proxy = QNetworkProxy::NoProxy, QObject *parent = nullptr);
	
	QGSDownloaderLiteLoader(const QGSDownloaderLiteLoader & right) = delete;

	QGSDownloaderLiteLoader(QGSDownloaderLiteLoader && right) = delete;

	QGSDownloaderLiteLoader & operator=(const QGSDownloaderLiteLoader & right) = delete;

	QGSDownloaderLiteLoader & operator=(QGSDownloaderLiteLoader && right) = delete;

	virtual ~QGSDownloaderLiteLoader();
};
