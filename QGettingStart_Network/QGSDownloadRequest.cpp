#include "QGSDownloadRequest.h"

class QGSDownloadRequest::Private
{
public:
	Private() :mRequest(new QNetworkRequest)//, mFile(new QFile)
	{
		if (!mRequest)
		{
			throw ExceptionBadAlloc();
		}

		QSslConfiguration config = QSslConfiguration::defaultConfiguration();
		config.setPeerVerifyMode(QSslSocket::VerifyNone);
		config.setProtocol(QSsl::TlsV1_2);
		mRequest->setSslConfiguration(config);

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
	RequestData mRequestData;
	QNetworkRequest * mRequest;
};

QGSDownloadRequest::QGSDownloadRequest(RequestData * requestData, QObject *parent) :QObject(parent), d(new QGSDownloadRequest::Private)
{
	if (!d)
	{
		throw ExceptionBadAlloc();
	}

	d->mRequestData = *requestData;
	d->mRequest->setUrl(d->mRequestData.mURL);
}

void QGSDownloadRequest::setRequestData(RequestData & requestData)
{
	d->mRequestData = requestData;
	d->mRequest->setUrl(d->mRequestData.mURL);
}

QGSDownloadRequest::RequestData QGSDownloadRequest::getRequestData()const
{
	return d->mRequestData;
}

QGSDownloadRequest::~QGSDownloadRequest()
{
	if (d)
	{
		delete d;
	}

	d = nullptr;
}
