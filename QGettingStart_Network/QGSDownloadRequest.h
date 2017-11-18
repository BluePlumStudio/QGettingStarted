#pragma once

#include "../QGettingStart_Util/Exception.h"
#include "../QGettingStart/QGSUtil.h"

#include <QObject>
#include <QFile>
#include <QNetworkAccessManager>
#include <QNetworkConfiguration>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonObject>

class QGSDownloadRequest : public QObject
{
public:
	Q_OBJECT
public:
	struct  RequestData
	{
	public:
		RequestData(QString URL = "", QString path = "", uint threadCount = 1) :
			mURL(URL), mPath(path), mThreadCount(threadCount)
		{

		}

		~RequestData()
		{

		}

	public:
		QUrl mURL;
		QString mPath;
		uint mThreadCount;
	};

public:
	explicit QGSDownloadRequest(RequestData * requestData = nullptr, QObject *parent = nullptr);
	QGSDownloadRequest(const QGSDownloadRequest &) Q_DECL_EQ_DELETE;
	QGSDownloadRequest & operator =(QGSDownloadRequest rhs)Q_DECL_EQ_DELETE;

	void setRequestData(RequestData & requestData);
	RequestData getRequestData()const;

	~QGSDownloadRequest();

private:
	class Private;
	friend class Private;
	friend class QGSNetwork;

	Private * d;
};

