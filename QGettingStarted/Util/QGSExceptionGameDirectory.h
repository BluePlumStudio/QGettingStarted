#pragma once

#include "QGSException.h"

class QGSExceptionGameDirectory :public QGSException
{
public:
	QGSExceptionGameDirectory();

	virtual ~QGSExceptionGameDirectory();

	virtual QGSExceptionGameDirectory * clone()const override;

	virtual void raise()const override;

private:

};

