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

QGSYggdrasilAccount::QGSYggdrasilAccount(QObject * parent) :QGSIAccount(parent), mReply(nullptr), mNetworkAccessManager(nullptr)
{
}

QGSYggdrasilAccount::~QGSYggdrasilAccount()
{
}

void QGSYggdrasilAccount::authenticate(const QString & userName, const QString & password, QString clientToken, QNetworkProxy proxy)
{
	QJsonObject jsonObject;
	QJsonObject agent;
	QJsonDocument jsonDocument;

	agent.insert("name", "Minecraft");
	agent.insert("version", 1);
	jsonObject.insert("agent", agent);

	jsonObject.insert("username", userName);
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

	if (!mNetworkAccessManager)
	{
		mNetworkAccessManager = new QGSNetworkAccessManager;
	}
	mNetworkAccessManager->setProxy(proxy);
	mReply = mNetworkAccessManager->post(request, byteArrayRequestData);

	if (mReply)
	{
		QObject::connect(mReply, &QNetworkReply::finished, this, &QGSYggdrasilAccount::slotFinished);
		QObject::connect(mReply, static_cast<void (QNetworkReply::*)(QNetworkReply::NetworkError)>(&QNetworkReply::error), this, &QGSYggdrasilAccount::slotError);
	}
}

void QGSYggdrasilAccount::slotFinished()
{
	if (!mReply)
	{
		return;
	}

	QJsonObject jsonObject;
	QJsonObject agent;
	QJsonDocument jsonDocument;
	auto && replyData(mReply->readAll());

	mReply->deleteLater();
	mReply = nullptr;
	jsonDocument = QJsonDocument::fromJson(replyData);
	jsonObject = jsonDocument.object();

	auto && accessToken(jsonObject.value("accessToken").toString());

	auto && clientToken(jsonObject.value("clientToken").toString());

	auto && availableProfileArray(jsonObject.value("availableProfiles").toArray());
	QList<QGSAuthInfo::QGSProfile> availableProfiles;
    for (const auto & profileVal : availableProfileArray)
	{
		auto && profileObject(profileVal.toObject());

		availableProfiles.push_back(QGSAuthInfo::QGSProfile(profileObject.value("id").toString(),
			profileObject.value("name").toString(),
			profileObject.value("legacy").toBool()));
	}

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

	emit finished(QGSAuthInfo(accessToken, clientToken, UserType::Mojang, selectedProfile, availableProfiles, twitchAccessToken));
}

void QGSYggdrasilAccount::slotError(QNetworkReply::NetworkError code)
{
	QJsonObject jsonObject;
	QJsonDocument jsonDocument;
	QString errorString(mReply->errorString());
	auto && replyData(mReply->readAll());
	jsonDocument = QJsonDocument::fromJson(replyData);
	jsonObject = jsonDocument.object();

	if (mReply)
	{
		mReply->deleteLater();
		mReply = nullptr;
	}

	emit error(QGSNetworkError(code, errorString));
}
