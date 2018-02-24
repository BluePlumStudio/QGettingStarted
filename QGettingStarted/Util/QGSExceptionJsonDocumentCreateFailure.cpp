#include "QGSExceptionJsonDocumentCreateFailure.h"

QGSExceptionJsonDocumentCreateFailure::QGSExceptionJsonDocumentCreateFailure(const QJsonParseError & jsonPraseError):mJsonPraseError(jsonPraseError)
{
}

QGSExceptionJsonDocumentCreateFailure::~QGSExceptionJsonDocumentCreateFailure()
{
}

QGSExceptionJsonDocumentCreateFailure * QGSExceptionJsonDocumentCreateFailure::clone()const
{
	return new QGSExceptionJsonDocumentCreateFailure(*this);
}

void QGSExceptionJsonDocumentCreateFailure::raise()const
{
	throw *this;
}

QJsonParseError QGSExceptionJsonDocumentCreateFailure::getJsonPraseError()const
{
	return mJsonPraseError;
}