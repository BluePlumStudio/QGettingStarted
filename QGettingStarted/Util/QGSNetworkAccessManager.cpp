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

/*
QGSNetworkAccessManager & QGSNetworkAccessManager::setProxy(QNetworkProxy proxy)
{
	mManager->setProxy(proxy);
	return *this;
}

QNetworkReply * QGSNetworkAccessManager::get(const QNetworkRequest & request)
{
	return mManager->get(request);
}

QNetworkReply * QGSNetworkAccessManager::post(const QNetworkRequest & request, QIODevice * data)
{
	return mManager->post(request, data);
}

QNetworkReply * QGSNetworkAccessManager::post(const QNetworkRequest & request, const QByteArray & data)
{
	return mManager->post(request, data);
}

QNetworkReply * QGSNetworkAccessManager::post(const QNetworkRequest & request, QHttpMultiPart * multiPart)
{
	return mManager->post(request, multiPart);
}

QNetworkProxy QGSNetworkAccessManager::proxy() const
{
	return mManager->proxy();
}

void QGSNetworkAccessManager::connectToHost(const QString & hostName, quint16 port)
{
	mManager->connectToHost(hostName, port);
}

void QGSNetworkAccessManager::connectToHostEncrypted(const QString & hostName, quint16 port, const QSslConfiguration & sslConfiguration)
{
	mManager->connectToHostEncrypted(hostName, port, sslConfiguration);
}
*/

QGSNetworkAccessManager & QGSNetworkAccessManager::getGlobalInstance()
{
	static QGSNetworkAccessManager instance;
	return instance;
}
