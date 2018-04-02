#pragma once

#include "QGSIAccount.h"

class QGSOfflineAccount :public QGSIAccount
{
	Q_OBJECT

public:
	QGSOfflineAccount(QObject * parent = nullptr);

	virtual ~QGSOfflineAccount();

	QGSOfflineAccount(const QGSOfflineAccount & right) = default;

	QGSOfflineAccount(QGSOfflineAccount && right) = default;

	QGSOfflineAccount & operator=(const QGSOfflineAccount & right) = default;

	QGSOfflineAccount & operator=(QGSOfflineAccount && right) = default;

	virtual QGSAuthInfo authenticate(const QString & userName, const QString & password = "", QString clientToken = "", QNetworkProxy proxy = QNetworkProxy::NoProxy)noexcept override;

private:

};

