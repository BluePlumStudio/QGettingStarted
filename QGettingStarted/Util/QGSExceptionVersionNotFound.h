#pragma once

#include <QException>

class QGSExceptionVersionNotFound :public QException
{
public:
	QGSExceptionVersionNotFound();

	virtual ~QGSExceptionVersionNotFound();

	virtual QGSExceptionVersionNotFound * clone()const override;

	virtual void raise()const override;

private:

};