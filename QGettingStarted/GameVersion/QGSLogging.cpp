#include "QGSLogging.h"

QGSLogging::QGSLogging(const QGSLoggingDownload & fileDownload, const QString & argument, const QString & type) :mLoggingDownload(fileDownload), mArgument(argument), mType(type)
{
}

QGSLogging::~QGSLogging()
{
}

QGSLogging & QGSLogging::setLoggingDownload(const QGSLoggingDownload & fileDownload)
{
	mLoggingDownload = fileDownload;
	return *this;
}

QGSLogging & QGSLogging::setArgument(const QString & argument)
{
	mArgument = argument;
	return *this;
}

QGSLogging & QGSLogging::setType(const QString & type)
{
	mType = type;
	return *this;
}

QGSLogging::QGSLoggingDownload QGSLogging::getLoggingDownload()const
{
	return mLoggingDownload;
}

QString QGSLogging::getArgument()const
{
	return mArgument;
}

QString QGSLogging::getType()const
{
	return mType;
}



