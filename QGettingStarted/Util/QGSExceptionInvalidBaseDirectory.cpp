#include "QGSExceptionInvalidBaseDirectory.h"

QGSExceptionInvalidBaseDirectory::QGSExceptionInvalidBaseDirectory()
{
}

QGSExceptionInvalidBaseDirectory::~QGSExceptionInvalidBaseDirectory()
{
}

QGSExceptionInvalidBaseDirectory * QGSExceptionInvalidBaseDirectory::clone()const
{
	return new QGSExceptionInvalidBaseDirectory(*this);
}

void QGSExceptionInvalidBaseDirectory::raise()const
{
	throw *this;
}