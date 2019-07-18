#include <QTimer>

#include "QGSTask.h"
#include "QGSThreadPool.h"
#include "../Util/QGSExceptionInvalidValue.h"

static const unsigned long DEFAULT_WAIT_TIME(1000);

QGSTask::QGSTask(QObject * parent) :QObject(parent), mNextTask(nullptr), mThreadPool(nullptr)
{
	mOriginalThread = thread();
}

QGSTask::~QGSTask()
{

}

void QGSTask::moveToOriginalThread()
{
	moveToThread(mOriginalThread);
}

void QGSTask::deleteLater()
{
	/*
	QTimer * newTimer(new QTimer);
	newTimer->setSingleShot(true);
	newTimer->start(DEFAULT_WAIT_TIME);
	QObject::connect(newTimer, &QTimer::timeout, this, &QGSTask::deleteLater);
	QObject::connect(newTimer, &QTimer::timeout, newTimer, &QTimer::deleteLater);
	*/
	QObject::deleteLater();
}

QGSTask & QGSTask::setNextTask(QGSTask * task)
{
	if (!task)
	{
		throw QGSExceptionInvalidValue();
	}

	mNextTask = task;
	//QObject::connect(this, &QGSTask::finished, mNextTask, &QGSTask::start, Qt::ConnectionType::UniqueConnection);
	QObject::connect(this, &QGSTask::finished, this, &QGSTask::startNextTask);

	return *task;
}

QGSTask & QGSTask::setThreadPool(QGSThreadPool * threadPool)
{
	if (!threadPool)
	{
		throw QGSExceptionInvalidValue();
	}

	mThreadPool = threadPool;

	return *this;
}

QGSTask * QGSTask::getNextTask()
{
	return mNextTask;
}

QGSThreadPool * QGSTask::getThreadPool()
{
	return mThreadPool;
}

void QGSTask::start()
{
	QMetaObject::invokeMethod(this, "templateStart", Qt::ConnectionType::QueuedConnection, Q_ARG(QGSTask *, this));
}

void QGSTask::stop()
{
	QMetaObject::invokeMethod(this, "templateStop", Qt::ConnectionType::QueuedConnection, Q_ARG(QGSTask *, this));
}

void QGSTask::cancel()
{
	QMetaObject::invokeMethod(this, "templateCancel", Qt::ConnectionType::QueuedConnection, Q_ARG(QGSTask *, this));
}

void QGSTask::templateStart(QGSTask * task)
{

}

void QGSTask::templateStop(QGSTask * task)
{

}

void QGSTask::templateCancel(QGSTask * task)
{

}

void QGSTask::startNextTask()
{
	mThreadPool->addTaskBack(mNextTask);
}