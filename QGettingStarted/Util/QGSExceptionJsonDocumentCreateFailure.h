#pragma once

#include "QGSException.h"
#include "QGSExceptionJsonPraseError.h"
#include <QJsonDocument>

class QGSExceptionJsonDocumentCreateFailure :public QGSExceptionJsonPraseError
{
public:
	QGSExceptionJsonDocumentCreateFailure() = default;

	QGSExceptionJsonDocumentCreateFailure(const QJsonParseError & jsonPraseError);

	virtual ~QGSExceptionJsonDocumentCreateFailure();

	virtual QGSExceptionJsonDocumentCreateFailure * clone()const override;

	virtual void raise()const override;

	QJsonParseError getJsonPraseError()const;
private:
	QJsonParseError mJsonPraseError;
};

