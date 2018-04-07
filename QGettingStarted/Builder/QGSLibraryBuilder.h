#pragma once

#include "QGSIBuilder.h"

class QGSLibraryBuilder : public QGSIBuilder
{
	Q_OBJECT

public:
	QGSLibraryBuilder(QGSGameVersionInfo & versionInfo, 
		QGSGameDirectory * gameDirectory, 
		QGSDownloadTaskFactory * downloadTaskFactory, 
		QObject * parent = nullptr);

	QGSLibraryBuilder(const QGSLibraryBuilder & right) = delete;

	QGSLibraryBuilder(QGSLibraryBuilder && right) = delete;

	QGSLibraryBuilder & operator=(const QGSLibraryBuilder & right) = delete;

	QGSLibraryBuilder & operator=(QGSLibraryBuilder && right) = delete;

	virtual ~QGSLibraryBuilder();

	bool isFileOverride();

	QGSLibraryBuilder & setFileOverride(const bool fileOverride);

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
	bool initLibraryDownloadTasks();
private:
	QGSGameVersionInfo mVersionInfo;
	QGSGameDirectory * mGameDirectoryPtr;
	QGSDownloadTaskFactory * mDownloadTaskFactoryPtr;
	QList<QGSTask *> mTaskList;
	bool mFileOverride;

};

