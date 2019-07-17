#pragma once

#include "QGSGameVersionBuilder.h"

class QGSGameVersionDownloadTaskGenerationTask :public QGSDownloadTaskGenerationTask
{
public:
	QGSGameVersionDownloadTaskGenerationTask(
		QGSGameVersionBuilder * gameVersionBuilder, 
		QSharedPointer<QMutex> sharedMutex, 
		QSharedPointer<QWaitCondition> jsonDownloadTaskEnded,
		bool fileOverride = false, 
		QObject * parent = nullptr);

	QGSGameVersionDownloadTaskGenerationTask(const QGSGameVersionDownloadTaskGenerationTask & right) = delete;

	QGSGameVersionDownloadTaskGenerationTask(QGSGameVersionDownloadTaskGenerationTask && right) = delete;

	QGSGameVersionDownloadTaskGenerationTask & operator=(const QGSGameVersionDownloadTaskGenerationTask & right) = delete;

	QGSGameVersionDownloadTaskGenerationTask & operator=(QGSGameVersionDownloadTaskGenerationTask && right) = delete;

	virtual ~QGSGameVersionDownloadTaskGenerationTask();

protected slots:
	virtual void templateStart(QGSTask * task);
	virtual void templateStop(QGSTask * task);
	virtual void templateCancel(QGSTask * task);
private:
	QGSGameVersionBuilder * mGameVersionBuilderPtr;
	QSharedPointer<QMutex> mSharedMutex;
	QSharedPointer<QWaitCondition> mGameVersionJsonDownloadTaskEnded;
	bool mFileOverride;
};
