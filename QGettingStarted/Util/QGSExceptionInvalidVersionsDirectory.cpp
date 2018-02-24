#include "QGSExceptionInvalidVersionsDirectory.h"

QGSExceptionInvalidVersionsDirectory::QGSExceptionInvalidVersionsDirectory()
{
}

QGSExceptionInvalidVersionsDirectory::~QGSExceptionInvalidVersionsDirectory()
{
}

QGSExceptionInvalidVersionsDirectory * QGSExceptionInvalidVersionsDirectory::clone()const
{
	return new QGSExceptionInvalidVersionsDirectory(*this);
}

void QGSExceptionInvalidVersionsDirectory::raise()const
{
	throw *this;
}