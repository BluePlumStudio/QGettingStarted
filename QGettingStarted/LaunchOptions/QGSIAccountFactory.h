#pragma once

#include <QString>

#include "QGSIAccount.h"

/**

* @brief 账户工厂（抽象）

*/
class QGSIAccountFactory :public QObject
{
	Q_OBJECT

public:
	QGSIAccountFactory(QObject * parent = nullptr);

	QGSIAccountFactory(const QGSIAccountFactory & right) = delete;

	QGSIAccountFactory(QGSIAccountFactory && right) = delete;

	QGSIAccountFactory & operator=(const QGSIAccountFactory & right) = delete;

	QGSIAccountFactory & operator=(QGSIAccountFactory && right) = delete;

	virtual ~QGSIAccountFactory();

	virtual QGSIAccount * createAccount()const = 0;

private:
	
};
