#pragma once

#include <QQueue>
#include <QTimer>

#include "QGSTaskThread.h"

class QGSThreadPool : public QThread
{
	Q_OBJECT
public:
	friend class QGSTaskThread;

	QGSThreadPool(const int minThreadCount, const int maxThreadCount, QObject *parent = nullptr);

	QGSThreadPool(const QGSThreadPool & right) = delete;

	QGSThreadPool(QGSThreadPool && right) = delete;

	QGSThreadPool & operator=(const QGSThreadPool & right) = delete;

	QGSThreadPool & operator=(QGSThreadPool && right) = delete;

	virtual ~QGSThreadPool();

	static QGSThreadPool & getGlobalInstance();

	bool addTaskBack(QGSTask * task);

	bool addTaskFront(QGSTask * task);

	QGSThreadPool & setMaxThreadCount(const quint32 maxThreadCount);

	QGSThreadPool & setMinThreadCount(const quint32 minThreadCount);

	QGSThreadPool & setExpiryTimeout(const quint32 msecs);

	quint32 getExpiryTimeout();

	quint32 getMaxThreadCount();

	quint32 getMinThreadCount();

	quint32 getActiveThreadCount();

	int getThreadListSize();

	//void releaseThreads();
private:
	virtual void run();
	void init();
	void adjust();
signals:
	void taskStarted(QGSTask * task);
	void taskFinished(QGSTask* task);
private:
	//QWaitCondition mTaskQueueStartCondition;
	//QWaitCondition mTaskQueueNotFullCondition;

	QQueue<QGSTask *> mTaskQueue;
	QList<QGSTaskThread *> mThreadList;
	QMutex mMutex;
	//bool mTaskQueueBlock;
	bool mReleaseThreads;
	//quint32 mWaitReleasedThreadCount;

	QMutex mAttribMutex;
	quint32 mMinThreadCount;
	quint32 mMaxThreadCount;
	//quint32 mActiveThreadCount;

	int mExpiryTimeout;
	QTimer mTimer;
};
