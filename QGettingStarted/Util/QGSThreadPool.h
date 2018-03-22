#pragma once

#include <QQueue>

#include "QGSThread.h"

class QGSThreadPool : public QThread
{
	Q_OBJECT
public:
	friend class QGSThread;

	QGSThreadPool(const int minThreadCount, const int maxThreadCount, QObject *parent = nullptr);

	QGSThreadPool(const QGSThreadPool & right) = delete;

	QGSThreadPool(QGSThreadPool && right) = delete;

	QGSThreadPool & operator=(const QGSThreadPool & right) = delete;

	QGSThreadPool & operator=(QGSThreadPool && right) = delete;

	virtual ~QGSThreadPool();

	static QGSThreadPool & getGlobalInstance();

	bool addTask(QGSTask * task);

	QGSThreadPool & setMaxThreadCount(const quint32 maxThreadCount);

	QGSThreadPool & setMinThreadCount(const quint32 minThreadCount);

	QGSThreadPool & setSleepTime(const quint32 msecs);

	quint32 getMaxThreadCount();

	quint32 getMinThreadCount();

	quint32 getActiveThreadCount();

	quint32 getCurrentThreadCount();

	void releaseThreads();
private:
	bool addThread();
	virtual void run();
signals:
	void threadPoolFull();
private:
	QWaitCondition mTaskQueueNotEmptyCondition;
	//QWaitCondition mTaskQueueNotFullCondition;

	QQueue<QGSTask *> mTaskQueue;
	QMutex mMutex;
	bool mTaskQueueBlock;
	bool mReleaseThreads;
	quint32 mWaitReleasedThreadCount;

	QMutex mAttribMutex;
	quint32 mMinThreadCount;
	quint32 mMaxThreadCount;
	quint32 mActiveThreadCount;
	quint32 mCurrentThreadCount;

	int mSleepTime;
};
