#pragma once

#include "../QGettingStart_Util/Exception.h"

#include <QNetworkAccessManager>
#include <QNetworkConfiguration>
#include <QNetworkReply>
#include <QNetworkRequest>

#include "QGSDownloadRequest.h"
#include "QGSDownloader.h"

class QGSDownloadManager :public QObject
{
public:
	Q_OBJECT
public:
	struct DownloadProgress
	{
	public:
		DownloadProgress(qint64 bytesReceived = 0, qint64 fileSize = -1, int finishedCount = 0, int index = 0, uint threadCount = 1) :
			mBytesReceived(bytesReceived), mFileSize(fileSize), mFinishedCount(finishedCount), mIndex(index), mThreadCount(threadCount)
		{

		}

		~DownloadProgress()
		{

		}
	public:
		qint64 mBytesReceived;
		qint64 mFileSize;
		int mFinishedCount;
		int mIndex;
		uint mThreadCount;
	};
public:
	explicit QGSDownloadManager(QObject *parent = nullptr);
	QGSDownloadManager(const QGSDownloadManager & ref)Q_DECL_EQ_DELETE;
	QGSDownloadManager & operator =(QGSDownloadManager rhs)Q_DECL_EQ_DELETE;

	~QGSDownloadManager();

private:
	void addDownloader(QGSDownloader * downloader);
	void setFile(QFile * file);
	void setFileSize(qint64 fileSize);
	void setThreadCount(int threadCount);

signals:
	void finished();
	void downloadProgress(DownloadProgress downloadProgress);
public:
	void subPartFinished();
	void downloadProgress(QGSDownloader::DownloadProgress progress);

private:
	class Private;
	friend class Private;
	friend class QGSNetwork;

	Private * d;
};

