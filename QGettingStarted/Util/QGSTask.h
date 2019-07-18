#pragma once

#include <QObject>
#include <QThread>

//#include "QGSThreadPool.h"

class QGSThreadPool;

class QGSTask : public QObject
{
	Q_OBJECT

public:
	QGSTask(QObject * parent = nullptr);

	QGSTask(const QGSTask & right) = delete;

	QGSTask(QGSTask && right) = delete;

	QGSTask & operator=(const QGSTask & right) = delete;

	QGSTask & operator=(QGSTask && right) = delete;

	virtual ~QGSTask();

	void moveToOriginalThread();

	void deleteLater();

	QGSTask & setNextTask(QGSTask * task);
	QGSTask & setThreadPool(QGSThreadPool * threadPool);

	QGSTask * getNextTask();
	QGSThreadPool * getThreadPool();
signals:
	void started(QGSTask * task);
	void finished(QGSTask * task);
	void stoped(QGSTask * task);
	void canceled(QGSTask * task);
	void error(QGSTask * task);
public slots:
	void start();
	void stop();
	void cancel();
protected slots:
	virtual void templateStart(QGSTask * task);
	virtual void templateStop(QGSTask * task);
	virtual void templateCancel(QGSTask * task);
private slots:
	void startNextTask();
protected:
	QThread * mOriginalThread;
	QGSTask * mNextTask;
	QGSThreadPool * mThreadPool;
};
