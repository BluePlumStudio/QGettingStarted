#pragma once

#include <QObject>
#include <QFile>
#include <QSharedPointer>
#include <QThread>

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
	QGSDownloader(const DownloadInfo & downloadInfo, QObject *parent = nullptr);

	QGSDownloader(const QGSDownloader & right) = delete;

	QGSDownloader(QGSDownloader && right) = delete;

	QGSDownloader & operator=(const QGSDownloader & right) = delete;

	QGSDownloader & operator=(QGSDownloader && right) = delete;

	virtual ~QGSDownloader();

	bool start();

	QFile * generateFile()const;
private:
	void finishedSlot();
	void downloadProgressSlot(qint64 bytesReceived, qint64 bytesTotal);
signals:
	void downloadProgress(qint64 bytesReceived, qint64 bytesTotal);
	void finished();
private:
	QFile mFile;
	DownloadInfo mDownloadInfo;
	QNetworkReply * mReply;
};
