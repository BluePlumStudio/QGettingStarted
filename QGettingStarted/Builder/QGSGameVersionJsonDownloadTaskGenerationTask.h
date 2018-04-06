#pragma once

#include "QGSGameVersionBuilder.h"

class QGSGameVersionJsonDownloadTaskGenerationTask :public QGSDownloadTaskGenerationTask
{
public:
	friend QGSGameVersionDownloadTaskGenerationTask;

	QGSGameVersionJsonDownloadTaskGenerationTask(QGSGameVersionBuilder * gameVersionBuilder, QObject * parent = nullptr);

	QGSGameVersionJsonDownloadTaskGenerationTask(const QGSGameVersionJsonDownloadTaskGenerationTask & right) = delete;

	QGSGameVersionJsonDownloadTaskGenerationTask(QGSGameVersionJsonDownloadTaskGenerationTask && right) = delete;

	QGSGameVersionJsonDownloadTaskGenerationTask & operator=(const QGSGameVersionJsonDownloadTaskGenerationTask & right) = delete;

	QGSGameVersionJsonDownloadTaskGenerationTask & operator=(QGSGameVersionJsonDownloadTaskGenerationTask && right) = delete;

	virtual ~QGSGameVersionJsonDownloadTaskGenerationTask();

protected:
	virtual void templateStart(QGSTask * task);
	virtual void templateStop(QGSTask * task);
	virtual void templateCancel(QGSTask * task);
private :
	void wakeGameVersionJsonDownloadTaskEnded();
private:
	QGSGameVersionBuilder * mGameVersionBuilderPtr;
	static QMutex mMutex;
	static QWaitCondition mGameVersionJsonDownloadTaskEnded;
};
