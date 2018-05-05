#include <QCoreApplication> 

#include "QGSIBuilder.h"
#include "../Util/QGSExceptionInvalidValue.h"
#include "../Util/QGSExceptionIO.h"

QGSIBuilder::QGSIBuilder(QGSThreadPoolManager * threadPoolManagerPtr, QObject * parent)
	:QGSTask(parent), mLastErrorString(""), mThreadPoolManagerPtr(threadPoolManagerPtr)
{
	if (!mThreadPoolManagerPtr)
	{
		throw QGSExceptionInvalidValue();
	}
}

QGSIBuilder::~QGSIBuilder()
{

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
