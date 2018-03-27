#pragma once

#include <QString>
#include <QUrl>
#include <QMap>
#include <QStringList>

namespace DownloadType
{
	const QString CLIENT{ "client" };
	const QString SERVER{ "server" };
	const QString WINDOWS_SERVER{ "windows_server" };
	const QString UNKNOWN{ "unknown" };
}

class QGSIDownload
{
public:
	QGSIDownload(const int size = 0, const QString & SHA1 = "", const QString & path = "", const QUrl & url = QUrl());

	QGSIDownload(const QGSIDownload & right) = default;

	QGSIDownload(QGSIDownload && right) = default;

	QGSIDownload & operator=(const QGSIDownload & right) = default;

	QGSIDownload & operator=(QGSIDownload && right) = default;

	virtual ~QGSIDownload();

	QGSIDownload & setSize(const int size);

	QGSIDownload & setSHA1(const QString & SHA1);

	QGSIDownload & setPath(const QString & path);

	QGSIDownload & setUrl(const QUrl & url);

	int getSize()const;

	QString getSHA1()const;

	QString getPath()const;

	QUrl getUrl()const;

	void clear();

protected:
	int mSize;
	QString mSHA1;
	QString mPath;
	QUrl mUrl;
};

class QGSDownloads
{
public:
	QGSDownloads(const QGSIDownload & artifact = QGSIDownload(), const QMap<QString, QGSIDownload> & classifiers = QMap<QString, QGSIDownload>());

	QGSDownloads(const QGSDownloads & right) = default;

	QGSDownloads(QGSDownloads && right) = default;

	QGSDownloads & operator=(const QGSDownloads & right) = default;

	QGSDownloads & operator=(QGSDownloads && right) = default;

	~QGSDownloads();

	QGSDownloads & setArtifact(const QGSIDownload & artifact);

	QGSDownloads & setClassifiers(const QMap<QString, QGSIDownload> & classifiers);

	QGSIDownload getArtifact()const;

	QMap<QString, QGSIDownload> getClassifiers()const;

	void clear();
public:
	QGSIDownload mArtifact;
	QMap<QString, QGSIDownload> mClassifiers;
};
