#pragma once

#include <QObject>
#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkProxy>

namespace Network
{
	static const int DefaultTimeout = 300000;
}

class QGSNetwork :public QObject
{
	Q_OBJECT
public:
	static QGSNetwork & getInstance();

	//QNetworkAccessManager * getManager();

	QGSNetwork(const QGSNetwork & right) = delete;

	QGSNetwork(QGSNetwork && right) = delete;

	QGSNetwork & operator=(const QGSNetwork & right) = delete;

	QGSNetwork & operator=(QGSNetwork && right) = delete;

	~QGSNetwork();

	static QNetworkRequest generateNetworkRequest();

	static QNetworkRequest generateNetworkRequestWithSSL(QSsl::SslProtocol protocol = QSsl::SslProtocol::TlsV1_2);

	QGSNetwork & setProxy(QNetworkProxy proxy = QNetworkProxy::NoProxy);

	QNetworkReply * get(const QNetworkRequest &request);

	QNetworkReply * post(const QNetworkRequest &request, QIODevice *data);

	QNetworkReply * post(const QNetworkRequest &request, const QByteArray &data);

	QNetworkReply * post(const QNetworkRequest &request, QHttpMultiPart *multiPart);

	QNetworkProxy proxy()const;
private:
	QGSNetwork(QObject * parent = nullptr);
private:
	QNetworkAccessManager * mManager;
};

