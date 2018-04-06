#pragma once

#include "QGSDownloadTask.h"
#include "QGSIDownloadSource.h"
#include "../GameVersion/QGSGameVersion.h"
#include "../Launcher/QGSGameDirectory.h"
#include "../GameVersion/QGSGameVersionInfoList.h"

class QGSGameVersionDownloadTask : public QGSDownloadTask
{
	Q_OBJECT

public:
	QGSGameVersionDownloadTask(const QGSGameVersion & version, const QString & category, QGSIDownloadSource * downloadSource, QGSGameDirectory & gameDirectory, int connectionCount = 4, const QNetworkProxy & proxy = QNetworkProxy::NoProxy, QObject *parent = nullptr);
	
	QGSGameVersionDownloadTask(const QGSGameVersionDownloadTask & right) = delete;

	QGSGameVersionDownloadTask(QGSGameVersionDownloadTask && right) = delete;

	QGSGameVersionDownloadTask & operator=(const QGSGameVersionDownloadTask & right) = delete;

	QGSGameVersionDownloadTask & operator=(QGSGameVersionDownloadTask && right) = delete;

	virtual ~QGSGameVersionDownloadTask();
};
