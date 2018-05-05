#pragma once

#include "QGSException.h"

class QGSExceptionVersionNotFound :public QGSException
{
public:
	QGSExceptionVersionNotFound();

	virtual ~QGSExceptionVersionNotFound();

	virtual QGSExceptionVersionNotFound * clone()const override;

	virtual void raise()const override;

private:

};