#pragma once

#include "QGSException.h"
#include <QJsonDocument>

class QGSExceptionJsonPraseError :public QGSException
{
public:
	QGSExceptionJsonPraseError();

	virtual ~QGSExceptionJsonPraseError();

	virtual QGSExceptionJsonPraseError * clone()const override;

	virtual void raise()const override;
private:
	QJsonParseError mJsonPraseError;
};

