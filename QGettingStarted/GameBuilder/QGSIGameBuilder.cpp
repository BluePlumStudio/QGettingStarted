#include "QGSIGameBuilder.h"
#include "../Util/QGSExceptionInvalidValue.h"
#include "../Util/QGSExceptionFileIO.h"

static const int DEFAULT_MAX_CONNECTION_COUNT = 8;

QGSIGameBuilder::QGSIGameBuilder(QGSIDownloadSource * downloadSource, QGSGameDirectory * gameDirectory, QObject * parent)
	:QObject(parent), mMaxConnectionCount(DEFAULT_MAX_CONNECTION_COUNT), mDownloadTimeout(Network::DefaultTimeout), mGameDirectoryPtr(gameDirectory)
{
	if (!downloadSource || !gameDirectory)
	{
		throw QGSExceptionInvalidValue();
	}
	if (!mTemporaryDir.isValid())
	{
		throw QGSExceptionFileIO{ mTemporaryDir.path() };
	}
}

QGSIGameBuilder::~QGSIGameBuilder()
{

}

QGSIGameBuilder & QGSIGameBuilder::setMaxConnectionCount(const int maxConnectionCount)
{
	mMaxConnectionCount = maxConnectionCount;
	return *this;
}

QGSIGameBuilder & QGSIGameBuilder::setDownloadTimeout(const int msec)
{
	mDownloadTimeout = msec;
	return *this;
}

int QGSIGameBuilder::getDownloadTimeout() const
{
	return mDownloadTimeout;
}

int QGSIGameBuilder::getMaxConnectionCount() const
{
	return mMaxConnectionCount;
}
