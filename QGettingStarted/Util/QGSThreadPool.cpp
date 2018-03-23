#include <iostream>

#include "QGSThreadPool.h"

//msecs
static const unsigned long DEFAULT_SLEEP_TIME{ 1 };

QGSThreadPool::QGSThreadPool(const int minThreadCount, const int maxThreadCount, QObject *parent)
	: QThread(parent), 
	mTaskQueueBlock(false), 
	mReleaseThreads(false), 
	mMaxThreadCount(maxThreadCount),
	mMinThreadCount(minThreadCount),
	mActiveThreadCount(0),
	mSleepTime(DEFAULT_SLEEP_TIME)
{
	if (minThreadCount >= maxThreadCount)
	{
		mMinThreadCount = 1;
	}
	if (maxThreadCount < 1)
	{
		mMaxThreadCount = QGSThread::idealThreadCount();
	}
	mTaskQueue.clear();
}

QGSThreadPool::~QGSThreadPool()
{
	for (auto & thread : mThreadList)
	{
		thread->deleteLater();
	}
}

QGSThreadPool & QGSThreadPool::getGlobalInstance()
{
	static QGSThreadPool instance{ QGSThread::idealThreadCount(), QGSThread::idealThreadCount() };
	if (!instance.isRunning())
	{
		instance.start();
	}
	return instance;
}

bool QGSThreadPool::addTask(QGSTask * task)
{
	if (!task)
	{
		return false;
	}

	mMutex.lock();
	if (mReleaseThreads)
	{
		mMutex.unlock();
		return false;
	}
	task->moveToThread(this);
	mTaskQueue.push_back(task);
	mMutex.unlock();

	return true;
}

QGSThreadPool & QGSThreadPool::setMaxThreadCount(const quint32 maxThreadCount)
{
	mAttribMutex.lock();

	if (maxThreadCount >= 1)
	{
		mMaxThreadCount = maxThreadCount;
	}

	mAttribMutex.unlock();

	return *this;
}

QGSThreadPool & QGSThreadPool::setMinThreadCount(const quint32 minThreadCount)
{
	mAttribMutex.lock();

	if (minThreadCount < mMaxThreadCount)
	{
		mMinThreadCount = minThreadCount;
	}

	mAttribMutex.unlock();

	return *this;
}

QGSThreadPool & QGSThreadPool::setSleepTime(const quint32 msecs)
{
	mSleepTime = msecs;
	return *this;
}

quint32 QGSThreadPool::getMaxThreadCount()
{
	quint32 ret = 0;

	mAttribMutex.lock();
	ret = mMaxThreadCount;
	mAttribMutex.unlock();

	return ret;
}

quint32 QGSThreadPool::getMinThreadCount()
{
	quint32 ret = 0;

	mAttribMutex.lock();
	ret = mMinThreadCount;
	mAttribMutex.unlock();

	return ret;
}

quint32 QGSThreadPool::getActiveThreadCount()
{
	quint32 ret = 0;

	mAttribMutex.lock();
	ret = mActiveThreadCount;
	mAttribMutex.unlock();

	return ret;
}

int QGSThreadPool::getThreadListSize()
{
	int ret = 0;

	mAttribMutex.lock();
	ret = mThreadList.size();
	mAttribMutex.unlock();

	return ret;
}

