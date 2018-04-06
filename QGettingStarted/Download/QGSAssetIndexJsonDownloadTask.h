#pragma once

#include "QGSDownloadTask.h"
#include "QGSIDownloadSource.h"
#include "../GameVersion/QGSGameVersion.h"
#include "../Launcher/QGSGameDirectory.h"
#include "QGSAssetIndexJsonDownloadTask.h"

class QGSAssetIndexJsonDownloadTask : public QGSDownloadTask
{
	Q_OBJECT

public:
	QGSAssetIndexJsonDownloadTask(const QGSAssetIndex & assetIndex, QGSIDownloadSource * downloadSource, QGSGameDirectory & gameDirectory, int connectionCount = 4, const QNetworkProxy & proxy = QNetworkProxy::NoProxy, QObject *parent = nullptr);

	QGSAssetIndexJsonDownloadTask(const QGSAssetIndexJsonDownloadTask & right) = delete;

	QGSAssetIndexJsonDownloadTask(QGSAssetIndexJsonDownloadTask && right) = delete;

	QGSAssetIndexJsonDownloadTask & operator=(const QGSAssetIndexJsonDownloadTask & right) = delete;

	QGSAssetIndexJsonDownloadTask & operator=(QGSAssetIndexJsonDownloadTask && right) = delete;

	virtual ~QGSAssetIndexJsonDownloadTask();
};
