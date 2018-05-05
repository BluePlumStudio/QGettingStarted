#include <QEventLoop>
#include <QMetaType> 

#include "QGSNetworkAccessManager.h"

QGSNetworkError::QGSNetworkError(const QNetworkReply::NetworkError code, const QString & errorString)
	:mCode(code), mErrorString(errorString)
{
	qRegisterMetaType<QGSNetworkError>("QGSNetworkError");
}

QGSNetworkError::~QGSNetworkError()
{

}

QNetworkReply::NetworkError QGSNetworkError::getCode()const
{
	return mCode;
}

QString QGSNetworkError::getErrorString()const
{
	return mErrorString;
}

/**/

const int QGSNetworkAccessManager::DefaultTimeout = 300000;

QGSNetworkAccessManager::QGSNetworkAccessManager(QObject * parent) :QNetworkAccessManager(parent)//, mManager(new QNetworkAccessManager)
{
}

/*
QNetworkAccessManager * QGSNetworkAccessManager::getManager()
{
	return mManager;
}
*/

QGSNetworkAccessManager::~QGSNetworkAccessManager()
{
	/*
	if (mManager)
	{
		mManager->deleteLater();
	}
	*/
}

QNetworkRequest QGSNetworkAccessManager::generateNetworkRequest()
{
	return QNetworkRequest();
}

QNetworkRequest QGSNetworkAccessManager::generateHttpsNetworkRequest(QSsl::SslProtocol protocol)
{
	QNetworkRequest networkRequest;

	QSslConfiguration config = QSslConfiguration::defaultConfiguration();
	config.setPeerVerifyMode(QSslSocket::VerifyNone);
	config.setProtocol(protocol);
	networkRequest.setSslConfiguration(config);

	return networkRequest;
}

QGSNetworkAccessManager & QGSNetworkAccessManager::getGlobalInstance()
{
	static QGSNetworkAccessManager instance;
	return instance;
}
