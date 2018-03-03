#pragma once

#include <QString>

#include "QGSIAccount.h"
#include "Util/QGSNetwork.h"

class QGSYggdrasilAccount
{
public:
	QGSYggdrasilAccount();

	virtual ~QGSYggdrasilAccount();

	QGSYggdrasilAccount(const QGSYggdrasilAccount & right) = delete;

	QGSYggdrasilAccount(QGSYggdrasilAccount && right) = delete;

	QGSYggdrasilAccount & operator=(const QGSYggdrasilAccount & right) = delete;

	QGSYggdrasilAccount & operator=(QGSYggdrasilAccount && right) = delete;

	virtual AuthInfo authenticate(const QString & userName, const QString & password = "", QString clientToken = "");
private:
	QNetworkRequest * generateNetworkRequest();
};
