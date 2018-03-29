#pragma once

#include "QGSDownloadTask.h"

class QGSAssetIndexJsonDownloadTask : public QGSDownloadTask
{
	Q_OBJECT

public:
	QGSAssetIndexJsonDownloadTask(QFile * targetFile, const QGSDownloadInfo & downloadInfo, int threadCount = 4, const QNetworkProxy & proxy = QNetworkProxy::NoProxy, QObject *parent = nullptr);

	QGSAssetIndexJsonDownloadTask(const QGSAssetIndexJsonDownloadTask & right) = delete;

	QGSAssetIndexJsonDownloadTask(QGSAssetIndexJsonDownloadTask && right) = delete;

	QGSAssetIndexJsonDownloadTask & operator=(const QGSAssetIndexJsonDownloadTask & right) = delete;

	QGSAssetIndexJsonDownloadTask & operator=(QGSAssetIndexJsonDownloadTask && right) = delete;

	virtual ~QGSAssetIndexJsonDownloadTask();
};
