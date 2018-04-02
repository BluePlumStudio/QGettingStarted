#pragma once

#include "QGSException.h"

class QGSExceptionIO :public QGSException
{
public:
	QGSExceptionIO(const QString & absolutePath = "");

	virtual ~QGSExceptionIO();

	virtual QGSExceptionIO * clone()const override;

	virtual void raise()const override;

	QString getAbsolutePath()const;
private:
	QString mAbsolutePath;
};

