#pragma once

#include "QGSIBuilder.h"

class QGSGameVersionBuilder : public QGSIBuilder
{
	Q_OBJECT

public:
	friend class QGSGameVersionJsonDownloadTaskGenerationTask;
	friend class QGSGameVersionDownloadTaskGenerationTask;

	QGSGameVersionBuilder(QGSThreadPoolManager * threadPoolManagerPtr, 
		QGSGameVersionInfo & versionInfo,
		QGSGameDirectory * gameDirectory, 
		QGSDownloadTaskFactory * downloadTaskFactory, 
		QObject * parent = nullptr);

	QGSGameVersionBuilder(const QGSGameVersionBuilder & right) = delete;

	QGSGameVersionBuilder(QGSGameVersionBuilder && right) = delete;

	QGSGameVersionBuilder & operator=(const QGSGameVersionBuilder & right) = delete;

	QGSGameVersionBuilder & operator=(QGSGameVersionBuilder && right) = delete;

	virtual ~QGSGameVersionBuilder();

	bool isFileOverride();

	QGSGameVersionBuilder & setFileOverride(const bool fileOverride);

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
	QGSDownloadTaskGenerationTask * initGameVersionJsonDownloadTaskGenerationTask();
	QGSDownloadTaskGenerationTask * initGameVersionDownloadTaskGenerationTask();
private:
	QGSGameVersionInfo mVersionInfo;
	QGSGameDirectory * mGameDirectoryPtr;
	QGSDownloadTaskFactory * mDownloadTaskFactoryPtr;
	QList<QGSTask *> mTaskList;
	bool mFileOverride;

};

