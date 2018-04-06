#include <QTimer>

#include "QGSTask.h"

static const unsigned long DEFAULT_WAIT_TIME(5000);

QGSTask::QGSTask(QObject * parent) :QObject(parent)
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
	QTimer * newTimer(new QTimer);
	newTimer->setSingleShot(true);
	newTimer->start(DEFAULT_WAIT_TIME);
	QObject::connect(newTimer, &QTimer::timeout, this, &QGSTask::deleteLater);
	QObject::connect(newTimer, &QTimer::timeout, newTimer, &QTimer::deleteLater);
}

void QGSTask::start()
{
	templateStart(this);
}

void QGSTask::stop()
{
	templateStop(this);
}

void QGSTask::cancel()
{
	templateCancel(this);
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
