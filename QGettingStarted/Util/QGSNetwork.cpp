#include <QEventLoop>

#include "QGSNetwork.h"

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

}

QNetworkRequest QGSNetwork::generateNetworkRequest()
{
	return QNetworkRequest();
}

QNetworkRequest QGSNetwork::generateNetworkRequestWithSSL(QSsl::SslProtocol protocol)
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

QGSNetwork & QGSNetwork::getInstance()
{
	static QGSNetwork instance;
	return instance;
}
