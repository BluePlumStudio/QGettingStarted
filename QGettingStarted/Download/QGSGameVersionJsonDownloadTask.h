#pragma once

#include "QGSDownloadTask.h"
#include "QGSIDownloadSource.h"
#include "../GameVersion/QGSGameVersion.h"
#include "../Launcher/QGSGameDirectory.h"
#include "../GameVersion/QGSGameVersionInfoList.h"

class QGSGameVersionJsonDownloadTask : public QGSDownloadTask
{
	Q_OBJECT

public:
	QGSGameVersionJsonDownloadTask(const QGSGameVersionInfo & versionInfo, QGSIDownloadSource * downloadSource, QGSGameDirectory & gameDirectory, int connectionCount = 4, const QNetworkProxy & proxy = QNetworkProxy::NoProxy, QObject *parent = nullptr);

	QGSGameVersionJsonDownloadTask(const QGSGameVersionJsonDownloadTask & right) = delete;

	QGSGameVersionJsonDownloadTask(QGSGameVersionJsonDownloadTask && right) = delete;

	QGSGameVersionJsonDownloadTask & operator=(const QGSGameVersionJsonDownloadTask & right) = delete;

	QGSGameVersionJsonDownloadTask & operator=(QGSGameVersionJsonDownloadTask && right) = delete;

	virtual ~QGSGameVersionJsonDownloadTask();
};
