#include "QGSExceptionJsonObjectCreateFailure.h"

QGSExceptionJsonObjectCreateFailure::QGSExceptionJsonObjectCreateFailure()
{
}

QGSExceptionJsonObjectCreateFailure::~QGSExceptionJsonObjectCreateFailure()
{
}

QGSExceptionJsonObjectCreateFailure * QGSExceptionJsonObjectCreateFailure::clone()const
{
	return new QGSExceptionJsonObjectCreateFailure(*this);
}

void QGSExceptionJsonObjectCreateFailure::raise()const
{
	throw *this;
}