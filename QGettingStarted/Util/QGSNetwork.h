#pragma once

#include <QObject>
#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

namespace Network
{
	static const QString YggdrasilAuthServerUrl{ "https://authserver.mojang.com/authenticate" };
}

class QGSNetwork :public QObject
{
	Q_OBJECT
public:
	static QGSNetwork & getInstance();

	QNetworkAccessManager * getManager();

	QGSNetwork(const QGSNetwork & right) = delete;

	QGSNetwork(QGSNetwork && right) = delete;

	QGSNetwork & operator=(const QGSNetwork & right) = delete;

	QGSNetwork & operator=(QGSNetwork && right) = delete;

	~QGSNetwork();

	static QNetworkRequest generateNetworkRequest();

	static QNetworkRequest generateNetworkRequestWithSSL(QSsl::SslProtocol protocol = QSsl::SslProtocol::TlsV1_2);

	static QUrl getRedirectURL(const QUrl & url);
private:
	QGSNetwork(QObject * parent = nullptr);
private:
	QNetworkAccessManager * mManager;
};

