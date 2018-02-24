#include "QGSExceptionVersionNotFound.h"

QGSExceptionVersionNotFound::QGSExceptionVersionNotFound()
{
}

QGSExceptionVersionNotFound::~QGSExceptionVersionNotFound()
{
}

QGSExceptionVersionNotFound * QGSExceptionVersionNotFound::clone()const
{
	return new QGSExceptionVersionNotFound(*this);
}

void QGSExceptionVersionNotFound::raise()const
{
	throw *this;
}