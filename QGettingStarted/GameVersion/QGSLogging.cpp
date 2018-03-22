#include "QGSLogging.h"

QGSLogging::QGSLogging(const File & file, const QString & argument, const QString & type) :mFile(file), mArgument(argument), mType(type)
{
}

QGSLogging::~QGSLogging()
{
}

QGSLogging & QGSLogging::setFile(const File & file)
{
	mFile = file;
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

QGSLogging::File QGSLogging::getFile()const
{
	return mFile;
}

QString QGSLogging::getArgument()const
{
	return mArgument;
}

QString QGSLogging::getType()const
{
	return mType;
}



