#pragma once

#include <QQueue>
#include <QTimer>

#include "QGSTaskThread.h"

class QGSThreadPool : public QThread
{
	Q_OBJECT
public:
	friend class QGSTaskThread;
	friend class QGSThreadPoolManager;

	QGSThreadPool(const int minThreadCount, const int maxThreadCount, QObject *parent = nullptr);

	QGSThreadPool(const QGSThreadPool & right) = delete;

	QGSThreadPool(QGSThreadPool && right) = delete;

	QGSThreadPool & operator=(const QGSThreadPool & right) = delete;

	QGSThreadPool & operator=(QGSThreadPool && right) = delete;

	virtual ~QGSThreadPool();
signals:
	void taskStarted(QGSTask * task);
	void taskFinished(QGSTask* task);
private:
	bool addTaskBack(QGSTask * task);

	bool addTaskFront(QGSTask * task);

	QGSThreadPool & setMaxThreadCount(const quint32 maxThreadCount);

	QGSThreadPool & setMinThreadCount(const quint32 minThreadCount);

	quint32 getMaxThreadCount();

	quint32 getMinThreadCount();

	quint32 getActiveThreadCount();

	int getThreadListSize();

	virtual void run();

	void init();

	void adjustThreads();
private:
	QWaitCondition mTaskQueueNotEmpty;
	QWaitCondition mTaskThreadActive;

	QQueue<QGSTask *> mTaskQueue;
	QList<QGSTaskThread *> mThreadList;
	QMutex mMutex;
	QMutex mConditionMutex;
	bool mReleaseThreads;

	quint32 mMinThreadCount;
	quint32 mMaxThreadCount;

};
