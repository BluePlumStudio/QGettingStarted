#include "QGSThread.h"
#include "QGSThreadPool.h"

QGSThread::QGSThread(QGSThreadPool * threadPool) :mThreadPoolPtr(threadPool), mActive(false), mTask(nullptr), mExit(false)
{
	if (!threadPool)
	{

	}
}

QGSThread::~QGSThread()
{

}

QGSThread & QGSThread::setTask(QGSTask * task)
{
	mTask = task;
	return *this;
}

bool QGSThread::isActive()
{
	return mActive;
}

void QGSThread::exit(int returnCode)
{
	mExit = true;
	QThread::exit(returnCode);
}

void QGSThread::run()
{
	if (!mThreadPoolPtr)
	{
		//exception
	}

	QEventLoop eventLoop;

	do
	{
		QMutexLocker mutexLocker{ &mThreadPoolPtr->mMutex };

		if (mTask)
		{
			mActive = true;
		}
		else
		{
			mActive = false;
			if (mExit)
			{
				//qDebug() << "Exit!";
				break;
			}
			continue;
		}

		/*
		signals:
		void started(QGSTask * task);
		void finished(QGSTask * task);
		void stoped(QGSTask * task);
		void canceled(QGSTask * task);
		void error(QGSTask * task);
		*/
		//计数
		mThreadPoolPtr->mAttribMutex.lock();
		mThreadPoolPtr->mActiveThreadCount++;
		mThreadPoolPtr->mAttribMutex.unlock();
		//任务开始
		QObject::connect(this, &QGSThread::taskStart, mTask, &QGSTask::start, Qt::DirectConnection);
		QObject::connect(mTask, &QGSTask::finished, &eventLoop, &QEventLoop::quit, Qt::ConnectionType::QueuedConnection);
		QObject::connect(mTask, &QGSTask::stoped, &eventLoop, &QEventLoop::quit, Qt::ConnectionType::QueuedConnection);
		QObject::connect(mTask, &QGSTask::canceled, &eventLoop, &QEventLoop::quit, Qt::ConnectionType::QueuedConnection);
		QObject::connect(mTask, &QGSTask::error, &eventLoop, &QEventLoop::quit, Qt::ConnectionType::QueuedConnection);
		emit taskStart(mTask);
		eventLoop.exec();
		QObject::disconnect(mTask, &QGSTask::finished, &eventLoop, &QEventLoop::quit);
		QObject::disconnect(mTask, &QGSTask::stoped, &eventLoop, &QEventLoop::quit);
		QObject::disconnect(mTask, &QGSTask::canceled, &eventLoop, &QEventLoop::quit);
		QObject::disconnect(mTask, &QGSTask::error, &eventLoop, &QEventLoop::quit);
		QObject::disconnect(this, &QGSThread::taskStart, mTask, &QGSTask::start);

		//qDebug() << "Current task finished:" << task;

		//计数
		mThreadPoolPtr->mAttribMutex.lock();
		mThreadPoolPtr->mActiveThreadCount--;
		mThreadPoolPtr->mAttribMutex.unlock();

		mActive = false;
		mTask = nullptr;
	} while (1);
}




/*
void QGSThread::run()
{
	if (!mThreadPoolPtr)
	{
		//exception
	}

	QEventLoop eventLoop;

	while (true)
	{
		mThreadPoolPtr->mMutex.lock();
		//检查队列是否有任务
		if (!mThreadPoolPtr->mTaskQueue.size() && !mThreadPoolPtr->mReleaseThreads)
		{
			mThreadPoolPtr->mTaskQueueStartCondition.wait(&mThreadPoolPtr->mMutex);
		}
		//线程池退出或线程释放
		if (mThreadPoolPtr->mReleaseThreads || mThreadPoolPtr->mWaitReleasedThreadCount)
		{
			mThreadPoolPtr->mCurrentThreadCount--;
			mThreadPoolPtr->mWaitReleasedThreadCount--;
			mThreadPoolPtr->mMutex.unlock();
			exit(0);
			//qDebug() << "Thread:" << this << "released!";
			break;
		}
		//检查是否遇到阻塞队列的任务
		if (mThreadPoolPtr->mTaskQueueBlock)
		{
			mThreadPoolPtr->mMutex.unlock();
			continue;
		}
		//获取任务
		auto * task{ mThreadPoolPtr->mTaskQueue.front() };
		//qDebug() << "Current task queue size:" << mThreadPoolPtr->mTaskQueue.size();
		mThreadPoolPtr->mTaskQueue.pop_front();
		mThreadPoolPtr->mTaskQueueBlock = task->isTaskQueueBlock();
		task->moveToThread(this->thread());
		//条件：队列未满
		QObject::connect(task, &QGSTask::finished, &eventLoop, &QEventLoop::quit);
		QObject::connect(task, &QGSTask::canceled, &eventLoop, &QEventLoop::quit);
		QObject::connect(task, &QGSTask::error, &eventLoop, &QEventLoop::quit);
		QObject::connect(this, &QGSThread::taskStart, task, &QGSTask::start);
		mThreadPoolPtr->mMutex.unlock();
		//计数
		mThreadPoolPtr->mAttribMutex.lock();
		mThreadPoolPtr->mActiveThreadCount++;
		mThreadPoolPtr->mAttribMutex.unlock();
		//任务开始
		emit taskStart(task);
		eventLoop.exec();
		QObject::disconnect(this, &QGSThread::taskStart, task, &QGSTask::start);
		//如果当前任务为阻塞队列的任务
		if (task->isTaskQueueBlock())
		{
			mThreadPoolPtr->mMutex.lock();
			//任务完成，解除阻塞
			mThreadPoolPtr->mTaskQueueBlock = false;
			mThreadPoolPtr->mMutex.unlock();
		}
		//qDebug() << "Current task finished:" << task;
		//计数
		mThreadPoolPtr->mAttribMutex.lock();
		mThreadPoolPtr->mActiveThreadCount--;
		mThreadPoolPtr->mAttribMutex.unlock();
	}
}
*/