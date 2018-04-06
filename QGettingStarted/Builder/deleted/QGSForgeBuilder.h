#pragma once

#include <QMutex>

#include "QGSIBuilder.h"

class QGSForgeBuilder :public QGSIBuilder
{
	Q_OBJECT

public:
	QGSForgeBuilder(QGSForgeVersionInfo & versionInfo, QGSGameDirectory * gameDirectory, QGSDownloadTaskFactory * downloadTaskFactory, QObject * parent = nullptr);

	QGSForgeBuilder(const QGSForgeBuilder & right) = delete;

	QGSForgeBuilder(QGSForgeBuilder && right) = delete;

	QGSForgeBuilder & operator=(const QGSForgeBuilder & right) = delete;

	QGSForgeBuilder & operator=(QGSForgeBuilder && right) = delete;

	virtual ~QGSForgeBuilder();

	bool isFileOverride();

	QGSForgeBuilder & setFileOverride(const bool fileOverride);

	int getTaskListSize();
signals:
	void installationError(QGSForgeBuilder * forgetBuilder);
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
private:
	bool initDownloadDirectory();
	QGSDownloadTask * initForgeDownloadTask();
	bool installForge();
	bool initLibraryDownloadTasks();
	void slotEraseDownloadTask(QGSTask * downloadTask);
	void slotFinished(QGSTask * downloadTask);

private:
	QString mVersionId;
	QGSForgeVersionInfo mVersionInfo;
	QGSGameDirectory * mGameDirectoryPtr;
	QGSDownloadTaskFactory * mDownloadTaskFactoryPtr;
	QList<QGSTask *> mTaskList;
	QGSDownloadTask * mForgeDownloadTask;
	QFile mForgeInstallerFile;
	QDir mForgeDir;
	bool mFileOverride;
};
