#pragma once

#include "QGSAssetIndexJsonDownloadTaskGenerationTask.h"

class QGSAssetObjectDownloadTaskGenerationTask :public QGSDownloadTaskGenerationTask
{
public:
	QGSAssetObjectDownloadTaskGenerationTask(
		QGSAssetBuilder * assetBuilder, 
		QSharedPointer<QMutex> sharedMutex,
		QSharedPointer<QWaitCondition> jsonDownloadTaskEnded, 
		bool fileOverride = false, 
		QObject * parent = nullptr);

	QGSAssetObjectDownloadTaskGenerationTask(const QGSAssetObjectDownloadTaskGenerationTask & right) = delete;

	QGSAssetObjectDownloadTaskGenerationTask(QGSAssetObjectDownloadTaskGenerationTask && right) = delete;

	QGSAssetObjectDownloadTaskGenerationTask & operator=(const QGSAssetObjectDownloadTaskGenerationTask & right) = delete;

	QGSAssetObjectDownloadTaskGenerationTask & operator=(QGSAssetObjectDownloadTaskGenerationTask && right) = delete;

	virtual ~QGSAssetObjectDownloadTaskGenerationTask();

protected slots:
	virtual void templateStart(QGSTask * task);
	virtual void templateStop(QGSTask * task);
	virtual void templateCancel(QGSTask * task);
private:
	QGSAssetBuilder * mAssetBuilderPtr;
	QSharedPointer<QMutex> mSharedMutex;
	QSharedPointer<QWaitCondition> mAssetIndexJsonDownloadTaskEnded;
	bool mFileOverride;

};
