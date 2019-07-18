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

class QGSNetworkHelper :public QObject
{
	Q_OBJECT

public:
	static QGSNetworkHelper & getGlobalInstance();

	QGSNetworkHelper(QObject * parent = nullptr);

	QGSNetworkHelper(const QGSNetworkHelper & right) = delete;

	QGSNetworkHelper(QGSNetworkHelper && right) = delete;

	QGSNetworkHelper & operator=(const QGSNetworkHelper & right) = delete;

	QGSNetworkHelper & operator=(QGSNetworkHelper && right) = delete;

	~QGSNetworkHelper();

	QNetworkAccessManager * getNetworkAccessManager();

	static QNetworkRequest generateNetworkRequest();

	static QNetworkRequest generateHttpsNetworkRequest(QSsl::SslProtocol protocol = QSsl::SslProtocol::TlsV1_0OrLater);
public:
	static const int DefaultTimeout;
private:
	QNetworkAccessManager * mNetworkHelperPtr;
};

