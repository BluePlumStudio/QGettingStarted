#include "QGSException.h"

QGSException::QGSException()
{
}

QGSException::~QGSException()
{
}

QGSException * QGSException::clone()const
{
	return new QGSException(*this);
}

void QGSException::raise()const
{
	throw *this;
}