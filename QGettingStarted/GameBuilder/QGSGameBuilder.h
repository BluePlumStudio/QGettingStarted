#pragma once

#include <QList>

#include "QGSIGameBuilder.h"
#include "../Util/QGSThreadPool.h"

class QGSGameBuilder : public QGSIGameBuilder
{
	Q_OBJECT

public:
	QGSGameBuilder(QGSIDownloadSource * downloadSource, QGSGameDirectory * gameDirectory, QObject * parent = nullptr);

	QGSGameBuilder(const QGSGameBuilder & right) = default;

	QGSGameBuilder(QGSGameBuilder && right) = default;

	QGSGameBuilder & operator=(const QGSGameBuilder & right) = default;

	QGSGameBuilder & operator=(QGSGameBuilder && right) = default;

	virtual ~QGSGameBuilder();
	/*²Ù×÷*/
	bool start(const GameVersionInfo & gameVersionInfo);

	bool cancel();
	/**/
private:
	QGSDownloader * generateGameVersionJsonDownloader(const GameVersionInfo & gameVersionInfo);
	QGSDownloader * generateGameVersionDownloader(const GameVersionInfo & gameVersionInfo);
	QList<QGSDownloader *> generateLibrarDownloaderList(const GameVersionInfo & gameVersionInfo);
	QGSDownloader * generateAssetIndexJsonDownloader(const GameVersionInfo & gameVersionInfo);
	QList<QGSDownloader *> generateAssetObjectDownloaderList(const AssetIndexInfo & assetIndexInfo);
private slots:
	void slotDownloadStart(const DownloadInfo downloadInfo);
	void slotDownloadProgress(qint64 bytesReceived, qint64 bytesTotal, const DownloadInfo downloadInfo);
	void slotDownloadFinished(const DownloadInfo downloadInfo);
	void slotDownloadTimeout(const DownloadInfo downloadInfo);
	void slotDownloadError(QGSDownloader::Error error, const DownloadInfo downloadInfo);
	void slotFinished();
	void slotError(const QString errorString);
private:
	QEventLoop mEventLoop;
	QList<QGSDownloader *> mDownloaderPtrList;
	QGSDownloaderFactory * mDownloaderFactoryPtr;
	QGSThreadPool mThreadPool;
};
