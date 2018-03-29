#pragma once

#include "QGSDownloadTask.h"

class QGSGameVersionJsonDownloadTask : public QGSDownloadTask
{
	Q_OBJECT

public:
	QGSGameVersionJsonDownloadTask(QFile * targetFile, const QGSDownloadInfo & downloadInfo, int threadCount = 4, const QNetworkProxy & proxy = QNetworkProxy::NoProxy, QObject *parent = nullptr);

	QGSGameVersionJsonDownloadTask(const QGSGameVersionJsonDownloadTask & right) = delete;

	QGSGameVersionJsonDownloadTask(QGSGameVersionJsonDownloadTask && right) = delete;

	QGSGameVersionJsonDownloadTask & operator=(const QGSGameVersionJsonDownloadTask & right) = delete;

	QGSGameVersionJsonDownloadTask & operator=(QGSGameVersionJsonDownloadTask && right) = delete;

	virtual ~QGSGameVersionJsonDownloadTask();
};
