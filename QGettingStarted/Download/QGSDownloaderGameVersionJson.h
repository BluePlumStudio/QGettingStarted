#pragma once

#include "QGSDownloader.h"

class QGSDownloaderGameVersionJson : public QGSDownloader
{
	Q_OBJECT

public:
	QGSDownloaderGameVersionJson(QFile * targetFile, const DownloadInfo & downloadInfo, const QNetworkProxy & proxy = QNetworkProxy::NoProxy, QObject *parent = nullptr);

	QGSDownloaderGameVersionJson(const QGSDownloaderGameVersionJson & right) = delete;

	QGSDownloaderGameVersionJson(QGSDownloaderGameVersionJson && right) = delete;

	QGSDownloaderGameVersionJson & operator=(const QGSDownloaderGameVersionJson & right) = delete;

	QGSDownloaderGameVersionJson & operator=(QGSDownloaderGameVersionJson && right) = delete;

	virtual ~QGSDownloaderGameVersionJson();
};
