#include "QGSDownloadInfo.h"

QGSDownloadInfo::QGSDownloadInfo(const QUrl & url, const QString & path, const QString & SHA1)
	:QGSIDownload(-1, SHA1, path, url)
{

}

QGSDownloadInfo::~QGSDownloadInfo()
{
}
