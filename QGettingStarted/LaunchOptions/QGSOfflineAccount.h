#pragma once

#include "QGSIAccount.h"

class QGSOfflineAccount :public QGSIAccount
{
public:
	QGSOfflineAccount();

	virtual ~QGSOfflineAccount();

	QGSOfflineAccount(const QGSOfflineAccount & right) = default;

	QGSOfflineAccount(QGSOfflineAccount && right) = default;

	QGSOfflineAccount & operator=(const QGSOfflineAccount & right) = default;

	QGSOfflineAccount & operator=(QGSOfflineAccount && right) = default;

	virtual AuthInfo authenticate(const QString & userName, const QString & password = "", QString clientToken = "")noexcept override;

private:

};

