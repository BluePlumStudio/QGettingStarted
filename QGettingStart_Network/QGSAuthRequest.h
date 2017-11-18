#pragma once

#include "../QGettingStart_Util/Exception.h"

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkConfiguration>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonObject>

class QGSAuthRequest : public QObject
{
public:
	Q_OBJECT
public:

	/*«Î«Ûƒ⁄»›*/
	struct RequestData
	{
	public:
		RequestData(QString userName = "", QString password = "", QString clientToken = "") :
			mUserName(userName), mPassword(password), mClientToken(clientToken)
		{
			agent.mName = "Minecraft";
			agent.mVersion = 1;
		}

		~RequestData()
		{

		}
	public:
		struct
		{
			QString mName;
			int mVersion;
		}agent;

		QString mUserName;
		QString mPassword;
		QString mClientToken;
	};

public:
	explicit QGSAuthRequest(QObject *parent = nullptr);
	QGSAuthRequest(const QGSAuthRequest &) Q_DECL_EQ_DELETE;
	QGSAuthRequest & operator =(QGSAuthRequest rhs)Q_DECL_EQ_DELETE;

	void setRequestData(RequestData & requestData);
	RequestData getRequestData()const;

	~QGSAuthRequest();
private:
	QJsonObject getJsonObject()const;
	QNetworkRequest * getNetworkRequest()const;
	QByteArray getRequestMetaData()const;
private:
	class Private;
	friend class Private;
	friend class QGSNetwork;

	Private * d;
};

