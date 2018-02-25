#include "QGSOfflineAccount.h"
#include "../Util/QGSUuidGenerator.h"

QGSOfflineAccount::QGSOfflineAccount()
{
}

QGSOfflineAccount::~QGSOfflineAccount()
{
}

AuthInfo QGSOfflineAccount::signIn(const QString & userName, const QString & password, const QString & clientToken)const
{
	return AuthInfo{ QGSUuidGenerator::getInstance().generateUuid(userName),
	clientToken.isEmpty() ? QGSUuidGenerator::getInstance().generateUuid(userName) : clientToken,
		UserType::LEGACY,
	AuthInfo::Profile{ QGSUuidGenerator::getInstance().generateUuid(userName),userName,false} };
}
