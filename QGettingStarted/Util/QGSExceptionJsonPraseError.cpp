#include "QGSExceptionJsonPraseError.h"

QGSExceptionJsonPraseError::QGSExceptionJsonPraseError(const QJsonParseError & jsonPraseError, const QString & errorMessage)
	:mJsonPraseError(jsonPraseError), mErrorMessage(errorMessage)
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

QJsonParseError QGSExceptionJsonPraseError::getJsonPraseError()const
{
	return mJsonPraseError;
}

QString QGSExceptionJsonPraseError::getErrorMessage() const
{
	return mErrorMessage;
}
