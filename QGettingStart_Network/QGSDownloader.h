#pragma once

#include "../QGettingStart_Util/Exception.h"

#include <QObject>
#include <QFile>
#include <QNetworkAccessManager>
#include <QNetworkConfiguration>
#include <QNetworkReply>
#include <QNetworkRequest>

class QGSDownloader : public QObject
{
public:
	Q_OBJECT
public:
	/*请求错误*/
	struct ReplyError
	{
	public:
		ReplyError(QString errorMessage = "", uint errorCode = 0) :
			mErrorMessage(errorMessage), mErrorCode(errorCode)
		{

		}

		~ReplyError()
		{

		}

	public:
		QString mErrorMessage;
		uint mErrorCode;
	};
	/*下载进程*/
	struct DownloadProgress
	{
	public:
		DownloadProgress(qint64 bytesReceived = 0, qint64 bytesTotal = -1, int index = 0) :
			mBytesReceived(bytesReceived), mBytesTotal(bytesTotal), mIndex(index)
		{

		}

		~DownloadProgress()
		{

		}
	public:
		qint64 mBytesReceived;
		qint64 mBytesTotal;
		int mIndex;
	};

public:
	explicit QGSDownloader(int index, QObject *parent = nullptr);
	QGSDownloader(const QGSDownloader &) Q_DECL_EQ_DELETE;
	QGSDownloader & operator =(QGSDownloader rhs)Q_DECL_EQ_DELETE;

	~QGSDownloader();

signals:
	/*下载完成*/
	void downloadFinished();
	/*下载错误*/
	void error(ReplyError replyError);
	/*下载进程*/
	void downloadProgress(DownloadProgress downloadProgress);

public:
	void finished();
	void downloadProgress(qint64 bytesReceived, qint64 bytesTotal);

private:
	/*开始下载*/
	bool startDownload(const QUrl & URL, QFile *file, qint64 startPoint = 0, qint64 endPoint = -1);

private:
	class Private;
	friend class Private;
	friend class QGSNetwork;

	Private * d;
};

