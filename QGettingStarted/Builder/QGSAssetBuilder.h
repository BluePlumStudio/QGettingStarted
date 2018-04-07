#pragma once

#include "QGSIBuilder.h"

class QGSAssetBuilder : public QGSIBuilder
{
	Q_OBJECT

public:
	friend class QGSAssetIndexJsonDownloadTaskGenerationTask;
	friend class QGSAssetObjectDownloadTaskGenerationTask;

	QGSAssetBuilder(QGSGameVersionInfo & versionInfo, 
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
	QGSDownloadTaskGenerationTask * initAssetIndexJsonDownloadTaskGenerationTask();
	QGSDownloadTaskGenerationTask * initAssetObjectDownloadTaskGenerationTask();
private:
	QGSGameVersionInfo mVersionInfo;
	QGSGameDirectory * mGameDirectoryPtr;
	QGSDownloadTaskFactory * mDownloadTaskFactoryPtr;
	QList<QGSTask *> mTaskList;
	bool mFileOverride;

};

