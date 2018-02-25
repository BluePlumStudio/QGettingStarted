#pragma once

#include "IAccountFactory.h"
#include "QGSOfflineAccount.h"

class QGSOfflineAccountFactory: public IAccountFactory 
{
public: 
	QGSOfflineAccountFactory();

	QGSOfflineAccountFactory(const IAccountFactory & right) = delete;

	QGSOfflineAccountFactory(QGSOfflineAccountFactory && right) = delete;

	QGSOfflineAccountFactory & operator=(const QGSOfflineAccountFactory & right) = delete;

	QGSOfflineAccountFactory & operator=(QGSOfflineAccountFactory && right) = delete;

	virtual ~QGSOfflineAccountFactory();

	virtual QGSOfflineAccount * createAccount()const override;
private:
	
};