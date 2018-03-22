#pragma once

#include "QGSDownloadTask.h"

class QGSGameVersionDownloadTask : public QGSDownloadTask
{
	Q_OBJECT

public:
	QGSGameVersionDownloadTask(QFile * targetFile, const DownloadInfo & downloadInfo, const QNetworkProxy & proxy = QNetworkProxy::NoProxy, QObject *parent = nullptr);
	
	QGSGameVersionDownloadTask(const QGSGameVersionDownloadTask & right) = delete;

	QGSGameVersionDownloadTask(QGSGameVersionDownloadTask && right) = delete;

	QGSGameVersionDownloadTask & operator=(const QGSGameVersionDownloadTask & right) = delete;

	QGSGameVersionDownloadTask & operator=(QGSGameVersionDownloadTask && right) = delete;

	virtual ~QGSGameVersionDownloadTask();
};
