#pragma once

#include "QGSIAccountFactory.h"
#include "QGSYggdrasilAccount.h"

class QGSYggdrasilAccountFactory : public QGSIAccountFactory
{
public:
	QGSYggdrasilAccountFactory();

	QGSYggdrasilAccountFactory(const QGSIAccountFactory & right) = delete;

	QGSYggdrasilAccountFactory(QGSYggdrasilAccountFactory && right) = delete;

	QGSYggdrasilAccountFactory & operator=(const QGSYggdrasilAccountFactory & right) = delete;

	QGSYggdrasilAccountFactory & operator=(QGSYggdrasilAccountFactory && right) = delete;

	virtual ~QGSYggdrasilAccountFactory();

	virtual QGSYggdrasilAccount * createAccount()const override;
private:

};