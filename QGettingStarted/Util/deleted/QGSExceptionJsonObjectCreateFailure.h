#pragma once

#include "QGSException.h"
#include "QGSExceptionJsonPraseError.h"
#include <QJsonDocument>
#include <QJsonObject>

class QGSExceptionJsonObjectCreateFailure :public QGSExceptionJsonPraseError
{
public:
	QGSExceptionJsonObjectCreateFailure();

	virtual ~QGSExceptionJsonObjectCreateFailure();

	virtual QGSExceptionJsonObjectCreateFailure * clone()const override;

	virtual void raise()const override;
private:

};

