#pragma once

#include <QString>

#include "AuthInfo.h"

class QGSIAccount
{
public:
	QGSIAccount();

	virtual ~QGSIAccount();

	QGSIAccount(const QGSIAccount & right) = default;

	QGSIAccount(QGSIAccount && right) = default;

	QGSIAccount & operator=(const QGSIAccount & right) = default;

	QGSIAccount & operator=(QGSIAccount && right) = default;

	virtual AuthInfo authenticate(const QString & userName, const QString & password = "", const QString & clientToken = "")const = 0;
private:

};

