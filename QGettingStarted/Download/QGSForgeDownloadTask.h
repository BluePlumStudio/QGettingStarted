#pragma once

#include "QGSDownloadTask.h"
#include "QGSIDownloadSource.h"

class QGSForgeDownloadTask : public QGSDownloadTask
{
	Q_OBJECT

public:
	QGSForgeDownloadTask(QFile * targetFile, 
		QGSIDownloadSource * downloadSource,
		const QString & mcversion, 
		const QString & version, 
		const QString & category, 
		const QString & format, 
		const QString & branch = "", 
		int connectionCount = 4, 
		const QNetworkProxy & proxy = QNetworkProxy::NoProxy, 
		QObject *parent = nullptr);
	
	QGSForgeDownloadTask(const QGSForgeDownloadTask & right) = delete;

	QGSForgeDownloadTask(QGSForgeDownloadTask && right) = delete;

	QGSForgeDownloadTask & operator=(const QGSForgeDownloadTask & right) = delete;

	QGSForgeDownloadTask & operator=(QGSForgeDownloadTask && right) = delete;

	virtual ~QGSForgeDownloadTask();
};
