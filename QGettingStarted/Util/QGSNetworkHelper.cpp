#include <QEventLoop>
#include <QMetaType> 

#include "QGSNetworkHelper.h"

QGSNetworkError::QGSNetworkError(const QNetworkReply::NetworkError code, const QString & errorString)
	:mCode(code), mErrorString(errorString)
{
	if (!QMetaType::isRegistered(QMetaType::type("QGSNetworkError")))
	{
		qRegisterMetaType<QGSNetworkError>("QGSNetworkError");
	}
}

QGSNetworkError::~QGSNetworkError()
{

}

QNetworkReply::NetworkError QGSNetworkError::getCode()const
{
	return mCode;
}

QString QGSNetworkError::getErrorString()const
{
	return mErrorString;
}

/**/

const int QGSNetworkHelper::DefaultTimeout = 300000;

QGSNetworkHelper::QGSNetworkHelper(QObject * parent) :QObject(parent), mNetworkAccessManager(new QNetworkAccessManager)
{
	if (!mNetworkAccessManager)
	{
		
	}
}

QGSNetworkHelper::~QGSNetworkHelper()
{
	if (mNetworkAccessManager)
	{
		mNetworkAccessManager->deleteLater();
		mNetworkAccessManager = nullptr;
	}
}

QNetworkAccessManager * QGSNetworkHelper::getNetworkAccessManager()
{
	return mNetworkAccessManager;
}

QNetworkRequest QGSNetworkHelper::generateNetworkRequest()
{
	return QNetworkRequest();
}

QNetworkRequest QGSNetworkHelper::generateHttpsNetworkRequest(QSsl::SslProtocol protocol)
{
	QNetworkRequest networkRequest;

	QSslConfiguration config = QSslConfiguration::defaultConfiguration();
	config.setPeerVerifyMode(QSslSocket::VerifyNone);
	config.setProtocol(protocol);
	networkRequest.setSslConfiguration(config);

	return networkRequest;
}

QGSNetworkHelper & QGSNetworkHelper::getGlobalInstance()
{
	static QGSNetworkHelper instance;
	return instance;
}
