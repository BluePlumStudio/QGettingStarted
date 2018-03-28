#include <QEventLoop>
#include <QMetaType> 

#include "QGSNetwork.h"

QGSNetworkError::QGSNetworkError(const QNetworkReply::NetworkError code, const QString & message)
	:mCode(code), mMessage(message)
{
	qRegisterMetaType<QGSNetworkError>("QGSNetworkError");
}

QGSNetworkError::QGSNetworkError(const QGSNetworkError & right)
{

}

QGSNetworkError::~QGSNetworkError()
{

}

QNetworkReply::NetworkError QGSNetworkError::getCode()const
{
	return mCode;
}

QString QGSNetworkError::getMessage()const
{
	return mMessage;
}

/**/

QGSNetwork::QGSNetwork(QObject * parent) :QObject(parent), mManager(new QNetworkAccessManager)
{
}

/*
QNetworkAccessManager * QGSNetwork::getManager()
{
	return mManager;
}
*/

QGSNetwork::~QGSNetwork()
{
	if (mManager)
	{
		mManager->deleteLater();
	}
}

QNetworkRequest QGSNetwork::generateNetworkRequest()
{
	return QNetworkRequest();
}

QNetworkRequest QGSNetwork::generateNetworkRequestWithSsl(QSsl::SslProtocol protocol)
{
	QNetworkRequest networkRequest;

	QSslConfiguration config = QSslConfiguration::defaultConfiguration();
	config.setPeerVerifyMode(QSslSocket::VerifyNone);
	config.setProtocol(protocol);
	networkRequest.setSslConfiguration(config);

	return networkRequest;
}

QGSNetwork & QGSNetwork::setProxy(QNetworkProxy proxy)
{
	mManager->setProxy(proxy);
	return *this;
}

QNetworkReply * QGSNetwork::get(const QNetworkRequest & request)
{
	return mManager->get(request);
}

QNetworkReply * QGSNetwork::post(const QNetworkRequest & request, QIODevice * data)
{
	return mManager->post(request, data);
}

QNetworkReply * QGSNetwork::post(const QNetworkRequest & request, const QByteArray & data)
{
	return mManager->post(request, data);
}

QNetworkReply * QGSNetwork::post(const QNetworkRequest & request, QHttpMultiPart * multiPart)
{
	return mManager->post(request, multiPart);
}

QNetworkProxy QGSNetwork::proxy() const
{
	return mManager->proxy();
}

void QGSNetwork::connectToHost(const QString & hostName, quint16 port)
{
	mManager->connectToHost(hostName, port);
}

void QGSNetwork::connectToHostEncrypted(const QString & hostName, quint16 port, const QSslConfiguration & sslConfiguration)
{
	mManager->connectToHostEncrypted(hostName, port, sslConfiguration);
}

QGSNetwork & QGSNetwork::getGlobalInstance()
{
	static QGSNetwork instance;
	return instance;
}
