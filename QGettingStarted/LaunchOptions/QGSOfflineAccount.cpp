#include "QGSOfflineAccount.h"
#include "../Util/QGSUuidGenerator.h"

QGSOfflineAccount::QGSOfflineAccount(QObject * parent) :QGSIAccount(parent)
{
}

QGSOfflineAccount::~QGSOfflineAccount()
{
}

QGSAuthInfo QGSOfflineAccount::authenticate(const QString & userName, const QString & password, QString clientToken, QNetworkProxy proxy)noexcept
{
	return QGSAuthInfo(QGSUuidGenerator::getInstance().generateUuid(userName),
	clientToken.isEmpty() ? QGSUuidGenerator::getInstance().generateUuid(userName) : clientToken,
		UserType::Legacy,
	QGSAuthInfo::QGSProfile(QGSUuidGenerator::getInstance().generateUuid(userName),userName,false));
}
