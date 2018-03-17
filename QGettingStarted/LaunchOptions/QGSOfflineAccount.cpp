#include "QGSOfflineAccount.h"
#include "../Util/QGSUuidGenerator.h"

QGSOfflineAccount::QGSOfflineAccount()
{
}

QGSOfflineAccount::~QGSOfflineAccount()
{
}

AuthInfo QGSOfflineAccount::authenticate(const QString & userName, const QString & password, QString clientToken, QNetworkProxy proxy)noexcept
{
	return AuthInfo{ QGSUuidGenerator::getInstance().generateUuid(userName),
	clientToken.isEmpty() ? QGSUuidGenerator::getInstance().generateUuid(userName) : clientToken,
		UserType::Legacy,
	AuthInfo::Profile{ QGSUuidGenerator::getInstance().generateUuid(userName),userName,false} };
}
