#pragma once

#include "QGSIAccountFactory.h"
#include "QGSOfflineAccount.h"

/**

* @brief 离线账户工厂

*/
class QGSOfflineAccountFactory: public QGSIAccountFactory 
{
	Q_OBJECT

public: 
	QGSOfflineAccountFactory(QObject * parent = nullptr);

	QGSOfflineAccountFactory(const QGSIAccountFactory & right) = delete;

	QGSOfflineAccountFactory(QGSOfflineAccountFactory && right) = delete;

	QGSOfflineAccountFactory & operator=(const QGSOfflineAccountFactory & right) = delete;

	QGSOfflineAccountFactory & operator=(QGSOfflineAccountFactory && right) = delete;

	virtual ~QGSOfflineAccountFactory();

	virtual QGSOfflineAccount * createAccount()const override;
private:
	
};