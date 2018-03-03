#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QSslConfiguration>
#include <QSslSocket>
#include <QEventLoop>

#include "QGSYggdrasilAccount.h"
#include "Util/QGSUuidGenerator.h"

QGSYggdrasilAccount::QGSYggdrasilAccount()
{
}

QGSYggdrasilAccount::~QGSYggdrasilAccount()
{
}

AuthInfo QGSYggdrasilAccount::authenticate(const QString & userName, const QString & password, QString clientToken)
{
	QJsonObject payload;
	QJsonObject agent;
	QJsonDocument jsonDocument;

	agent.insert("name", "Minecraft");
	agent.insert("version", 1);
	payload.insert("agent", agent);

	if (userName.isEmpty())
	{

	}
	payload.insert("username", userName);
	if (password.isEmpty())
	{

	}
	payload.insert("password", password);
	if (clientToken.isEmpty())
	{
		clientToken = QGSUuidGenerator::getInstance().generateUuid(userName);
	}
	payload.insert("clientToken", clientToken);
	payload.insert("requestUser", true);

	jsonDocument.setObject(payload);
	auto byteArrayRequestData{ jsonDocument.toJson() };
	QSharedPointer<QNetworkRequest>request{ generateNetworkRequest() };
	request->setHeader(QNetworkRequest::ContentLengthHeader, byteArrayRequestData.length());
	
	QEventLoop eventLoop;
	auto * reply = QGSNetwork::getInstance().getManager()->post(*request, byteArrayRequestData);
	QObject::connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
	eventLoop.exec();
	if (!reply->isFinished())
	{

	}
	auto replyData = reply->readAll();
	reply->deleteLater();

	return AuthInfo();
}

QNetworkRequest * QGSYggdrasilAccount::generateNetworkRequest()
{
	QNetworkRequest * networkRequest{ new QNetworkRequest };

	QSslConfiguration config = QSslConfiguration::defaultConfiguration();
	config.setPeerVerifyMode(QSslSocket::VerifyNone);
	config.setProtocol(QSsl::TlsV1_2);
	networkRequest->setSslConfiguration(config);

	networkRequest->setUrl(Network::YggdrasilAuthServerUrl);
	networkRequest->setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

	return networkRequest;
}
