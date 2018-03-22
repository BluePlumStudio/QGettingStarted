#pragma once

#include <QWaitCondition>
#include <QMutex>
#include <QEventLoop>
#include <QDebug>

#include "QGSTask.h"

class QGSThreadPool;

class QGSThread : public QThread
{
	Q_OBJECT

public:
	friend class QGSThreadPool;

	QGSThread(QGSThreadPool * threadPool);

	QGSThread(const QGSThread & right) = delete;

	QGSThread(QGSThread && right) = delete;

	QGSThread & operator=(const QGSThread & right) = delete;

	QGSThread & operator=(QGSThread && right) = delete;

	virtual ~QGSThread();
private:
	virtual void run();
signals:
	void taskStart(QGSTask * task);
private:
	QGSThreadPool * mThreadPoolPtr;
};
