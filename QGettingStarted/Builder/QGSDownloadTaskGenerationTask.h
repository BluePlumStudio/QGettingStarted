#pragma once

#include <QMutex>
#include <QMetaType>
#include <QWaitCondition>

#include "../Util/QGSTask.h"
#include "../Util/QGSNetworkHelper.h"

class QGSDownloadTaskGenerationTask : public QGSTask
{
	Q_OBJECT

public:
	QGSDownloadTaskGenerationTask(QObject * parent = nullptr);

	QGSDownloadTaskGenerationTask(const QGSDownloadTaskGenerationTask & right) = delete;

	QGSDownloadTaskGenerationTask(QGSDownloadTaskGenerationTask && right) = delete;

	QGSDownloadTaskGenerationTask & operator=(const QGSDownloadTaskGenerationTask & right) = delete;

	QGSDownloadTaskGenerationTask & operator=(QGSDownloadTaskGenerationTask && right) = delete;

	virtual ~QGSDownloadTaskGenerationTask();
};
