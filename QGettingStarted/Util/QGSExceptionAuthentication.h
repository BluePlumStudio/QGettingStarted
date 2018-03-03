#pragma once

#include <QException>
#include <QString>

class QGSExceptionAuthentication :public QException
{
public:
	QGSExceptionAuthentication(const QString & error = "", const QString & errorMessage = "", const QString & cause = "");

	virtual ~QGSExceptionAuthentication();

	virtual QGSExceptionAuthentication * clone()const override;

	virtual void raise()const override;

	QString getError()const;

	QString getErrorMessage()const;

	QString getCause()const;
private:
	QString mError;
	QString mErrorMessage;
	QString mCause;
};