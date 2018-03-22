#include "QGSTask.h"

QGSTask::QGSTask() :mTaskQueueBlock(false)
{

}

QGSTask::~QGSTask()
{

}

bool QGSTask::isTaskQueueBlock() const
{
	return mTaskQueueBlock;
}

QGSTask & QGSTask::setTaskQueueBlock(const bool taskQueueBlock)
{
	mTaskQueueBlock = taskQueueBlock;
	return *this;
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
