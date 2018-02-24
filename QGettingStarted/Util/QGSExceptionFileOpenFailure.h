#pragma once

#include "QGSException.h"

class QGSExceptionFileOpenFailure :public QGSException
{
public:
	QGSExceptionFileOpenFailure();

	virtual ~QGSExceptionFileOpenFailure();

	virtual QGSExceptionFileOpenFailure * clone()const override;

	virtual void raise()const override;

private:

};

