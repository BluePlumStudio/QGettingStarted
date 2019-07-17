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

class QGSNetworkError
{
public:
	QGSNetworkError(const QNetworkReply::NetworkError code = QNetworkReply::NetworkError::NoError, const QString & errorString = "");

	QGSNetworkError(const QGSNetworkError & right) = default;

	QGSNetworkError(QGSNetworkError && right) = default;

	QGSNetworkError & operator=(const QGSNetworkError & right) = default;

	QGSNetworkError & operator=(QGSNetworkError && right) = default;

	~QGSNetworkError();

	QNetworkReply::NetworkError getCode()const;

	QString getErrorString()const;

private:
	QNetworkReply::NetworkError mCode;
	QString mErrorString;
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

	static QNetworkRequest generateHttpsNetworkRequest(QSsl::SslProtocol protocol = QSsl::SslProtocol::TlsV1_0OrLater);
public:
	static const int DefaultTimeout;
};

