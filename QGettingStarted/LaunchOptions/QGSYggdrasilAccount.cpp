#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QEventLoop>
#include <QTimer>

#include "QGSYggdrasilAccount.h"
#include "../Util/QGSUuidGenerator.h"
#include "../Util/QGSExceptionAuthentication.h"

static const QString AuthServerUrl("https://authserver.mojang.com/authenticate");

QGSYggdrasilAccount::QGSYggdrasilAccount(QObject * parent) :QGSIAccount(parent)
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
	QGSNetworkAccessManager networkAccessManager;
	const int timeOutms(30000);
	QTimer *timer(nullptr);
	QEventLoop eventLoop;

	agent.insert("name", "Minecraft");
	agent.insert("version", 1);
	jsonObject.insert("agent", agent);

	if (userName.isEmpty())
	{
		throw QGSExceptionAuthentication("Username is empty!", "Username is empty!", "Username is empty!");
	}
	jsonObject.insert("username", userName);
	if (password.isEmpty())
	{
		throw QGSExceptionAuthentication("Password is empty!", "Password is empty!", "Password is empty!");
	}
	jsonObject.insert("password", password);
	if (clientToken.isEmpty())
	{
		clientToken = QGSUuidGenerator::getInstance().generateUuid(userName);
	}
	jsonObject.insert("clientToken", clientToken);
	jsonObject.insert("requestUser", true);

	jsonDocument.setObject(jsonObject);
	auto && byteArrayRequestData(jsonDocument.toJson());
	auto && request(QGSNetworkAccessManager::generateHttpsNetworkRequest());
	request.setUrl(AuthServerUrl);
	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
	request.setHeader(QNetworkRequest::ContentLengthHeader, byteArrayRequestData.length());
	
	if (timeOutms > 0)
	{
		timer = new QTimer(this);

		QObject::connect(timer, &QTimer::timeout, &eventLoop, &QEventLoop::quit);
		timer->setSingleShot(true);
	}

	networkAccessManager.setProxy(proxy);
	auto * reply(networkAccessManager.post(request, byteArrayRequestData));

	timer->start(timeOutms);
	if (reply)
	{
		QObject::connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
		QObject::connect(reply, static_cast<void (QNetworkReply::*)(QNetworkReply::NetworkError)>(&QNetworkReply::error), &eventLoop, &QEventLoop::quit);
		QObject::connect(reply, static_cast<void (QNetworkReply::*)(QNetworkReply::NetworkError)>(&QNetworkReply::error), [=](QNetworkReply::NetworkError code)
		{
			if (reply)
			{
				reply->deleteLater();
			}

			throw QGSExceptionAuthentication("Network error!",reply->errorString(),"Network error!");
		});
	}
	eventLoop.exec();

	auto && replyData(reply->readAll());
	reply->deleteLater();
	jsonDocument = QJsonDocument::fromJson(replyData);
	jsonObject = jsonDocument.object();

	if (jsonObject.contains("error"))
	{
		throw QGSExceptionAuthentication(jsonObject.contains("error") ? jsonObject.value("error").toString() : "Unknown error!",
			jsonObject.contains("errorMessage") ? jsonObject.value("errorMessage").toString() : "Unknown error message!",
			jsonObject.contains("cause") ? jsonObject.value("cause").toString() : "Unknown cause!"
		);
	}

	auto && accessToken(jsonObject.value("accessToken").toString());

	clientToken = jsonObject.value("clientToken").toString();

	auto && selectedProfileObject(jsonObject.value("selectedProfile").toObject());
	QGSAuthInfo::QGSProfile selectedProfile(selectedProfileObject.value("id").toString(),
		selectedProfileObject.value("name").toString(),
		selectedProfileObject.value("legacy").toBool());

	QString twitchAccessToken("{}");
	if (jsonObject.contains("user"))
	{
		auto && userObject(jsonObject.value("user").toObject());
		if (userObject.contains("properties"))
		{
			auto && propertyArray(userObject.value("properties").toArray());
            for (const auto & propertyValueRef : propertyArray)
			{
				auto && propertyObject(propertyValueRef.toObject());

				if (propertyObject.value("name").toString() == "twitch_access_token")
				{
					twitchAccessToken = QString("{\"twitch_access_token\": [\"%1\"]}").arg(propertyObject.value("value").toString());
				}
			}
		}
	}

	return QGSAuthInfo(accessToken,clientToken,UserType::Mojang,selectedProfile,twitchAccessToken);
}
