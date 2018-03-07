#include "QGSNetwork.h"

QGSNetwork::QGSNetwork(QObject * parent) :QObject(parent), mManager(new QNetworkAccessManager)
{
}

QNetworkAccessManager * QGSNetwork::getManager()
{
	return mManager;
}

QGSNetwork::~QGSNetwork()
{
}

QNetworkRequest * QGSNetwork::generateNetworkRequest()
{
	return new QNetworkRequest;
}

QNetworkRequest * QGSNetwork::generateNetworkRequestWithSSL()
{
	QNetworkRequest * networkRequest{ new QNetworkRequest };

	QSslConfiguration config = QSslConfiguration::defaultConfiguration();
	config.setPeerVerifyMode(QSslSocket::VerifyNone);
	config.setProtocol(QSsl::TlsV1_2);
	networkRequest->setSslConfiguration(config);

	return networkRequest;
}

QGSNetwork & QGSNetwork::getInstance()
{
	static QGSNetwork instance;
	return instance;
}
