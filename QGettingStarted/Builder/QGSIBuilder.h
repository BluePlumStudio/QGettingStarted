#pragma once

#include <QObject>
#include <QSharedPointer>
#include <QMetaType>
#include <QMutex>

#include "../Download/QGSDownloadTaskFactory.h"
#include "../Download/QGSBMCLAPIDownloadSource.h"
#include "../Download/QGSOfficialDownloadSource.h"
#include "../GameVersion/QGSAssetIndexInfoFactory.h"
#include "../GameVersion/QGSForgeVersionInfoListFactory.h"
#include "../GameVersion/QGSGameVersionInfoListFactory.h"
#include "../GameVersion/QGSLiteLoaderVersionInfoListFactory.h"
#include "../GameVersion/QGSOptifineVersionInfoListFactory.h"
#include "../Launcher/QGSGameDirectory.h"
#include "../Util/QGSThreadPool.h"
#include "QGSDownloadTaskGenerationTask.h"

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

	static QGSThreadPool & getThreadPool();

	QString getLastErrorString();
signals:
	void downloadTaskStarted(QGSDownloadTask * task);
	void downloadTaskFinished(QGSDownloadTask* task);
	void downloadTaskStoped(QGSDownloadTask * task);
	void downloadTaskCanceled(QGSDownloadTask * task);
	void downloadTaskDownloadProgress(qint64 bytesReceived, qint64 bytesTotal, QGSDownloadTask * task);
	void downloadTaskDownloadError(QGSNetworkError error, QGSDownloadTask * task);
	void downloadTaskError(QGSDownloadTask * task);
protected slots:
	void setLastErrorString(QString lastErrorString);
protected:
	static QGSThreadPool mThreadPool;

	QMutex mMutex;
	QString mLastErrorString;
};
