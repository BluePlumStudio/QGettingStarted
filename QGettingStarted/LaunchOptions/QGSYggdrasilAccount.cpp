#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QSslConfiguration>
#include <QSslSocket>
#include <QEventLoop>

#include "QGSYggdrasilAccount.h"
#include "Util/QGSUuidGenerator.h"
#include "Util/QGSExceptionAuthentication.h"

QGSYggdrasilAccount::QGSYggdrasilAccount()
{
}

QGSYggdrasilAccount::~QGSYggdrasilAccount()
{
}

AuthInfo QGSYggdrasilAccount::authenticate(const QString & userName, const QString & password, QString clientToken)
{
	QJsonObject jsonObject;
	QJsonObject agent;
	QJsonDocument jsonDocument;

	agent.insert("name", "Minecraft");
	agent.insert("version", 1);
	jsonObject.insert("agent", agent);

	if (userName.isEmpty())
	{
		throw QGSExceptionAuthentication{ "Username is empty!", "Username is empty!", "Username is empty!" };
	}
	jsonObject.insert("username", userName);
	if (password.isEmpty())
	{
		throw QGSExceptionAuthentication{ "Password is empty!", "Password is empty!", "Password is empty!" };
	}
	jsonObject.insert("password", password);
	if (clientToken.isEmpty())
	{
		clientToken = QGSUuidGenerator::getInstance().generateUuid(userName);
	}
	jsonObject.insert("clientToken", clientToken);
	jsonObject.insert("requestUser", true);

	jsonDocument.setObject(jsonObject);
	auto byteArrayRequestData{ jsonDocument.toJson() };
	QSharedPointer<QNetworkRequest>request{ QGSNetwork::generateNetworkRequestWithSSL() };
	request->setUrl(Network::YggdrasilAuthServerUrl);
	request->setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
	request->setHeader(QNetworkRequest::ContentLengthHeader, byteArrayRequestData.length());
	
	QEventLoop eventLoop;
	auto * reply = QGSNetwork::getInstance().getManager()->post(*request, byteArrayRequestData);
	QObject::connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
	eventLoop.exec();

	if (!reply->isFinished())
	{
		reply->deleteLater();
		throw QGSExceptionAuthentication{};
	}
	auto replyData = reply->readAll();
	reply->deleteLater();
	jsonDocument = QJsonDocument::fromJson(replyData);
	jsonObject = jsonDocument.object();

	if (jsonObject.contains("error"))
	{
		throw QGSExceptionAuthentication{ jsonObject.contains("error") ? jsonObject.value("error").toString() : "Unknown error!",
			jsonObject.contains("errorMessage") ? jsonObject.value("errorMessage").toString() : "Unknown error message!",
			jsonObject.contains("cause") ? jsonObject.value("cause").toString() : "Unknown cause!"
		};
	}
	auto accessToken{ jsonObject.value("accessToken").toString() };
	clientToken = jsonObject.value("clientToken").toString();
	auto selectedProfileObject{ jsonObject.value("selectedProfile").toObject() };
	AuthInfo::Profile selectedProfile{ selectedProfileObject.value("id").toString(),
		selectedProfileObject.value("name").toString(),
		selectedProfileObject.value("legacy").toBool() };
	QString twitchAccessToken{ "{}" };
	/*twitchAccessToken
	if (jsonObject.contains("user"))
	{
		auto userObject = jsonObject.value("user").toObject();
	}
	*/
	return AuthInfo{ accessToken,clientToken,UserType::MOJANG,selectedProfile,twitchAccessToken };
}
