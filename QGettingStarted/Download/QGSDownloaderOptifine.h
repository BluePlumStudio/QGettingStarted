#pragma once

#include "QGSDownloader.h"

class QGSDownloaderOptifine : public QGSDownloader
{
	Q_OBJECT

public:
	QGSDownloaderOptifine(QFile * targetFile, const DownloadInfo & downloadInfo, const QNetworkProxy & proxy = QNetworkProxy::NoProxy, QObject *parent = nullptr);
	
	QGSDownloaderOptifine(const QGSDownloaderOptifine & right) = delete;

	QGSDownloaderOptifine(QGSDownloaderOptifine && right) = delete;

	QGSDownloaderOptifine & operator=(const QGSDownloaderOptifine & right) = delete;

	QGSDownloaderOptifine & operator=(QGSDownloaderOptifine && right) = delete;

	virtual ~QGSDownloaderOptifine();
};
