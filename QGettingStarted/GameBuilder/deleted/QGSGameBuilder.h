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
	QGSDownloadTask * generateGameVersionJsonDownloadTask(const GameVersionInfo & gameVersionInfo);
	QGSDownloadTask * generateGameVersionDownloadTask(const GameVersionInfo & gameVersionInfo);
	QList<QGSDownloadTask *> generateLibrarDownloadTaskList(const GameVersionInfo & gameVersionInfo);
	QGSDownloadTask * generateAssetIndexJsonDownloadTask(const GameVersionInfo & gameVersionInfo);
	QList<QGSDownloadTask *> generateAssetObjectDownloadTaskList(const AssetIndexInfo & assetIndexInfo);
private slots:
	void slotDownloadStart(const DownloadInfo downloadInfo);
	void slotDownloadProgress(qint64 bytesReceived, qint64 bytesTotal, const DownloadInfo downloadInfo);
	void slotDownloadFinished(const DownloadInfo downloadInfo);
	void slotDownloadTimeout(const DownloadInfo downloadInfo);
	void slotDownloadError(QGSDownloadTask::Error error, const DownloadInfo downloadInfo);
	void slotFinished();
	void slotError(const QString errorString);
private:
	QEventLoop mEventLoop;
	QList<QGSDownloadTask *> mDownloadTaskPtrList;
	QGSDownloadTaskFactory * mDownloadTaskFactoryPtr;
	//QGSThreadPool mThreadPool;
};
