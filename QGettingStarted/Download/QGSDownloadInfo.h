#pragma once

#include "../Util/QGSNetworkAccessManager.h"
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