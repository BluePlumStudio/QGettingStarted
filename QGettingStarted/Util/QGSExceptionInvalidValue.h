#pragma once

#include "QGSException.h"

class QGSExceptionInvalidValue :public QGSException
{
public:
	QGSExceptionInvalidValue();
	
	virtual ~QGSExceptionInvalidValue();

	virtual QGSExceptionInvalidValue * clone()const override;

	virtual void raise()const override;
};
