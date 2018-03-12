#include "QGSExceptionInvalidValue.h"

QGSExceptionInvalidValue::QGSExceptionInvalidValue()
{
}

QGSExceptionInvalidValue::~QGSExceptionInvalidValue()
{
}

QGSExceptionInvalidValue * QGSExceptionInvalidValue::clone() const
{
	return new QGSExceptionInvalidValue(*this);
}

void QGSExceptionInvalidValue::raise() const
{
	throw *this;
}