void QGSThreadPool::run()
{
	init();

	while (true)
	{
		//QGSThread::msleep(mSleepTime);

		//任务分配
		mMutex.lock();
		if (mTaskQueue.size() && !mTaskQueueBlock)
		{
			for (auto & thread : mThreadList)
			{
				if (!thread->isRunning() || thread->isFinished())
				{
					auto * newTask{ mTaskQueue.front() };

					mTaskQueue.pop_front();
					newTask->moveToThread(thread);
					thread->setTask(newTask);
					thread->start();
					//qDebug() << "Thread:" << thread << " new task:" << newTask << " added!";
					break;
				}
			}
		}
		mMutex.unlock();

		//获取成员变量
		mMutex.lock();
		const bool taskQueueBlock{ mTaskQueueBlock };
		const bool releaseThreads{ mReleaseThreads };
		const int taskQueueSize{ mTaskQueue.size() };
		mMutex.unlock();
		mAttribMutex.lock();
		const quint32 minThreadCount{ mMinThreadCount };
		const quint32 maxThreadCount{ mMaxThreadCount };
		const quint32 activeThreadCount{ mActiveThreadCount };
		const int threadListSize{ mThreadList.size() };
		mAttribMutex.unlock();

		//增加线程
		if (taskQueueSize > minThreadCount&&threadListSize < maxThreadCount)
		{
			mMutex.lock();
			quint32 threadAddedCount{ qMin(static_cast<quint32>(QGSThread::idealThreadCount()),maxThreadCount - threadListSize) };

			for (int i = 0; i < threadAddedCount; i++)
			{
				auto * newThread{ new QGSThread{ this } };
				if (newThread)
				{
					mAttribMutex.lock();
					mAttribMutex.unlock();
					//qDebug() << "Thread:" << newThread << " added!";
					mThreadList.push_back(newThread);
				}
			}
			mMutex.unlock();

		}
		else if (activeThreadCount * 4 < threadListSize&&threadListSize > minThreadCount)
		{
			mMutex.lock();
			for (auto it = mThreadList.begin(); it != mThreadList.end(); it++)
			{
				if (!(*it)->isRunning() || (*it)->isFinished())
				{
					(*it)->exit(0);
					mThreadList.erase(it);
					//qDebug() << "Thread:" << (*it) << " released!";
					break;
				}
			}
			mMutex.unlock();

		}
	}
}

void QGSThreadPool::init()
{
	const auto gendThreadCount{ qMin(static_cast<quint32>(QGSThread::idealThreadCount()),mMaxThreadCount) };
	for (quint32 i = 0; i < gendThreadCount; i++)
	{
		auto * newThread{ new QGSThread{ this } };
		if (!newThread)
		{
			//exception
		}
		mThreadList.push_back(newThread);
	}
}

/*
void QGSThreadPool::releaseThreads()
{
	mMutex.lock();
	mReleaseThreads = true;
	mMutex.unlock();
}
*/

/*
void QGSThreadPool::run()
{
	const auto PregeneratedThreadCount{ qMin(static_cast<quint32>(QGSThread::idealThreadCount()),mMaxThreadCount) };
	for (quint32 i = 0; i < PregeneratedThreadCount; i++)
	{
		auto * newThread{ new QGSThread{this} };
		if (!newThread)
		{
			//exception
		}
		newThread->start();
		mCurrentThreadCount++;
	}

	while (!mReleaseThreads)
	{
		QGSThread::msleep(mSleepTime);

		//获取成员变量
		mMutex.lock();
		const bool taskQueueBlock{ mTaskQueueBlock };
		const bool releaseThreads{ mReleaseThreads };
		const int taskQueueSize{ mTaskQueue.size() };
		mMutex.unlock();
		mAttribMutex.lock();
		const quint32 minThreadCount{ mMinThreadCount };
		const quint32 maxThreadCount{ mMaxThreadCount };
		const quint32 activeThreadCount{ mActiveThreadCount };
		const quint32 currentThreadCount{ mCurrentThreadCount };
		mAttribMutex.unlock();

		//增加线程
		if (taskQueueSize > minThreadCount&&currentThreadCount < maxThreadCount)
		{
			mMutex.lock();
			quint32 threadAddedCount{ qMin(static_cast<quint32>(QGSThread::idealThreadCount()),maxThreadCount - currentThreadCount) };

			for (int i = 0; i < threadAddedCount; i++)
			{
				auto * newThread{ new QGSThread{ this } };
				if (newThread)
				{
					mAttribMutex.lock();
					mCurrentThreadCount++;
					mAttribMutex.unlock();

					newThread->start();

					//qDebug() << "Thread:" << newThread << " added!";
				}
			}
			mMutex.unlock();

		}
		else if (activeThreadCount * 4 < currentThreadCount&&currentThreadCount > minThreadCount)
		{
			mMutex.lock();
			quint32 threadReleasedCount{ qMin(static_cast<quint32>(QGSThread::idealThreadCount()),activeThreadCount) };

			mWaitReleasedThreadCount++;
			mTaskQueueStartCondition.wakeOne();
			mMutex.unlock();

		}
	}
}
*/