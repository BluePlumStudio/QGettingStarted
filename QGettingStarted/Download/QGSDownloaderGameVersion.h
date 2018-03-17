#pragma once

#include "QGSDownloader.h"

class QGSDownloaderGameVersion : public QGSDownloader
{
	Q_OBJECT

public:
	QGSDownloaderGameVersion(QFile * targetFile, const DownloadInfo & downloadInfo, const QNetworkProxy & proxy = QNetworkProxy::NoProxy, QObject *parent = nullptr);
	
	QGSDownloaderGameVersion(const QGSDownloaderGameVersion & right) = delete;

	QGSDownloaderGameVersion(QGSDownloaderGameVersion && right) = delete;

	QGSDownloaderGameVersion & operator=(const QGSDownloaderGameVersion & right) = delete;

	QGSDownloaderGameVersion & operator=(QGSDownloaderGameVersion && right) = delete;

	virtual ~QGSDownloaderGameVersion();
};
