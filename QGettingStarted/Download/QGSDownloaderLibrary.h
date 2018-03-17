#pragma once

#include "QGSDownloader.h"

class QGSDownloaderLibrary : public QGSDownloader
{
	Q_OBJECT

public:
	QGSDownloaderLibrary(QFile * targetFile, const DownloadInfo & downloadInfo, const QNetworkProxy & proxy = QNetworkProxy::NoProxy, QObject *parent = nullptr);

	QGSDownloaderLibrary(const QGSDownloaderLibrary & right) = delete;

	QGSDownloaderLibrary(QGSDownloaderLibrary && right) = delete;

	QGSDownloaderLibrary & operator=(const QGSDownloaderLibrary & right) = delete;

	QGSDownloaderLibrary & operator=(QGSDownloaderLibrary && right) = delete;

	virtual ~QGSDownloaderLibrary();
};
