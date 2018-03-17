#pragma once

#include <QObject>
#include <QVector>
#include <QThread>
#include <QMutexLocker>
#include <QMutex>

#include "../Download/QGSDownloader.h"

/*A fake thread pool*/
class QGSThreadPool : public QObject
{
	Q_OBJECT

public:
	QGSThreadPool(QObject *parent = nullptr);

	QGSThreadPool(const QGSThreadPool & right) = delete;

	QGSThreadPool(QGSThreadPool && right) = delete;

	QGSThreadPool & operator=(const QGSThreadPool & right) = delete;

	QGSThreadPool & operator=(QGSThreadPool && right) = delete;

	virtual ~QGSThreadPool();

	int getFreeThreadSize()const;

	int getRunningThreadSize()const;

	int getMaxFreeThreadSize()const;

	QGSThreadPool & setMaxFreeThreadSize(const int maxFreeThreadSize);

	bool run(QGSDownloader * object);

	void clear();
private:
	QThread * getFreeThread();

	void addThreads(int size);

	QThread * addThread();
private:
	QVector<QThread *> mThreadVector;
	int mMaxFreeThreadSize;
	QThread * mManagerThread;
	QMutex mMutex;
};
