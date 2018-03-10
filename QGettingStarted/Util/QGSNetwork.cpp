#include <QEventLoop>

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

QUrl QGSNetwork::getRedirectURL(const QUrl & url)
{
	QEventLoop eventLoop;
	auto newUrl{ url };

	QNetworkReply * reply = getInstance().getManager()->head(QNetworkRequest(newUrl));//获取重定向后的下载链接
	QObject::connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit, Qt::DirectConnection);
	eventLoop.exec();

	int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
	if (statusCode == 302 && reply->hasRawHeader("Location"))
	{
		QString location = reply->rawHeader("Location");
		newUrl.setPath(location);
	}

	return newUrl;
}

QGSNetwork & QGSNetwork::getInstance()
{
	static QGSNetwork instance;
	return instance;
}
