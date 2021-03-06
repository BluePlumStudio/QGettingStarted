#pragma once

#include <QWaitCondition>
#include <QMutex>
#include <QEventLoop>
#include <QDebug>

#include "QGSTask.h"

class QGSThreadPool;

class QGSTaskThread : public QThread
{
	Q_OBJECT

public:
	friend class QGSThreadPool;

	QGSTaskThread(QGSThreadPool * threadPool);

	QGSTaskThread(const QGSTaskThread & right) = delete;

	QGSTaskThread(QGSTaskThread && right) = delete;

	QGSTaskThread & operator=(const QGSTaskThread & right) = delete;

	QGSTaskThread & operator=(QGSTaskThread && right) = delete;

	virtual ~QGSTaskThread();

	//QGSTaskThread & setTask(QGSTask * task);

	void exit(int returnCode = 0);

	void quit();
signals:
	void taskStarted(QGSTask * task);
	void taskFinished(QGSTask* task);
private:
	virtual void run();
private:
	QGSThreadPool * mThreadPoolPtr;
	QGSTask * mTask;
	QMutex mConditionMutex;

	bool mActive;
	bool mExit;
};
