#include "QGSTask.h"

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
