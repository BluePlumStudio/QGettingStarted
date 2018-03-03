#include "QGSExceptionAuthentication.h"

QGSExceptionAuthentication::QGSExceptionAuthentication(const QString & error, const QString & errorMessage, const QString & cause)
	:mError(error), mErrorMessage(errorMessage), mCause(cause)
{

}

QGSExceptionAuthentication::~QGSExceptionAuthentication()
{

}

QGSExceptionAuthentication * QGSExceptionAuthentication::clone() const
{
	return new QGSExceptionAuthentication(*this);
}

void QGSExceptionAuthentication::raise() const
{
	throw *this;
}

QString QGSExceptionAuthentication::getError() const
{
	return mError;
}

QString QGSExceptionAuthentication::getErrorMessage() const
{
	return mErrorMessage;
}

QString QGSExceptionAuthentication::getCause() const
{
	return mCause;
}
