#pragma once

#include <QObject>
#include <QString>
#ifdef Q_CC_MSVC
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkProxy>
#include <QSslConfiguration>
#include <QSslSocket>
#else
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkProxy>
#include <QtNetwork/QSslConfiguration>
#include <QtNetwork/QSslSocket>
#endif

namespace Network
{
	static const int DefaultTimeout = 300000;
}

class QGSNetworkError //:public QObject
{
	//Q_OBJECT
public:
	QGSNetworkError(const QNetworkReply::NetworkError code = QNetworkReply::NetworkError::NoError, const QString & message = "");

	QGSNetworkError(const QGSNetworkError & right);

	QGSNetworkError(QGSNetworkError && right) = default;

	QGSNetworkError & operator=(const QGSNetworkError & right) = default;

	QGSNetworkError & operator=(QGSNetworkError && right) = default;

	~QGSNetworkError();

	QNetworkReply::NetworkError getCode()const;

	QString getMessage()const;

private:
	QNetworkReply::NetworkError mCode;
	QString mMessage;
};

class QGSNetwork :public QObject
{
	Q_OBJECT

public:
	static QGSNetwork & getGlobalInstance();

	QGSNetwork(QObject * parent = nullptr);

	QGSNetwork(const QGSNetwork & right) = delete;

	QGSNetwork(QGSNetwork && right) = delete;

	QGSNetwork & operator=(const QGSNetwork & right) = delete;

	QGSNetwork & operator=(QGSNetwork && right) = delete;

	~QGSNetwork();

	static QNetworkRequest generateNetworkRequest();

	static QNetworkRequest generateNetworkRequestWithSsl(QSsl::SslProtocol protocol = QSsl::SslProtocol::TlsV1_0);

	QGSNetwork & setProxy(QNetworkProxy proxy = QNetworkProxy::NoProxy);

	QNetworkReply * get(const QNetworkRequest &request);

	QNetworkReply * post(const QNetworkRequest &request, QIODevice *data);

	QNetworkReply * post(const QNetworkRequest &request, const QByteArray &data);

	QNetworkReply * post(const QNetworkRequest &request, QHttpMultiPart *multiPart);

	QNetworkProxy proxy()const;	

	void connectToHost(const QString &hostName, quint16 port = 80);

	void connectToHostEncrypted(const QString &hostName, quint16 port = 443, const QSslConfiguration &sslConfiguration = QSslConfiguration::defaultConfiguration());
private:
	QNetworkAccessManager * mManager;
};

