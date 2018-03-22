#pragma once

#include <QObject>
#include <QFile>
#include <QSharedPointer>
#include <QThread>
#include <QNetworkProxy>
#include <QTimer>
#include <QEventLoop>
#include <QRunnable>

#include "../Util/QGSNetwork.h"
#include "../GameVersion/Downloads.h"
#include "../Util/QGSTask.h"

class DownloadInfo:public Downloads::Download
{
public:
	DownloadInfo::DownloadInfo(const QUrl & url = QUrl(), const QString & path = "", const QString & SHA1 = "")
		:Download(-1, SHA1, path, url)
	{
		qRegisterMetaType<DownloadInfo>("DownloadInfo");
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

class QGSDownloadTask : public QGSTask
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
			:mCode(code), mMessage(message);

		~Error();

		QNetworkReply::NetworkError getCode()const;

		QString getMessage()const;

	private:
		QNetworkReply::NetworkError mCode;
		QString mMessage;
	};


public:
	QGSDownloadTask(QFile * targetFile, const DownloadInfo & downloadInfo, const QNetworkProxy & proxy = QNetworkProxy::NoProxy, QObject *parent = nullptr);

	QGSDownloadTask(const QGSDownloadTask & right) = delete;

	QGSDownloadTask(QGSDownloadTask && right) = delete;

	QGSDownloadTask & operator=(const QGSDownloadTask & right) = delete;

	QGSDownloadTask & operator=(QGSDownloadTask && right) = delete;

	virtual ~QGSDownloadTask();
	/*����*/
	bool start();

	bool stop();

	bool cancel();
	/**/
	QGSDownloadTask & setTimeout(const int msec);

	int getTimeout()const;

	QFile * getTargetFile();

	State getState()const;

	static QString generateRandomFileName();
protected:
	/*ģ�����*/
	virtual void templateStart(QGSTask * task);
	virtual void templateStop(QGSTask * task);
	virtual void templateCancel(QGSTask * task);
private slots:
	void slotFinished();
	void slotDownloadProgress(qint64 bytesReceived, qint64 bytesTotal);
	void slotError(QNetworkReply::NetworkError code);
	void slotSslErrors(const QList<QSslError> &errors);
	void slotTimeout();
	void slotRedirected(const QUrl &url);
signals:
	void downloadProgress(qint64 bytesReceived, qint64 bytesTotal, const DownloadInfo downloadInfo);
	void finished(const DownloadInfo downloadInfo);
	void error(Error error, const DownloadInfo downloadInfo);
	void sslErrors(const QList<QSslError> &errors, const DownloadInfo downloadInfo);
	void timeout(const DownloadInfo downloadInfo);

protected:
	QFile * mTargetFilePtr;
	DownloadInfo mDownloadInfo;
	QNetworkReply * mReply;
	QNetworkProxy mProxy;
	State mState;
	bool mDelete;
	QTimer mTimer;
	qint64 mBytesReceived;
};
