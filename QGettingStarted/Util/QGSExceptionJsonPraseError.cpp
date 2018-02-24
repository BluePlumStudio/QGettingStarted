#include "QGSExceptionJsonPraseError.h"

QGSExceptionJsonPraseError::QGSExceptionJsonPraseError() 
{
}

QGSExceptionJsonPraseError::~QGSExceptionJsonPraseError()
{
}

QGSExceptionJsonPraseError * QGSExceptionJsonPraseError::clone()const
{
	return new QGSExceptionJsonPraseError(*this);
}

void QGSExceptionJsonPraseError::raise()const
{
	throw *this;
}