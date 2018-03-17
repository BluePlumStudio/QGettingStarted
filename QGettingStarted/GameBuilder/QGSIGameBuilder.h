#pragma once

#include <QObject>
#include <QTemporaryDir>
#include <QTemporaryFile>

#include "../Download/QGSDownloaderFactory.h"
#include "../Download/QGSDownloadSourceBMCLAPI.h"
#include "../Download/QGSDownloadSourceOfficial.h"
#include "../GameVersion/QGSAssetIndexInfoFactory.h"
#include "../GameVersion/QGSForgeVersionInfoListFactory.h"
#include "../GameVersion/QGSGameVersionInfoListFactory.h"
#include "../GameVersion/QGSLiteLoaderVersionInfoListFactory.h"
#include "../GameVersion/QGSOptifineVersionInfoListFactory.h"
#include "../Launcher/QGSGameDirectory.h"

class QGSIGameBuilder : public QObject
{
	Q_OBJECT

public:
	QGSIGameBuilder(QGSIDownloadSource * downloadSource, QGSGameDirectory * gameDirectory, QObject * parent = nullptr);

	QGSIGameBuilder(const QGSIGameBuilder & right) = default;

	QGSIGameBuilder(QGSIGameBuilder && right) = default;

	QGSIGameBuilder & operator=(const QGSIGameBuilder & right) = default;

	QGSIGameBuilder & operator=(QGSIGameBuilder && right) = default;

	virtual ~QGSIGameBuilder();

	QGSIGameBuilder & setMaxConnectionCount(const int maxConnectionCount);

	QGSIGameBuilder & setDownloadTimeout(const int msec);

	int getDownloadTimeout()const;

	int getMaxConnectionCount()const;

signals:
	void downloadStart(const DownloadInfo downloadInfo);
	void downloadProgress(qint64 bytesReceived, qint64 bytesTotal, const DownloadInfo downloadInfo);
	void downloadFinished(const DownloadInfo downloadInfo);
	void downloadtimeout(const DownloadInfo downloadInfo);
	void downloadError(QGSDownloader::Error error, const DownloadInfo downloadInfo);
	void finished();
	void error(const QString errorString);
protected:
	QGSIDownloadSource * mDownloadSourcePtr;
	QGSGameDirectory * mGameDirectoryPtr;
	int mMaxConnectionCount;
	int mDownloadTimeout;
	QTemporaryDir mTemporaryDir;
};
