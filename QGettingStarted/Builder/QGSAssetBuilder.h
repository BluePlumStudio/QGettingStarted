#pragma once

#include "QGSIBuilder.h"

class QGSAssetBuilder : public QGSIBuilder
{
	Q_OBJECT

public:
	friend class QGSAssetIndexJsonDownloadTaskGenerationTask;
	friend class QGSAssetObjectDownloadTaskGenerationTask;

	QGSAssetBuilder(QGSThreadPoolManager * threadPoolManagerPtr,
		QGSGameVersionInfo & versionInfo,
		QGSGameDirectory * gameDirectory, 
		QGSDownloadTaskFactory * downloadTaskFactory, 
		QObject * parent = nullptr);

	QGSAssetBuilder(const QGSAssetBuilder & right) = delete;

	QGSAssetBuilder(QGSAssetBuilder && right) = delete;

	QGSAssetBuilder & operator=(const QGSAssetBuilder & right) = delete;

	QGSAssetBuilder & operator=(QGSAssetBuilder && right) = delete;

	virtual ~QGSAssetBuilder();

	bool isFileOverride();

	QGSAssetBuilder & setFileOverride(const bool fileOverride);

	int getTaskListSize();
protected slots:
	virtual void templateStart(QGSTask * task);
	virtual void templateStop(QGSTask * task);
	virtual void templateCancel(QGSTask * task);
private slots:
	void slotDownloadTaskStarted(QGSTask * task);
	void slotDownloadTaskFinished(QGSTask * task);
	void slotDownloadTaskStoped(QGSTask * task);
	void slotDownloadTaskCanceled(QGSTask * task);
	void slotDownloadTaskError(QGSTask * task);
	void slotDownloadTaskDownloadProgress(qint64 bytesReceived, qint64 bytesTotal, QGSTask * task);
	void slotDownloadTaskDownloadError(QGSNetworkError error, QGSTask * task);
	void slotEraseTask(QGSTask * task);
	void slotFinished();
private:
	void initDownloadTasks();
	QGSAssetIndexJsonDownloadTaskGenerationTask * initAssetIndexJsonDownloadTaskGenerationTask();
	QGSAssetObjectDownloadTaskGenerationTask * initAssetObjectDownloadTaskGenerationTask();
private:
	QGSAssetIndexJsonDownloadTaskGenerationTask * mJsonDownloadTaskGenerationTask;
	QGSAssetObjectDownloadTaskGenerationTask * mObjectDownloadTaskGenerationTask;
	QGSGameVersionInfo mVersionInfo;
	QGSDownloadTaskFactory * mDownloadTaskFactoryPtr;
	QList<QGSTask *> mTaskList;
	QList<QGSTask *> mTaskDeletedLaterList;
	QGSAssetIndexInfo mAssetIndexInfo;
	bool mFileOverride;
	static QList<QGSGameDirectory *> mDirectoriesBuilding;

};

