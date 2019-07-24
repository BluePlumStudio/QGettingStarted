#include "QGSDownloadInfo.h"

QGSDownloadInfo::QGSDownloadInfo(const QUrl & url, const QString & path, const QString & SHA1)
	:QGSDownloadBase(-1, SHA1, path, url)
{
	if (!QMetaType::isRegistered(QMetaType::type("QGSDownloadInfo")))
	{
		qRegisterMetaType<QGSDownloadInfo>("QGSDownloadInfo");
	}
}

QGSDownloadInfo::~QGSDownloadInfo()
{
}
