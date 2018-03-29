#pragma once

#include "QGSDownloadTask.h"

class QGSLibraryDownloadTask : public QGSDownloadTask
{
	Q_OBJECT

public:
	QGSLibraryDownloadTask(QFile * targetFile, const QGSDownloadInfo & downloadInfo, int threadCount = 4, const QNetworkProxy & proxy = QNetworkProxy::NoProxy, QObject *parent = nullptr);

	QGSLibraryDownloadTask(const QGSLibraryDownloadTask & right) = delete;

	QGSLibraryDownloadTask(QGSLibraryDownloadTask && right) = delete;

	QGSLibraryDownloadTask & operator=(const QGSLibraryDownloadTask & right) = delete;

	QGSLibraryDownloadTask & operator=(QGSLibraryDownloadTask && right) = delete;

	virtual ~QGSLibraryDownloadTask();
};
