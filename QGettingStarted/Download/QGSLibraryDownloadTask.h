#pragma once

#include "QGSDownloadTask.h"
#include "QGSIDownloadSource.h"
#include "../GameVersion/QGSGameVersion.h"
#include "../Launcher/QGSGameDirectory.h"

class QGSLibraryDownloadTask : public QGSDownloadTask
{
	Q_OBJECT

public:
	QGSLibraryDownloadTask(const QGSLibrary & library, QGSIDownloadSource * downloadSource, QGSGameDirectory & gameDirectory, int connectionCount = 4, const QNetworkProxy & proxy = QNetworkProxy::NoProxy, QObject *parent = nullptr);

	QGSLibraryDownloadTask(const QGSLibraryDownloadTask & right) = delete;

	QGSLibraryDownloadTask(QGSLibraryDownloadTask && right) = delete;

	QGSLibraryDownloadTask & operator=(const QGSLibraryDownloadTask & right) = delete;

	QGSLibraryDownloadTask & operator=(QGSLibraryDownloadTask && right) = delete;

	virtual ~QGSLibraryDownloadTask();
};
