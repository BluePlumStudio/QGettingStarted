#pragma once

#include "QGSException.h"

class QGSExceptionCompress :public QGSException
{
public:
	QGSExceptionCompress(const QString & file = "", const QString & directory = "");

	virtual QGSExceptionCompress * clone()const override;

	virtual void raise()const override;

	virtual ~QGSExceptionCompress();

	QString getFile()const;

	QString getDirectory()const;

private:
	QString mFile;
	QString mDirectory;
};