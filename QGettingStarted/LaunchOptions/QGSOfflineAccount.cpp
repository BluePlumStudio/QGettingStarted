#include "QGSOfflineAccount.h"
#include "../Util/QGSUuidGenerator.h"

QGSOfflineAccount::QGSOfflineAccount(QObject * parent) :QGSIAccount(parent)
{
}

QGSOfflineAccount::~QGSOfflineAccount()
{
}

void QGSOfflineAccount::authenticate(const QString & userName, const QString & password, QString clientToken, QNetworkProxy proxy)noexcept
{
	QMetaObject::invokeMethod(this,
		"finished", 
		Qt::QueuedConnection,
		Q_ARG(QGSAuthInfo,
			QGSAuthInfo(QGSUuidGenerator::getInstance().generateUuid(userName),
				clientToken.isEmpty() ? QGSUuidGenerator::getInstance().generateUuid(userName) : clientToken,
				UserType::Legacy,
				QGSAuthInfo::QGSProfile(QGSUuidGenerator::getInstance().generateUuid(userName), userName, false))));
}
