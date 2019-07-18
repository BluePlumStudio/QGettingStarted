#pragma once

#include <QString>

#include "QGSIAccount.h"
#include "../Util/QGSNetworkHelper.h"

class QGSYggdrasilAccount :public QGSIAccount
{
	Q_OBJECT

public:
	QGSYggdrasilAccount(QObject * parent = nullptr);

	virtual ~QGSYggdrasilAccount();

	QGSYggdrasilAccount(const QGSYggdrasilAccount & right) = delete;

	QGSYggdrasilAccount(QGSYggdrasilAccount && right) = delete;

	QGSYggdrasilAccount & operator=(const QGSYggdrasilAccount & right) = delete;

	QGSYggdrasilAccount & operator=(QGSYggdrasilAccount && right) = delete;

	virtual void authenticate(const QString & userName, const QString & password = "", QString clientToken = "", QNetworkProxy proxy = QNetworkProxy::NoProxy);
private slots:
	void slotFinished();
	void slotError(QNetworkReply::NetworkError code);
private:
	QNetworkReply * mReply;
	QGSNetworkHelper * mNetworkAccessManager;
};
