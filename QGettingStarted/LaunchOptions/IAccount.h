#pragma once

#include <QString>

#include "AuthInfo.h"

class IAccount
{
public:
	IAccount();

	virtual ~IAccount();

	IAccount(const IAccount & right) = default;

	IAccount(IAccount && right) = default;

	IAccount & operator=(const IAccount & right) = default;

	IAccount & operator=(IAccount && right) = default;

	virtual AuthInfo signIn(const QString & userName, const QString & password, const QString & clientToken = "")const = 0;
private:

};

