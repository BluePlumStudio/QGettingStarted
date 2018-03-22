#pragma once

#include "QGSDownloadTask.h"

class QGSGameVersionJsonDownloadTask : public QGSDownloadTask
{
	Q_OBJECT

public:
	QGSGameVersionJsonDownloadTask(QFile * targetFile, const DownloadInfo & downloadInfo, const QNetworkProxy & proxy = QNetworkProxy::NoProxy, QObject *parent = nullptr);

	QGSGameVersionJsonDownloadTask(const QGSGameVersionJsonDownloadTask & right) = delete;

	QGSGameVersionJsonDownloadTask(QGSGameVersionJsonDownloadTask && right) = delete;

	QGSGameVersionJsonDownloadTask & operator=(const QGSGameVersionJsonDownloadTask & right) = delete;

	QGSGameVersionJsonDownloadTask & operator=(QGSGameVersionJsonDownloadTask && right) = delete;

	virtual ~QGSGameVersionJsonDownloadTask();
};
