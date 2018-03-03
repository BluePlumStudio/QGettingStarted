#include "QGSExceptionFileIO.h"

QGSExceptionFileIO::QGSExceptionFileIO(const QString & absolutePath) :mAbsolutePath(absolutePath)
{
}

QGSExceptionFileIO::~QGSExceptionFileIO()
{
}

QGSExceptionFileIO * QGSExceptionFileIO::clone()const
{
	return new QGSExceptionFileIO(*this);
}

void QGSExceptionFileIO::raise()const
{
	throw *this;
}

QString QGSExceptionFileIO::getAbsolutePath() const
{
	return mAbsolutePath;
}
