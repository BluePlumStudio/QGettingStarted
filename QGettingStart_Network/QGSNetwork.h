#pragma once

#include "../QGettingStart_Util/Exception.h"

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkConfiguration>
#include <QNetworkReply>
#include <QNetworkRequest>

#include "QGSAuthReply.h"
#include "QGSAuthRequest.h"
#include "QGSDownloadRequest.h"
#include "QGSDownloader.h"
#include "QGSDownloadManager.h"

class QGSNetwork :public QObject
{
public:
	Q_OBJECT
public:
	static QGSNetwork * getInstance();

	QNetworkReply * get(const QNetworkRequest & request);
	QNetworkReply * post(const QNetworkRequest & request, const QByteArray & data);

	QGSDownloadManager * get(QGSDownloadRequest & request);
	QGSAuthReply * post(const QGSAuthRequest & request);

	qint64 getFileSize(QUrl URL);
	QUrl getRedirectURL(QUrl URL);

	~QGSNetwork();
private:
	explicit QGSNetwork(QObject *parent = nullptr);
	QGSNetwork(const QGSNetwork &) Q_DECL_EQ_DELETE;
	QGSNetwork & operator =(QGSNetwork rhs)Q_DECL_EQ_DELETE;

private:
	class Private;
	friend class Private;

	Private * d;
};

