#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QSslConfiguration>
#include <QSslSocket>
#include <QEventLoop>
#include <QTimer>

#include "QGSYggdrasilAccount.h"
#include "Util/QGSUuidGenerator.h"
#include "Util/QGSExceptionAuthentication.h"

static const QString AuthServerUrl{ "https://authserver.mojang.com/authenticate" };

QGSYggdrasilAccount::QGSYggdrasilAccount()
{
}

QGSYggdrasilAccount::~QGSYggdrasilAccount()
{
}

QGSAuthInfo QGSYggdrasilAccount::authenticate(const QString & userName, const QString & password, QString clientToken, QNetworkProxy proxy)
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
	auto && byteArrayRequestData{ jsonDocument.toJson() };
	auto && request{ QGSNetwork::generateNetworkRequestWithSSL() };
	request.setUrl(AuthServerUrl);
	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
	request.setHeader(QNetworkRequest::ContentLengthHeader, byteArrayRequestData.length());
	
	QSharedPointer<QEventLoop> eventLoop{ new QEventLoop };
	auto * reply = QGSNetwork::getInstance().post(request, byteArrayRequestData);
	QObject::connect(reply, &QNetworkReply::finished, eventLoop.data(), &QEventLoop::quit);
	QTimer::singleShot(Network::DefaultTimeout, eventLoop.data(), [=]()
	{
		eventLoop->quit();
		throw QGSExceptionAuthentication{ "timeout!", "timeout", "timeout" };
	});
	eventLoop->exec();

	if (!reply->isFinished())
	{
		reply->deleteLater();
		throw QGSExceptionAuthentication();
	}
	auto && replyData = reply->readAll();
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

	auto && accessToken{ jsonObject.value("accessToken").toString() };

	clientToken = jsonObject.value("clientToken").toString();

	auto && selectedProfileObject{ jsonObject.value("selectedProfile").toObject() };
	QGSAuthInfo::Profile selectedProfile{ selectedProfileObject.value("id").toString(),
		selectedProfileObject.value("name").toString(),
		selectedProfileObject.value("legacy").toBool() };

	QString twitchAccessToken{ "{}" };
	if (jsonObject.contains("user"))
	{
		auto && userObject{ jsonObject.value("user").toObject() };
		if (userObject.contains("properties"))
		{
			auto && propertyArray{ userObject.value("properties").toArray() };
			for (auto & propertyValueRef : propertyArray)
			{
				auto && propertyObject{ propertyValueRef.toObject() };
				twitchAccessToken = propertyObject.value("name").toString();
				if (twitchAccessToken == "twitch_access_token")
				{
					twitchAccessToken = QString{ "{\"twitch_access_token\": [\"%1\"]}" }.arg(twitchAccessToken);
				}
			}
		}
	}

	return QGSAuthInfo{ accessToken,clientToken,UserType::Mojang,selectedProfile,twitchAccessToken };
}
