#pragma once

#include "QGSAssetBuilder.h"

class QGSAssetIndexJsonDownloadTaskGenerationTask :public QGSDownloadTaskGenerationTask
{
public:
	friend class QGSAssetObjectDownloadTaskGenerationTask;
	friend class QGSAssetBuilder;

	QGSAssetIndexJsonDownloadTaskGenerationTask(QGSAssetBuilder * assetBuilder, bool fileOverride = false, QObject * parent = nullptr);

	QGSAssetIndexJsonDownloadTaskGenerationTask(const QGSAssetIndexJsonDownloadTaskGenerationTask & right) = delete;

	QGSAssetIndexJsonDownloadTaskGenerationTask(QGSAssetIndexJsonDownloadTaskGenerationTask && right) = delete;

	QGSAssetIndexJsonDownloadTaskGenerationTask & operator=(const QGSAssetIndexJsonDownloadTaskGenerationTask & right) = delete;

	QGSAssetIndexJsonDownloadTaskGenerationTask & operator=(QGSAssetIndexJsonDownloadTaskGenerationTask && right) = delete;

	virtual ~QGSAssetIndexJsonDownloadTaskGenerationTask();

protected slots:
	virtual void templateStart(QGSTask * task);
	virtual void templateStop(QGSTask * task);
	virtual void templateCancel(QGSTask * task);
private:
	void wakeAssetIndexJsonDownloadTaskEnded();
private:
	QGSAssetBuilder * mAssetBuilderPtr;
	QSharedPointer<QMutex> mSharedMutex;
	QSharedPointer<QWaitCondition> mAssetIndexJsonDownloadTaskEnded;
	bool mFileOverride;
};
