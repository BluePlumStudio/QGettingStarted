#include "QGSExceptionIO.h"

QGSExceptionIO::QGSExceptionIO(const QString & absolutePath) :mAbsolutePath(absolutePath)
{
}

QGSExceptionIO::~QGSExceptionIO()
{
}

QGSExceptionIO * QGSExceptionIO::clone()const
{
	return new QGSExceptionIO(*this);
}

void QGSExceptionIO::raise()const
{
	throw *this;
}

QString QGSExceptionIO::getAbsolutePath() const
{
	return mAbsolutePath;
}
