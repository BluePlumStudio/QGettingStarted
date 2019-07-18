#pragma once

#include <QString>
#include <QObject>

#include "QGSAuthInfo.h"
#include "../Util/QGSNetworkHelper.h"

class QGSIAccount :public QObject
{
	Q_OBJECT

public:
	QGSIAccount(QObject * parent = nullptr);

	virtual ~QGSIAccount();

	QGSIAccount(const QGSIAccount & right) = default;

	QGSIAccount(QGSIAccount && right) = default;

	QGSIAccount & operator=(const QGSIAccount & right) = default;

	QGSIAccount & operator=(QGSIAccount && right) = default;

	virtual void authenticate(const QString & userName, const QString & password = "", QString clientToken = "", QNetworkProxy proxy = QNetworkProxy::NoProxy) = 0;
	//authenticate(const QString & userName, const QString & password = "", QString clientToken = "", QNetworkProxy proxy = QNetworkProxy::NoProxy)
signals:
	void finished(QGSAuthInfo authInfo);
	void error(QGSNetworkError networkError);
};

