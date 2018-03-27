#pragma once

#include "QGSDownloadTask.h"

class QGSLiteLoaderDownloadTask : public QGSDownloadTask
{
	Q_OBJECT

public:
	QGSLiteLoaderDownloadTask(QFile * targetFile, const QGSDownloadInfo & downloadInfo, const QNetworkProxy & proxy = QNetworkProxy::NoProxy, QObject *parent = nullptr);
	
	QGSLiteLoaderDownloadTask(const QGSLiteLoaderDownloadTask & right) = delete;

	QGSLiteLoaderDownloadTask(QGSLiteLoaderDownloadTask && right) = delete;

	QGSLiteLoaderDownloadTask & operator=(const QGSLiteLoaderDownloadTask & right) = delete;

	QGSLiteLoaderDownloadTask & operator=(QGSLiteLoaderDownloadTask && right) = delete;

	virtual ~QGSLiteLoaderDownloadTask();
};
