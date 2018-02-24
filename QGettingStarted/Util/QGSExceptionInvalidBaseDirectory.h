#pragma once

#include "QGSExceptionGameDirectory.h"

class QGSExceptionInvalidBaseDirectory :public QGSExceptionGameDirectory
{
public:
	QGSExceptionInvalidBaseDirectory();

	virtual ~QGSExceptionInvalidBaseDirectory();

	virtual QGSExceptionInvalidBaseDirectory * clone()const override;

	virtual void raise()const override;

private:

};
