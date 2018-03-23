#pragma once

#include <QObject>
#include <QThread>

class QGSTask : public QObject
{
	Q_OBJECT

public:
	QGSTask();

	QGSTask(const QGSTask & right) = delete;

	QGSTask(QGSTask && right) = delete;

	QGSTask & operator=(const QGSTask & right) = delete;

	QGSTask & operator=(QGSTask && right) = delete;

	virtual ~QGSTask();

	bool isTaskQueueBlock()const;

	QGSTask & setTaskQueueBlock(const bool taskQueueBlock);
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
protected:
	virtual void templateStart(QGSTask * task);
	virtual void templateStop(QGSTask * task);
	virtual void templateCancel(QGSTask * task);

protected:
	bool mTaskQueueBlock;
};
