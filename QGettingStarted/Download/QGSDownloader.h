#pragma once

#include <QObject>
#include <QFile>
#include <QSharedPointer>
#include <QThread>
#include <QNetworkProxy>
#include <QTimer>
#include <QEventLoop>

#include "Util/QGSNetwork.h"
#include "Version/Downloads.h"

class DownloadInfo:public Downloads::Download
{
public:
	DownloadInfo::DownloadInfo(const int size = -1, const QString & SHA1 = "", const QString & path = "", const QUrl & url = QUrl())
		:Download(size, SHA1, path, url)
	{
	}

	DownloadInfo(const DownloadInfo & right) = default;

	DownloadInfo(DownloadInfo && right) = default;

	DownloadInfo & operator=(const DownloadInfo & right) = default;

	DownloadInfo & operator=(DownloadInfo && right) = default;

	virtual DownloadInfo::~DownloadInfo()
	{
	}

private:

};

class QGSDownloader : public QObject
{
	Q_OBJECT
public:
	enum class State
	{
		Start,
		Stop
	};

	class Error
	{
	public:
		Error(const QNetworkReply::NetworkError code, const QString & message)
			:mCode(code), mMessage(message)
		{

		}

		~Error()
		{

		}

		QNetworkReply::NetworkError getCode()const
		{
			return mCode;
		}

		QString getMessage()const
		{
			return mMessage;
		}

	private:
		QNetworkReply::NetworkError mCode;
		QString mMessage;
	};


public:
	QGSDownloader(const DownloadInfo & downloadInfo, const QNetworkProxy & proxy = QNetworkProxy::NoProxy, QObject *parent = nullptr);

	QGSDownloader(const QGSDownloader & right) = delete;

	QGSDownloader(QGSDownloader && right) = delete;

	QGSDownloader & operator=(const QGSDownloader & right) = delete;

	QGSDownloader & operator=(QGSDownloader && right) = delete;

	virtual ~QGSDownloader();

	bool start();

	bool stop();

	bool cancel();

	QFile * generateFile()const;

	QFile & getFile();

	State getState()const;
private:
	void slotFinished();
	void slotDownloadProgress(qint64 bytesReceived, qint64 bytesTotal);
	void slotError(QNetworkReply::NetworkError code);
	void slotSslErrors(const QList<QSslError> &errors);
	void slotTimeout();
	void slotRedirected(const QUrl &url);

	QString generateRandomFileName();
signals:
	void downloadProgress(qint64 bytesReceived, qint64 bytesTotal);
	void finished();
	void error(Error error);
	void sslErrors(const QList<QSslError> &errors);
	void timeout();

private:
	QFile mFile;
	DownloadInfo mDownloadInfo;
	QNetworkReply * mReply;
	QNetworkProxy mProxy;
	State mState;
	bool mDelete;
	QEventLoop mEventLoop;
	QTimer mTimer;
	qint64 mBytesReceived;
};
