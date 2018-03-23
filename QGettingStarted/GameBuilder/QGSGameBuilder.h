#pragma once

#include "QGSIGameBuilder.h"

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

protected:
	virtual void templateStart(QGSTask * task);
	virtual void templateStop(QGSTask * task);
	virtual void templateCancel(QGSTask * task);
private slots:
	void slotDownloadTaskStarted(QGSTask * task);
	void slotDownloadTaskFinished(QGSTask * task);
	void slotDownloadTaskStoped(QGSTask * task);
	void slotDownloadTaskCanceled(QGSTask * task);
	void slotDownloadTaskError(QGSNetworkError error, QGSTask * task);
private:
	QGSDownloadTask * initGameVersionJsonDownloadTask();
	bool initGameVersionDownloadTask();
	bool initLibraryDownloadTask();
	void eraseDownloadTask(QGSTask * downloadTask);
private:
	QMutex mMutex;

	QGSGameVersionInfo mVersionInfo;
	QGSGameDirectory * mGameDirectoryPtr;
	QGSDownloadTaskFactory * mDownloadTaskFactoryPtr;
	QList<QGSDownloadTask *> mDownloadTaskList;
	bool mFileOverride;

};
