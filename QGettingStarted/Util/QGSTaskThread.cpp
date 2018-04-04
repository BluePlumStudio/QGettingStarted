#include "QGSTaskThread.h"
#include "QGSThreadPool.h"

QGSTaskThread::QGSTaskThread(QGSThreadPool * threadPool) :mThreadPoolPtr(threadPool), mActive(false), mTask(nullptr), mExit(false)
{
	if (!threadPool)
	{

	}
}

QGSTaskThread::~QGSTaskThread()
{

}

/*
QGSTaskThread & QGSTaskThread::setTask(QGSTask * task)
{
	mTask = task;
	return *this;
}
*/

void QGSTaskThread::exit(int returnCode)
{
	mExit = true;
	QThread::exit(returnCode);
}

void QGSTaskThread::run()
{
	if (!mThreadPoolPtr)
	{
		//exception
	}

	QEventLoop eventLoop;

	do
	{
		mThreadPoolPtr->mMutex.lock();

		//qDebug() << "Thread:" << this;

		if (mExit)
		{
			mThreadPoolPtr->mMutex.unlock();
			break;
		}

		if (!mTask)
		{
			mActive = false;

			mThreadPoolPtr->mMutex.unlock();

			continue;
		}
		mActive = true;
		auto * newTask(mTask);
		mThreadPoolPtr->mMutex.unlock();

		//����ʼ
		QObject::connect(newTask, &QGSTask::finished, &eventLoop, &QEventLoop::quit, Qt::ConnectionType::QueuedConnection);
		QObject::connect(newTask, &QGSTask::canceled, &eventLoop, &QEventLoop::quit, Qt::ConnectionType::QueuedConnection);
		QObject::connect(newTask, &QGSTask::error, &eventLoop, &QEventLoop::quit, Qt::ConnectionType::QueuedConnection);
		//emit taskStarted(mTask);
		QMetaObject::invokeMethod(newTask, "start", Qt::ConnectionType::DirectConnection);
		eventLoop.exec();
		//mTask->moveToOriginalThread();
		emit taskFinished(newTask);
		QObject::disconnect(newTask, &QGSTask::finished, &eventLoop, &QEventLoop::quit);
		QObject::disconnect(newTask, &QGSTask::canceled, &eventLoop, &QEventLoop::quit);
		QObject::disconnect(newTask, &QGSTask::error, &eventLoop, &QEventLoop::quit);

		mThreadPoolPtr->mMutex.lock();

		mActive = false;
		mTask = nullptr;

		mThreadPoolPtr->mMutex.unlock();
	} while (true);

	exit(0);
}

/*
void QGSTaskThread::run()
{
	if (!mThreadPoolPtr)
	{
		//exception
	}

	QEventLoop eventLoop;

	while (true)
	{
		mThreadPoolPtr->mMutex.lock();
		//�������Ƿ�������
		if (!mThreadPoolPtr->mTaskQueue.size() && !mThreadPoolPtr->mReleaseThreads)
		{
			mThreadPoolPtr->mTaskQueueStartCondition.wait(&mThreadPoolPtr->mMutex);
		}
		//�̳߳��˳����߳��ͷ�
		if (mThreadPoolPtr->mReleaseThreads || mThreadPoolPtr->mWaitReleasedThreadCount)
		{
			mThreadPoolPtr->mCurrentThreadCount--;
			mThreadPoolPtr->mWaitReleasedThreadCount--;
			mThreadPoolPtr->mMutex.unlock();
			exit(0);
			//qDebug() << "Thread:" << this << "released!";
			break;
		}
		//����Ƿ������������е�����
		if (mThreadPoolPtr->mTaskQueueBlock)
		{
			mThreadPoolPtr->mMutex.unlock();
			continue;
		}
		//��ȡ����
		auto * task(mThreadPoolPtr->mTaskQueue.front());
		//qDebug() << "Current task queue size:" << mThreadPoolPtr->mTaskQueue.size();
		mThreadPoolPtr->mTaskQueue.pop_front();
		mThreadPoolPtr->mTaskQueueBlock = task->isTaskQueueBlock();
		task->moveToThread(this->thread());
		//����������δ��
		QObject::connect(task, &QGSTask::finished, &eventLoop, &QEventLoop::quit);
		QObject::connect(task, &QGSTask::canceled, &eventLoop, &QEventLoop::quit);
		QObject::connect(task, &QGSTask::error, &eventLoop, &QEventLoop::quit);
		QObject::connect(this, &QGSTaskThread::taskStart, task, &QGSTask::start);
		mThreadPoolPtr->mMutex.unlock();
		//����
		mThreadPoolPtr->mAttribMutex.lock();
		mThreadPoolPtr->mActiveThreadCount++;
		mThreadPoolPtr->mAttribMutex.unlock();
		//����ʼ
		emit taskStart(task);
		eventLoop.exec();
		QObject::disconnect(this, &QGSTaskThread::taskStart, task, &QGSTask::start);
		//�����ǰ����Ϊ�������е�����
		if (task->isTaskQueueBlock())
		{
			mThreadPoolPtr->mMutex.lock();
			//������ɣ��������
			mThreadPoolPtr->mTaskQueueBlock = false;
			mThreadPoolPtr->mMutex.unlock();
		}
		//qDebug() << "Current task finished:" << task;
		//����
		mThreadPoolPtr->mAttribMutex.lock();
		mThreadPoolPtr->mActiveThreadCount--;
		mThreadPoolPtr->mAttribMutex.unlock();
	}
}
*/