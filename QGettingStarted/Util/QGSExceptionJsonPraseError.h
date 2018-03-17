#pragma once

#include "QGSException.h"
#include <QJsonDocument>

class QGSExceptionJsonPraseError :public QGSException
{
public:
	QGSExceptionJsonPraseError(const QJsonParseError & jsonPraseError = QJsonParseError(), const QString & errorMessage = "");

	virtual ~QGSExceptionJsonPraseError();

	virtual QGSExceptionJsonPraseError * clone()const override;

	virtual void raise()const override;

	QJsonParseError getJsonPraseError()const;

	QString getErrorMessage()const;
private:
	QJsonParseError mJsonPraseError;
	QString mErrorMessage;
};

