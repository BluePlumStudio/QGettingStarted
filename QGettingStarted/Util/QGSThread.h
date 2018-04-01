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

	//QGSThread & setTask(QGSTask * task);

	void exit(int returnCode = 0);
private:
	virtual void run();
signals:
	void taskStarted(QGSTask * task);
	void taskFinished(QGSTask * task); 
private:
	QGSThreadPool * mThreadPoolPtr;
	QGSTask * mTask;
	//QMutex mMutex;
	bool mActive;
	bool mExit;
};