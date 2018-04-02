#pragma once

#include <QObject>
#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkProxy>
#include <QSslConfiguration>
#include <QSslSocket>
#include <QMetaType>

namespace Network
{
	static const int DefaultTimeout = 300000;
}

class QGSNetworkError
{
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

Q_DECLARE_METATYPE(QGSNetworkError)

class QGSNetworkAccessManager :public QNetworkAccessManager
{
	Q_OBJECT

public:
	static QGSNetworkAccessManager & getGlobalInstance();

	QGSNetworkAccessManager(QObject * parent = nullptr);

	QGSNetworkAccessManager(const QGSNetworkAccessManager & right) = delete;

	QGSNetworkAccessManager(QGSNetworkAccessManager && right) = delete;

	QGSNetworkAccessManager & operator=(const QGSNetworkAccessManager & right) = delete;

	QGSNetworkAccessManager & operator=(QGSNetworkAccessManager && right) = delete;

	~QGSNetworkAccessManager();

	static QNetworkRequest generateNetworkRequest();

	static QNetworkRequest generateHttpsNetworkRequest(QSsl::SslProtocol protocol = QSsl::SslProtocol::TlsV1SslV3);
	/*
	QGSNetworkAccessManager & setProxy(QNetworkProxy proxy = QNetworkProxy::NoProxy);

	QNetworkReply * get(const QNetworkRequest &request);

	QNetworkReply * post(const QNetworkRequest &request, QIODevice *data);

	QNetworkReply * post(const QNetworkRequest &request, const QByteArray &data);

	QNetworkReply * post(const QNetworkRequest &request, QHttpMultiPart *multiPart);

	QNetworkProxy proxy()const;	

	void connectToHost(const QString &hostName, quint16 port = 80);

	void connectToHostEncrypted(const QString &hostName, quint16 port = 443, const QSslConfiguration &sslConfiguration = QSslConfiguration::defaultConfiguration());
	*/
private:
	//QNetworkAccessManager * mManager;
};

