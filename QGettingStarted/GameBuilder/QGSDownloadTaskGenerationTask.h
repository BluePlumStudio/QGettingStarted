#pragma once

#include <QMutex>

#include "../Util/QGSTask.h"
#include "../Util/QGSNetworkAccessManager.h"

class QGSDownloadTaskGenerationTask : public QGSTask
{
	Q_OBJECT

public:
	QGSDownloadTaskGenerationTask();

	QGSDownloadTaskGenerationTask(const QGSDownloadTaskGenerationTask & right) = delete;

	QGSDownloadTaskGenerationTask(QGSDownloadTaskGenerationTask && right) = delete;

	QGSDownloadTaskGenerationTask & operator=(const QGSDownloadTaskGenerationTask & right) = delete;

	QGSDownloadTaskGenerationTask & operator=(QGSDownloadTaskGenerationTask && right) = delete;

	virtual ~QGSDownloadTaskGenerationTask();
signals:
	void generationTaskStarted(QGSTask * task);
	void generationTaskFinished(QGSTask * task);
	void generationTaskStoped(QGSTask * task);
	void generationTaskCanceled(QGSTask * task);
	void generationTaskDownloadError(QGSNetworkError error, QGSTask * task);
protected:
};
