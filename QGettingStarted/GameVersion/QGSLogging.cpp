#include "QGSLogging.h"

QGSLogging::QGSLogging(const QGSFileDownload & fileDownload, const QString & argument, const QString & type) :mFileDownload(fileDownload), mArgument(argument), mType(type)
{
}

QGSLogging::~QGSLogging()
{
}

QGSLogging & QGSLogging::setFileDownload(const QGSFileDownload & fileDownload)
{
	mFileDownload = fileDownload;
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

QGSLogging::QGSFileDownload QGSLogging::getFileDownload()const
{
	return mFileDownload;
}

QString QGSLogging::getArgument()const
{
	return mArgument;
}

QString QGSLogging::getType()const
{
	return mType;
}



