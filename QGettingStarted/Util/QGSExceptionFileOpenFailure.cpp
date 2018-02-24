#include "QGSExceptionFileOpenFailure.h"

QGSExceptionFileOpenFailure::QGSExceptionFileOpenFailure()
{
}

QGSExceptionFileOpenFailure::~QGSExceptionFileOpenFailure()
{
}

QGSExceptionFileOpenFailure * QGSExceptionFileOpenFailure::clone()const
{
	return new QGSExceptionFileOpenFailure(*this);
}

void QGSExceptionFileOpenFailure::raise()const
{
	throw *this;
}