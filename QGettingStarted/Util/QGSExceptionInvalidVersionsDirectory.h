#pragma once

#include "QGSExceptionGameDirectory.h"

class QGSExceptionInvalidVersionsDirectory :public QGSExceptionGameDirectory
{
public:
	QGSExceptionInvalidVersionsDirectory();

	virtual ~QGSExceptionInvalidVersionsDirectory();

	virtual QGSExceptionInvalidVersionsDirectory * clone()const override;

	virtual void raise()const override;

private:

};
