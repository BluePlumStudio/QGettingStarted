#pragma once

#include <QObject>
#include <QTemporaryDir>
#include <QTemporaryFile>

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

class QGSIGameBuilder :public QGSTask
{
	Q_OBJECT

public:
	QGSIGameBuilder();

	QGSIGameBuilder(const QGSIGameBuilder & right) = delete;

	QGSIGameBuilder(QGSIGameBuilder && right) = delete;

	QGSIGameBuilder & operator=(const QGSIGameBuilder & right) = delete;

	QGSIGameBuilder & operator=(QGSIGameBuilder && right) = delete;

	virtual ~QGSIGameBuilder();
signals:
	void downloadTaskStarted(QGSTask * task);
	void downloadTaskFinished(QGSTask * task);
	void downloadTaskStoped(QGSTask * task);
	void downloadTaskCanceled(QGSTask * task);
	void downloadTaskDownloadError(QGSNetworkError error, QGSTask * task);
	void downloadTaskError(QGSTask * task);
};
