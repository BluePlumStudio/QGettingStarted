#pragma once

#include <QFile>

#include "QGSDownloadInfo.h"
#include "../Util/QGSNetworkHelper.h"

class QGSDownloader : public QObject
{
	Q_OBJECT

public:
	QGSDownloader(QFile * targetFile, 
		const QGSDownloadInfo & downloadInfo,
		QGSNetworkHelper * networkAccessManagerPtr, 
		qint64 bytesBegin, 
		qint64 bytesEnd, 
		const QNetworkProxy & proxy = QNetworkProxy::NoProxy, 
		QObject *parent = nullptr);

	QGSDownloader(const QGSDownloader & right) = delete;

	QGSDownloader(QGSDownloader && right) = delete;

	QGSDownloader & operator=(const QGSDownloader & right) = delete;

	QGSDownloader & operator=(QGSDownloader && right) = delete;

	virtual ~QGSDownloader();

	QNetworkReply * getNetworkReply()const;
signals:
	void started(QGSDownloader * downloader);
	void finished(QGSDownloader * downloader);
	void stoped(QGSDownloader * downloader);
	void canceled(QGSDownloader * downloader);
	void downloadProgress(qint64 bytesNewlyReceived, qint64 bytesReceived, qint64 bytesTotal, QGSDownloader * downloader);
	void downloadError(QGSNetworkError error, QGSDownloader * downloader);
	void sslErrors(const QList<QSslError> &errors, QGSDownloader * downloader);
	void redirected(const QUrl &url, QGSDownloader * downloader);
public slots:
	void start();
	void stop();
	void cancel();
private:
	void slotFinished();
	void slotDownloadProgress(qint64 bytesReceived, qint64 bytesTotal);
	void slotDownloadError(QNetworkReply::NetworkError error);
	void slotSslErrors(const QList<QSslError> &errors);
	void slotRedirected(const QUrl &url);
private:
	bool get();
private:
	QFile * mTargetFilePtr;
	QGSDownloadInfo mDownloadInfo;
	QNetworkReply * mReply;
	QNetworkProxy mProxy;
	qint64 mBytesReceived;
	qint64 mBytesBegin;
	qint64 mBytesEnd;
	QGSNetworkHelper * mNetworkHelperPtr;
};
