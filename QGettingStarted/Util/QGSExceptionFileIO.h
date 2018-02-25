#pragma once

#include "QGSException.h"

class QGSExceptionFileIO :public QGSException
{
public:
	QGSExceptionFileIO();

	QGSExceptionFileIO(const QString & absolutePath);

	virtual ~QGSExceptionFileIO();

	virtual QGSExceptionFileIO * clone()const override;

	virtual void raise()const override;

	QString getAbsolutePath()const;
private:
	QString mAbsolutePath;
};

