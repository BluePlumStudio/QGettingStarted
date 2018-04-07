#pragma once

#include <QMutex>

#include "QGSDownloader.h"

namespace DownloadTask
{
	const int DEFAULT_CONNECTION_COUNT(16);
}

enum class DownloadState
{
	Start,
	Stop
};

class QGSDownloadTask : public QGSTask
{
	Q_OBJECT

public:
	QGSDownloadTask(int connectionCount = DownloadTask::DEFAULT_CONNECTION_COUNT, const QNetworkProxy & proxy = QNetworkProxy::NoProxy, QObject *parent = nullptr);

	QGSDownloadTask(QFile * targetFile, const QGSDownloadInfo & downloadInfo, int connectionCount = DownloadTask::DEFAULT_CONNECTION_COUNT, const QNetworkProxy & proxy = QNetworkProxy::NoProxy, QObject *parent = nullptr);

	QGSDownloadTask(const QGSDownloadTask & right) = delete;

	QGSDownloadTask(QGSDownloadTask && right) = delete;

	QGSDownloadTask & operator=(const QGSDownloadTask & right) = delete;

	QGSDownloadTask & operator=(QGSDownloadTask && right) = delete;

	virtual ~QGSDownloadTask();

	QGSDownloadTask & setTargetFile(QFile * targetFile);

	QGSDownloadTask & setDownloadInfo(const QGSDownloadInfo & downloadInfo);

	QFile * getTargetFile();

	DownloadState getState();

	QGSDownloadInfo getDownloadInfo();

	static QString generateRandomFileName();

	static void setLargeFileSize(const quint64 bytes);

	static void setSmallFileSize(const quint64 bytes);
signals:
	void downloadProgress(qint64 bytesReceived, qint64 bytesTotal, QGSTask * task);
	void downloadError(QGSNetworkError error, QGSTask * task);
	void sslErrors(const QList<QSslError> &errors, QGSTask * task);
protected slots:
	virtual void templateStart(QGSTask * task);
	virtual void templateStop(QGSTask * task);
	virtual void templateCancel(QGSTask * task);

	virtual void downloadTemplateFinished();
	virtual void downloadTemplateDownloadProgress(qint64 bytesNewlyReceived, qint64 bytesReceived, qint64 bytesTotal);
	virtual void downloadTemplateError(QGSNetworkError error);
	virtual void downloadTemplateSslErrors(const QList<QSslError> &errors);
	virtual void downloadTemplateRedirected(const QUrl &url);
private slots:
	void slotFinished(QGSDownloader * downloader);
	void slotDownloadProgress(qint64 bytesNewlyReceived, qint64 bytesReceived, qint64 bytesTotal, QGSDownloader * downloader);
	void slotDownloadError(QGSNetworkError error, QGSDownloader * downloader);
	void slotSslErrors(const QList<QSslError> &errors, QGSDownloader * downloader);
	void slotRedirected(const QUrl &url, QGSDownloader * downloader);
private:
	quint64 getFileSize();
	void cancelTask();
protected:
	QMutex mMutex;
	QFile * mTargetFilePtr;
	QGSDownloadInfo mDownloadInfo;
	int mConnectionCount;
	QNetworkProxy mProxy;
	DownloadState mState;
	qint64 mBytesReceived;
	qint64 mBytesTotal;

	QList<QGSDownloader *> mDownloaderList;

	QGSNetworkAccessManager * mNetworkAccessManagerPtr;

	static quint64 mLargeFileSize;
	static quint64 mSmallFileSize;
};
