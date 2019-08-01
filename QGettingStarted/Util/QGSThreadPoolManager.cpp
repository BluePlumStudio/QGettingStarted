#include "QGSThreadPoolManager.h"

//msecs
static const unsigned long DEFAULT_SLEEP_TIME(5000);

QGSThreadPoolManager::QGSThreadPoolManager(const int minThreadCount, const int maxThreadCount, QObject *parent)
	: QObject(parent), mThreadPoolPtr(new QGSThreadPool(minThreadCount, maxThreadCount)), mExpiryTimeout(DEFAULT_SLEEP_TIME)
{
	mThreadPoolPtr->start();

	mTimer.singleShot(mExpiryTimeout, this, &QGSThreadPoolManager::adjustThreads);
}

QGSThreadPoolManager::~QGSThreadPoolManager()
{
	if (mThreadPoolPtr)
	{
		mThreadPoolPtr->quit();
		mThreadPoolPtr->wait();
		mThreadPoolPtr->deleteLater();
	}

	mThreadPoolPtr = nullptr;
}

QGSThreadPool * QGSThreadPoolManager::getThreadPoolInstance()
{
	return mThreadPoolPtr;
}

bool QGSThreadPoolManager::addTaskBack(QGSTask * task)
{
	return mThreadPoolPtr->addTaskBack(task);
}

bool QGSThreadPoolManager::addTaskFront(QGSTask * task)
{
	return mThreadPoolPtr->addTaskFront(task);
}

QGSThreadPoolManager & QGSThreadPoolManager::setMaxThreadCount(const quint32 maxThreadCount)
{
	mThreadPoolPtr->setMaxThreadCount(maxThreadCount);
	return *this;
}

QGSThreadPoolManager & QGSThreadPoolManager::setMinThreadCount(const quint32 minThreadCount)
{
	mThreadPoolPtr->setMinThreadCount(minThreadCount);
	return *this;
}

QGSThreadPoolManager & QGSThreadPoolManager::setExpiryTimeout(const quint32 msecs)
{
	mExpiryTimeout = msecs;
	return *this;
}

quint32 QGSThreadPoolManager::getExpiryTimeout()
{
	return mExpiryTimeout;
}

quint32 QGSThreadPoolManager::getMaxThreadCount()
{
	return mThreadPoolPtr->getMaxThreadCount();
}

quint32 QGSThreadPoolManager::getMinThreadCount()
{
	return mThreadPoolPtr->getMinThreadCount();
}

quint32 QGSThreadPoolManager::getActiveThreadCount()
{
	return mThreadPoolPtr->getActiveThreadCount();
}

int QGSThreadPoolManager::getThreadListSize()
{
	return mThreadPoolPtr->getThreadListSize();
}

void QGSThreadPoolManager::adjustThreads()
{
	mThreadPoolPtr->adjustThreads();

	mTimer.singleShot(mExpiryTimeout, this, &QGSThreadPoolManager::adjustThreads);
}
