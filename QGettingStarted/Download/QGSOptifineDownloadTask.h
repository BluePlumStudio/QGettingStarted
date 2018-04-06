#pragma once

#include "QGSDownloadTask.h"

class QGSOptifineDownloadTask : public QGSDownloadTask
{
	Q_OBJECT

public:
	QGSOptifineDownloadTask(QFile * targetFile, const QGSDownloadInfo & downloadInfo, int connectionCount = 4, const QNetworkProxy & proxy = QNetworkProxy::NoProxy, QObject *parent = nullptr);
	
	QGSOptifineDownloadTask(const QGSOptifineDownloadTask & right) = delete;

	QGSOptifineDownloadTask(QGSOptifineDownloadTask && right) = delete;

	QGSOptifineDownloadTask & operator=(const QGSOptifineDownloadTask & right) = delete;

	QGSOptifineDownloadTask & operator=(QGSOptifineDownloadTask && right) = delete;

	virtual ~QGSOptifineDownloadTask();
};
