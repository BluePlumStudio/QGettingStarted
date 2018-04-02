#pragma once

#include <QObject>
#include <QTemporaryDir>
#include <QTemporaryFile>
#include <QMetaType>

#include "../Download/QGSDownloadTaskFactory.h"
#include "../Download/QGSDownloadSourceBMCLAPI.h"
#include "../Download/QGSDownloadSourceOfficial.h"
#include "../GameVersion/QGSAssetIndexInfoFactory.h"
#include "../GameVersion/QGSForgeVersionInfoListFactory.h"
#include "../GameVersion/QGSGameVersionInfoListFactory.h"
#include "../GameVersion/QGSLiteLoaderVersionInfoListFactory.h"
#include "../GameVersion/QGSOptifineVersionInfoListFactory.h"
#include "../Launcher/QGSGameDirectory.h"
#include "../Util/QGSThreadPool.h"

class QGSIBuilder :public QGSTask
{
	Q_OBJECT

public:
	QGSIBuilder(QObject * parent = nullptr);

	QGSIBuilder(const QGSIBuilder & right) = delete;

	QGSIBuilder(QGSIBuilder && right) = delete;

	QGSIBuilder & operator=(const QGSIBuilder & right) = delete;

	QGSIBuilder & operator=(QGSIBuilder && right) = delete;

	virtual ~QGSIBuilder();
signals:
	void downloadTaskStarted(QGSDownloadInfo downloadInfo);
	void downloadTaskFinished(QGSDownloadInfo downloadInfo);
	void downloadTaskStoped(QGSDownloadInfo downloadInfo);
	void downloadTaskCanceled(QGSDownloadInfo downloadInfo);
	void downloadTaskDownloadProgress(qint64 bytesReceived, qint64 bytesTotal, QGSDownloadInfo downloadInfo);
	void downloadTaskDownloadError(QGSNetworkError error, QGSDownloadInfo downloadInfo);
	void downloadTaskError(QGSDownloadInfo downloadInfo);
};
