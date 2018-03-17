#pragma once

#include <QString>

#include "AuthInfo.h"
#include "Util/QGSNetwork.h"

class QGSIAccount
{
public:
	QGSIAccount();

	virtual ~QGSIAccount();

	QGSIAccount(const QGSIAccount & right) = default;

	QGSIAccount(QGSIAccount && right) = default;

	QGSIAccount & operator=(const QGSIAccount & right) = default;

	QGSIAccount & operator=(QGSIAccount && right) = default;

	virtual AuthInfo authenticate(const QString & userName, const QString & password = "", QString clientToken = "", QNetworkProxy proxy = QNetworkProxy::NoProxy) = 0;
	//authenticate(const QString & userName, const QString & password = "", QString clientToken = "", QNetworkProxy proxy = QNetworkProxy::NoProxy)
private:

};

