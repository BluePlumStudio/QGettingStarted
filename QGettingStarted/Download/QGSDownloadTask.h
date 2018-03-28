#pragma once

#include <QObject>
#include <QFile>
#include <QSharedPointer>
#include <QThread>
#include <QEventLoop>
#include <QRunnable>
#include <QMutex>

#include "../Util/QGSNetwork.h"
#include "../GameVersion/QGSDownloads.h"
#include "../Util/QGSTask.h"

class QGSDownloadInfo :public QGSIDownload
{
public:
	QGSDownloadInfo(const QUrl & url = QUrl(), const QString & path = "", const QString & SHA1 = "");

	QGSDownloadInfo(const QGSDownloadInfo & right) = default;

	QGSDownloadInfo(QGSDownloadInfo && right) = default;

	QGSDownloadInfo & operator=(const QGSDownloadInfo & right) = default;

	QGSDownloadInfo & operator=(QGSDownloadInfo && right) = default;

	virtual ~QGSDownloadInfo();

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

public:
	QGSDownloadTask(QFile * targetFile, const QGSDownloadInfo & downloadInfo, const QNetworkProxy & proxy = QNetworkProxy::NoProxy, QObject *parent = nullptr);

	QGSDownloadTask(const QGSDownloadTask & right) = delete;

	QGSDownloadTask(QGSDownloadTask && right) = delete;

	QGSDownloadTask & operator=(const QGSDownloadTask & right) = delete;

	QGSDownloadTask & operator=(QGSDownloadTask && right) = delete;

	virtual ~QGSDownloadTask();

	QFile * getTargetFile();

	State getState();

	QGSDownloadInfo getDownloadInfo();

	static QString generateRandomFileName();
protected:
	virtual void templateStart(QGSTask * task);
	virtual void templateStop(QGSTask * task);
	virtual void templateCancel(QGSTask * task);

	virtual void downloadTemplateFinished();
	virtual void downloadTemplateDownloadProgress(qint64 bytesReceived, qint64 bytesTotal);
	virtual void downloadTemplateError(QNetworkReply::NetworkError error);
	virtual void downloadTemplateSslErrors(const QList<QSslError> &errors);
	virtual void downloadTemplateRedirected(const QUrl &url);
private slots:
	void slotFinished();
	void slotDownloadProgress(qint64 bytesReceived, qint64 bytesTotal);
	void slotError(QNetworkReply::NetworkError error);
	void slotSslErrors(const QList<QSslError> &errors);
	void slotRedirected(const QUrl &url);
signals:
	void downloadProgress(qint64 bytesReceived, qint64 bytesTotal, QGSTask * task);
	void downloadError(QGSNetworkError error, QGSTask * task);
	void sslErrors(const QList<QSslError> &errors, QGSTask * task);
protected:
	QFile * mTargetFilePtr;
	QGSDownloadInfo mDownloadInfo;
	QNetworkReply * mReply;
	QNetworkProxy mProxy;
	State mState;
	bool mDelete;
	qint64 mBytesReceived;

	QGSNetwork * mNetworkPtr;
};
