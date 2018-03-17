#pragma once

#include "QGSDownloader.h"

class QGSDownloaderForge : public QGSDownloader
{
	Q_OBJECT

public:
	QGSDownloaderForge(QFile * targetFile, const DownloadInfo & downloadInfo, const QNetworkProxy & proxy = QNetworkProxy::NoProxy, QObject *parent = nullptr);
	
	QGSDownloaderForge(const QGSDownloaderForge & right) = delete;

	QGSDownloaderForge(QGSDownloaderForge && right) = delete;

	QGSDownloaderForge & operator=(const QGSDownloaderForge & right) = delete;

	QGSDownloaderForge & operator=(QGSDownloaderForge && right) = delete;

	virtual ~QGSDownloaderForge();
};
