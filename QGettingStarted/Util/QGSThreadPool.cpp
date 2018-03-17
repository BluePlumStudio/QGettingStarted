#include <QDebug>

#include "QGSThreadPool.h"

QGSThreadPool::QGSThreadPool(QObject *parent)
	: QObject(parent), mMaxFreeThreadSize(QThread::idealThreadCount())
{
	addThreads(mMaxFreeThreadSize);
}

QGSThreadPool::~QGSThreadPool()
{
	clear();
}

int QGSThreadPool::getFreeThreadSize() const
{
	int ret = 0;

	for (auto & thread : mThreadVector)
	{
		if (!thread->isRunning())
		{
			ret++;
		}
	}

	return ret;
}

int QGSThreadPool::getRunningThreadSize() const
{
	int ret = 0;
	
	for (auto & thread : mThreadVector)
	{
		if (thread->isRunning())
		{
			ret++;
		}
	}

	return ret;
}

int QGSThreadPool::getMaxFreeThreadSize() const
{
	return mMaxFreeThreadSize;
}

QGSThreadPool & QGSThreadPool::setMaxFreeThreadSize(const int maxFreeThreadSize)
{
	QMutexLocker mutexLocker{ &mMutex };

	mMaxFreeThreadSize = maxFreeThreadSize;
	return *this;
}

bool QGSThreadPool::run(QGSDownloader * object)
{
	if (!object)
	{
		return false;
	}

	auto freeThread{ getFreeThread() };

	if (!freeThread)
	{
		return false;
	}

	QMutexLocker mutexLocker{ &mMutex };

	object->moveToThread(freeThread);
	freeThread->start();
	connect(object, &QGSDownloader::finished, [=] 
	{
		qDebug() << freeThread;
		freeThread->exit();
	});

	return true;
}

void QGSThreadPool::clear()
{
	for (auto & thread : mThreadVector)
	{
		thread->terminate();
	}
}

QThread * QGSThreadPool::getFreeThread()
{
	for (auto & thread : mThreadVector)
	{
		if (!thread->isRunning())
		{
			return thread;
		}
	}

	return addThread();
}

void QGSThreadPool::addThreads(int size)
{
	QMutexLocker mutexLocker{ &mMutex };

	while (size--)
	{
		auto * newThread{ new QThread };

		mThreadVector.push_back(newThread);
	}
}

QThread * QGSThreadPool::addThread()
{
	QMutexLocker mutexLocker{ &mMutex };

	auto * newThread{ new QThread };

	mThreadVector.push_back(newThread);

	return newThread;
}
