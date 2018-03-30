#pragma once

#include "QGSIGameBuilder.h"
#include "QGSDownloadTaskGenerationTask.h"

#include <QMutex>

class QGSGameBuilder :public QGSIGameBuilder
{
	Q_OBJECT

public:
	QGSGameBuilder(QGSGameVersionInfo & versionInfo, QGSGameDirectory * gameDirectory, QGSDownloadTaskFactory * downloadTaskFactory);

	QGSGameBuilder(const QGSGameBuilder & right) = delete;

	QGSGameBuilder(QGSGameBuilder && right) = delete;

	QGSGameBuilder & operator=(const QGSGameBuilder & right) = delete;

	QGSGameBuilder & operator=(QGSGameBuilder && right) = delete;

	virtual ~QGSGameBuilder();

	bool isFileOverride();

	QGSGameBuilder & setFileOverride(const bool fileOverride);

	QString getLastErrorString();

	int getTaskListSize();

	static QGSThreadPool & getThreadPool();
protected:
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
	void slotEraseDownloadTask(QGSTask * downloadTask);
	void slotFinished();
private:
	friend class GameVersionJsonDownloadTaskGenerationTask;
	friend class GameVersionDownloadTaskGenerationTask;
	friend class LibraryDownloadTasksGenerationTask;
	friend class AssetIndexJsonDownloadTaskGenerationTask;
	friend class AssetObjectDownloadTasksGenerationTask;

	void initDownloadTasks();
	QGSDownloadTask * initGameVersionJsonDownloadTask();
	bool initGameVersionDownloadTask();
	bool initLibraryDownloadTasks();
	QGSDownloadTask *  initAssetIndexJsonDownloadTask();
	bool initAssetObjectDownloadTasks();

	void deleteTasksFinished();
private:
	static QGSThreadPool mThreadPool;
	QMutex mMutex;
	QTimer * mTimerPtr;

	QGSAssetIndexInfo mAssetIndexInfo;
	QGSGameVersionInfo mVersionInfo;
	QGSGameDirectory * mGameDirectoryPtr;
	QGSDownloadTaskFactory * mDownloadTaskFactoryPtr;
	QList<QGSTask *> mTaskList;
	QList<QGSTask *> mTaskWillBeDeletedList;
	bool mFileOverride;
	QString mLastErrorString;
};

/**/

/*
class GameVersionJsonDownloadTaskGenerationTask :public QGSDownloadTaskGenerationTask
{
	Q_OBJECT

public:
	GameVersionJsonDownloadTaskGenerationTask(QGSGameBuilder * gameBuilder);

	virtual ~GameVersionJsonDownloadTaskGenerationTask();
protected:
	virtual void templateStart(QGSTask * task);
private:
	QGSGameBuilder * mGameBuilderPtr;
};

class GameVersionDownloadTaskGenerationTask :public QGSDownloadTaskGenerationTask
{
	Q_OBJECT

public:
	GameVersionDownloadTaskGenerationTask(QGSGameBuilder * gameBuilder);

	virtual ~GameVersionDownloadTaskGenerationTask();

protected:
	virtual void templateStart(QGSTask * task);
private:
	QGSGameBuilder * mGameBuilderPtr;
};

class LibraryDownloadTasksGenerationTask :public QGSDownloadTaskGenerationTask
{
	Q_OBJECT

public:
	LibraryDownloadTasksGenerationTask(QGSGameBuilder * gameBuilder);

	virtual ~LibraryDownloadTasksGenerationTask();
protected:
	virtual void templateStart(QGSTask * task);
private:
	QGSGameBuilder * mGameBuilderPtr;
};

class AssetIndexJsonDownloadTaskGenerationTask :public QGSDownloadTaskGenerationTask
{
	Q_OBJECT

public:
	AssetIndexJsonDownloadTaskGenerationTask(QGSGameBuilder * gameBuilder);

	virtual ~AssetIndexJsonDownloadTaskGenerationTask();
protected:
	virtual void templateStart(QGSTask * task);
private:
	QGSGameBuilder * mGameBuilderPtr;
};

class AssetObjectDownloadTasksGenerationTask :public QGSDownloadTaskGenerationTask
{
	Q_OBJECT

public:
	AssetObjectDownloadTasksGenerationTask(QGSGameBuilder * gameBuilder);

	virtual ~AssetObjectDownloadTasksGenerationTask();

protected:
	virtual void templateStart(QGSTask * task);
private:
	QGSGameBuilder * mGameBuilderPtr;
};
*/