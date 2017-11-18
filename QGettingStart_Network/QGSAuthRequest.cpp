#include "QGSAuthRequest.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

class QGSAuthRequest::Private
{
public:
	Private() :mRequest(new QNetworkRequest)
	{
		if (!mRequest)
		{
			throw ExceptionBadAlloc();
		}

		QSslConfiguration config = QSslConfiguration::defaultConfiguration();
		config.setPeerVerifyMode(QSslSocket::VerifyNone);
		config.setProtocol(QSsl::TlsV1_2);
		mRequest->setSslConfiguration(config);

		mRequest->setUrl(QUrl("https://authserver.mojang.com/authenticate"));

		mRequest->setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

		mChanged = false;
		mLength = 0;
	}

	~Private()
	{
		if (mRequest)
		{
			delete mRequest;
		}
		mRequest = nullptr;
	}

public:
	QNetworkRequest * mRequest;
	RequestData mRequestData;
	bool mChanged;
	int mLength;
};

/**/

QGSAuthRequest::QGSAuthRequest(QObject * parent) :QObject(parent), d(new QGSAuthRequest::Private)
{

}

void QGSAuthRequest::setRequestData(RequestData & requestData)
{
	d->mChanged = true;
	d->mRequestData = requestData;
}

QGSAuthRequest::RequestData QGSAuthRequest::getRequestData()const
{
	return d->mRequestData;
}

QJsonObject QGSAuthRequest::getJsonObject()const
{
	QJsonObject jsonObject;
	QJsonObject agent;

	agent.insert("name", d->mRequestData.agent.mName);
	agent.insert("version", d->mRequestData.agent.mVersion);
	jsonObject.insert("agent", agent);
	jsonObject.insert("username", d->mRequestData.mUserName);
	jsonObject.insert("password", d->mRequestData.mPassword);
	jsonObject.insert("clientToken", d->mRequestData.mClientToken);

	return jsonObject;
}

QNetworkRequest * QGSAuthRequest::getNetworkRequest()const
{
	if (d->mRequest)
	{
		if (d->mChanged)
		{
			QJsonDocument jsonDocument;
			jsonDocument.setObject(getJsonObject());
			d->mLength = jsonDocument.toJson().length();
			d->mChanged = false;
		}

		d->mRequest->setHeader(QNetworkRequest::ContentLengthHeader, d->mLength);
	}
	return d->mRequest;
}

QByteArray QGSAuthRequest::getRequestMetaData()const
{
	QJsonDocument jsonDocument;
	jsonDocument.setObject(getJsonObject());

	return jsonDocument.toJson();
}

QGSAuthRequest::~QGSAuthRequest()
{
	if (d)
	{
		delete d;
	}
	d = nullptr;
}
