#pragma once

#include <QString>

#include "QGSIAccount.h"

class QGSIAccountFactory
{
public:
	QGSIAccountFactory();

	QGSIAccountFactory(const QGSIAccountFactory & right) = delete;

	QGSIAccountFactory(QGSIAccountFactory && right) = delete;

	QGSIAccountFactory & operator=(const QGSIAccountFactory & right) = delete;

	QGSIAccountFactory & operator=(QGSIAccountFactory && right) = delete;

	virtual ~QGSIAccountFactory();

	virtual QGSIAccount * createAccount()const = 0;

private:
	
};
