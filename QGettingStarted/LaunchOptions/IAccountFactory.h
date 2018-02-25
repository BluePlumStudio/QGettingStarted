#pragma once

#include <QString>

#include "IAccount.h"

class IAccountFactory
{
public:
	IAccountFactory();

	IAccountFactory(const IAccountFactory & right) = delete;

	IAccountFactory(IAccountFactory && right) = delete;

	IAccountFactory & operator=(const IAccountFactory & right) = delete;

	IAccountFactory & operator=(IAccountFactory && right) = delete;

	virtual ~IAccountFactory();

	virtual IAccount * createAccount()const = 0;

private:
	
};
