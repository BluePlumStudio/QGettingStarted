#pragma once

#include "IAccount.h"

class QGSOfflineAccount :public IAccount
{
public:
	QGSOfflineAccount();

	virtual ~QGSOfflineAccount();

	QGSOfflineAccount(const QGSOfflineAccount & right) = default;

	QGSOfflineAccount(QGSOfflineAccount && right) = default;

	QGSOfflineAccount & operator=(const QGSOfflineAccount & right) = default;

	QGSOfflineAccount & operator=(QGSOfflineAccount && right) = default;

	virtual AuthInfo signIn(const QString & userName, const QString & password, const QString & clientToken = "")const override;

private:

};

