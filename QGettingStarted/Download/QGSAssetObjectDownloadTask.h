#pragma once

#include "QGSDownloadTask.h"
#include "QGSIDownloadSource.h"
#include "../GameVersion/QGSGameVersion.h"
#include "../Launcher/QGSGameDirectory.h"

class QGSAssetObjectDownloadTask : public QGSDownloadTask
{
	Q_OBJECT

public:
	QGSAssetObjectDownloadTask(const QGSAssetObject & assetObject, QGSIDownloadSource * downloadSource, QGSGameDirectory & gameDirectory, int connectionCount = 4, const QNetworkProxy & proxy = QNetworkProxy::NoProxy, QObject *parent = nullptr);

	QGSAssetObjectDownloadTask(const QGSAssetObjectDownloadTask & right) = delete;

	QGSAssetObjectDownloadTask(QGSAssetObjectDownloadTask && right) = delete;

	QGSAssetObjectDownloadTask & operator=(const QGSAssetObjectDownloadTask & right) = delete;

	QGSAssetObjectDownloadTask & operator=(QGSAssetObjectDownloadTask && right) = delete;

	virtual ~QGSAssetObjectDownloadTask();
};
