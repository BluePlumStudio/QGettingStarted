#pragma once

#include <QString>

#include "QGSAuthInfo.h"
#include "Util/QGSNetworkAccessManager.h"

class QGSIAccount
{
public:
	QGSIAccount();

	virtual ~QGSIAccount();

	QGSIAccount(const QGSIAccount & right) = default;

	QGSIAccount(QGSIAccount && right) = default;

	QGSIAccount & operator=(const QGSIAccount & right) = default;

	QGSIAccount & operator=(QGSIAccount && right) = default;

	virtual QGSAuthInfo authenticate(const QString & userName, const QString & password = "", QString clientToken = "", QNetworkProxy proxy = QNetworkProxy::NoProxy) = 0;
	//authenticate(const QString & userName, const QString & password = "", QString clientToken = "", QNetworkProxy proxy = QNetworkProxy::NoProxy)
private:

};

