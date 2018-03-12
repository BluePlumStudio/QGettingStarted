#pragma once

#include <QString>
#include <QUrl>
#include <QObject>
#include <QFileInfo>

#include "QGSDownloader.h"
#include "QGSIDownloadSource.h"
#include "QGSIDownloadSource.h"
#include "Version/Version.h"
#include "Launcher/QGSGameDirectory.h"

class QGSDownloadManager
{
public:
	QGSDownloadManager(QGSIDownloadSource * downloadSource);

	QGSDownloadManager(const QGSDownloadManager & right) = delete;

	QGSDownloadManager(QGSDownloadManager && right) = delete;

	QGSDownloadManager & operator=(const QGSDownloadManager & right) = delete;

	QGSDownloadManager & operator=(QGSDownloadManager && right) = delete;

	virtual ~QGSDownloadManager();
	
	QGSDownloader * generateVersionManifestDownloader(DownloadInfo & downloadInfo = DownloadInfo());

	QGSDownloader * generateLibraryDownloader(const Library & library, DownloadInfo & downloadInfo = DownloadInfo());

	QGSDownloader * generateVersionDownloader(Version & version, const QString & category, DownloadInfo & downloadInfo = DownloadInfo());

	QGSDownloader * generateForgeDownloader(const QString & mcversion, const QString & version, const QString & category, const QString & format, const QString & branch = "", DownloadInfo & downloadInfo = DownloadInfo());

	QGSDownloader * generateLiteLoaderDownloader(const QString & version, const QString & mcversion, DownloadInfo & downloadInfo = DownloadInfo());

	QGSDownloader * generateOptifineDownloader(const QString & mcversion, const QString & type, const QString & patch, DownloadInfo & downloadInfo = DownloadInfo());
private:
	QGSIDownloadSource * mDownloadSourcePtr;
};

/**/



