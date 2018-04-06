#include "QGSIBuilder.h"
#include "../Util/QGSExceptionInvalidValue.h"
#include "../Util/QGSExceptionIO.h"

QGSThreadPool QGSIBuilder::mThreadPool(0, 16);

QGSIBuilder::QGSIBuilder(QObject * parent)
	:QGSTask(parent), mLastErrorString("")
{
	if (!mThreadPool.isRunning())
	{
		mThreadPool.start();
	}
}

QGSIBuilder::~QGSIBuilder()
{

}

QGSThreadPool & QGSIBuilder::getThreadPool()
{
	return mThreadPool;
}

QString QGSIBuilder::getLastErrorString()
{
	QMutexLocker mutexLocker(&mMutex);

	return mLastErrorString;
}

void QGSIBuilder::setLastErrorString(QString lastErrorString)
{
	QMutexLocker mutexLocker(&mMutex);
	
	mLastErrorString = lastErrorString;
}
