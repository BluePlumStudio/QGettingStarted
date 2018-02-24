#include "QGSExceptionGameDirectory.h"

QGSExceptionGameDirectory::QGSExceptionGameDirectory()
{
}

QGSExceptionGameDirectory::~QGSExceptionGameDirectory()
{
}

QGSExceptionGameDirectory * QGSExceptionGameDirectory::clone()const
{
	return new QGSExceptionGameDirectory(*this);
}

void QGSExceptionGameDirectory::raise()const
{
	throw *this;
}