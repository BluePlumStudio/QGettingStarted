#pragma once

#include "QGSIAccountFactory.h"
#include "QGSOfflineAccount.h"

class QGSOfflineAccountFactory: public QGSIAccountFactory 
{
public: 
	QGSOfflineAccountFactory();

	QGSOfflineAccountFactory(const QGSIAccountFactory & right) = delete;

	QGSOfflineAccountFactory(QGSOfflineAccountFactory && right) = delete;

	QGSOfflineAccountFactory & operator=(const QGSOfflineAccountFactory & right) = delete;

	QGSOfflineAccountFactory & operator=(QGSOfflineAccountFactory && right) = delete;

	virtual ~QGSOfflineAccountFactory();

	virtual QGSOfflineAccount * createAccount()const override;
private:
	
};