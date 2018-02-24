#pragma once

#include <QException>

class QGSException :public QException
{
public:
	QGSException();

	virtual ~QGSException();

	virtual QGSException * clone()const override;

	virtual void raise()const override;

private:

};
