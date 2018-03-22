#pragma once

#include "QGSDownloadTask.h"

class QGSForgeDownloadTask : public QGSDownloadTask
{
	Q_OBJECT

public:
	QGSForgeDownloadTask(QFile * targetFile, const DownloadInfo & downloadInfo, const QNetworkProxy & proxy = QNetworkProxy::NoProxy, QObject *parent = nullptr);
	
	QGSForgeDownloadTask(const QGSForgeDownloadTask & right) = delete;

	QGSForgeDownloadTask(QGSForgeDownloadTask && right) = delete;

	QGSForgeDownloadTask & operator=(const QGSForgeDownloadTask & right) = delete;

	QGSForgeDownloadTask & operator=(QGSForgeDownloadTask && right) = delete;

	virtual ~QGSForgeDownloadTask();
};
