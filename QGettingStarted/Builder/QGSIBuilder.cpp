#include <QCoreApplication> 

#include "QGSIBuilder.h"
#include "../Util/QGSExceptionInvalidValue.h"
#include "../Util/QGSExceptionIO.h"

QGSIBuilder::QGSIBuilder(QGSThreadPoolManager * threadPoolManagerPtr, QGSGameDirectory * gameDirectory, QObject * parent)
	:QGSTask(parent), mLastErrorString(""), mGameDirectoryPtr(gameDirectory), mThreadPoolManagerPtr(threadPoolManagerPtr)
{
	if (!mThreadPoolManagerPtr || !gameDirectory)
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
