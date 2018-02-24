#pragma once

#include "QGSExceptionGameDirectory.h"

class QGSExceptionVersionNotFound :public QGSExceptionGameDirectory
{
public:
	QGSExceptionVersionNotFound();

	virtual ~QGSExceptionVersionNotFound();

	virtual QGSExceptionVersionNotFound * clone()const override;

	virtual void raise()const override;

private:

};