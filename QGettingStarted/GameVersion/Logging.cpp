#include "Logging.h"

Logging::Logging(const File & file, const QString & argument, const QString & type) :mFile(file), mArgument(argument), mType(type)
{
}

Logging::~Logging()
{
}

Logging & Logging::setFile(const File & file)
{
	mFile = file;
	return *this;
}

Logging & Logging::setArgument(const QString & argument)
{
	mArgument = argument;
	return *this;
}

Logging & Logging::setType(const QString & type)
{
	mType = type;
	return *this;
}

Logging::File Logging::getFile()const
{
	return mFile;
}

QString Logging::getArgument()const
{
	return mArgument;
}

QString Logging::getType()const
{
	return mType;
}



