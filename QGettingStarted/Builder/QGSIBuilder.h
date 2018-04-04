#pragma once

#include <QObject>
#include <QTemporaryDir>
#include <QTemporaryFile>
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
	void downloadTaskStarted(QGSDownloadInfo downloadInfo);
	void downloadTaskFinished(QGSDownloadInfo downloadInfo);
	void downloadTaskStoped(QGSDownloadInfo downloadInfo);
	void downloadTaskCanceled(QGSDownloadInfo downloadInfo);
	void downloadTaskDownloadProgress(qint64 bytesReceived, qint64 bytesTotal, QGSDownloadInfo downloadInfo);
	void downloadTaskDownloadError(QGSNetworkError error, QGSDownloadInfo downloadInfo);
	void downloadTaskError(QGSDownloadInfo downloadInfo);
protected:
	static QGSThreadPool mThreadPool;

	QMutex mMutex;
	QString mLastErrorString;
};
