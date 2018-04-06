#pragma once

#include "QGSAssetIndexJsonDownloadTaskGenerationTask.h"

class QGSAssetObjectDownloadTaskGenerationTask :public QGSDownloadTaskGenerationTask
{
public:
	QGSAssetObjectDownloadTaskGenerationTask(QGSAssetBuilder * assetBuilder, bool fileOverride = false, QObject * parent = nullptr);

	QGSAssetObjectDownloadTaskGenerationTask(const QGSAssetObjectDownloadTaskGenerationTask & right) = delete;

	QGSAssetObjectDownloadTaskGenerationTask(QGSAssetObjectDownloadTaskGenerationTask && right) = delete;

	QGSAssetObjectDownloadTaskGenerationTask & operator=(const QGSAssetObjectDownloadTaskGenerationTask & right) = delete;

	QGSAssetObjectDownloadTaskGenerationTask & operator=(QGSAssetObjectDownloadTaskGenerationTask && right) = delete;

	virtual ~QGSAssetObjectDownloadTaskGenerationTask();

protected:
	virtual void templateStart(QGSTask * task);
	virtual void templateStop(QGSTask * task);
	virtual void templateCancel(QGSTask * task);
private:
	QGSAssetBuilder * mAssetBuilderPtr;
	bool mFileOverride;
};
