#include "QGSExceptionCompress.h"

QGSExceptionCompress::QGSExceptionCompress(const QString & file, const QString & directory)
	:mFile(file), mDirectory(directory)
{

}

QGSExceptionCompress::~QGSExceptionCompress()
{
}

QString QGSExceptionCompress::getFile() const
{
	return mFile;
}

QString QGSExceptionCompress::getDirectory() const
{
	return mDirectory;
}

QGSExceptionCompress * QGSExceptionCompress::clone()const
{
	return new QGSExceptionCompress(*this);
}

void QGSExceptionCompress::raise()const
{
	throw *this;
}