#include "QGSIBuilder.h"
#include "../Util/QGSExceptionInvalidValue.h"
#include "../Util/QGSExceptionIO.h"

QGSThreadPool QGSIBuilder::mThreadPool(8, 64);

QGSIBuilder::QGSIBuilder(QObject * parent)
	:QGSTask(parent)
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

