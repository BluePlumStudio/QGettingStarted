#pragma once

#include "QGSThreadPool.h"

class QGSThreadPoolManager : public QObject
{
	Q_OBJECT

public:
	QGSThreadPoolManager(const int minThreadCount, const int maxThreadCount, QObject *parent = nullptr);

	virtual ~QGSThreadPoolManager();

	QGSThreadPool * getThreadPoolInstance();

	bool addTaskBack(QGSTask * task);

	bool addTaskFront(QGSTask * task);

	QGSThreadPoolManager & setMaxThreadCount(const quint32 maxThreadCount);

	QGSThreadPoolManager & setMinThreadCount(const quint32 minThreadCount);

	QGSThreadPoolManager & setExpiryTimeout(const quint32 msecs);

	quint32 getExpiryTimeout();

	quint32 getMaxThreadCount();

	quint32 getMinThreadCount();

	quint32 getActiveThreadCount();

	int getThreadListSize();
private:
	void adjustThreads();
private:
	QGSThreadPool * mThreadPoolPtr;
	QTimer mTimer;
	int mExpiryTimeout;

};
