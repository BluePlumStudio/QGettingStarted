#pragma once

#include "QGSDownloadTask.h"

class QGSAssetObjectDownloadTask : public QGSDownloadTask
{
	Q_OBJECT

public:
	QGSAssetObjectDownloadTask(QFile * targetFile, const QGSDownloadInfo & downloadInfo, int threadCount = 4, const QNetworkProxy & proxy = QNetworkProxy::NoProxy, QObject *parent = nullptr);

	QGSAssetObjectDownloadTask(const QGSAssetObjectDownloadTask & right) = delete;

	QGSAssetObjectDownloadTask(QGSAssetObjectDownloadTask && right) = delete;

	QGSAssetObjectDownloadTask & operator=(const QGSAssetObjectDownloadTask & right) = delete;

	QGSAssetObjectDownloadTask & operator=(QGSAssetObjectDownloadTask && right) = delete;

	virtual ~QGSAssetObjectDownloadTask();
};