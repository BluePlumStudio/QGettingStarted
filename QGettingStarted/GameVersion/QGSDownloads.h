#pragma once

#include <QString>
#include <QUrl>
#include <QMap>
#include <QStringList>
#include <QObject>
#include <QMetaType>

namespace DownloadType
{
	const QString CLIENT("client");
	const QString SERVER("server");
	const QString WINDOWS_SERVER("windows_server");
	const QString UNKNOWN("unknown");
}

class QGSDownloadBase
{
public:
	QGSDownloadBase(const int size = 0, const QString & SHA1 = "", const QString & path = "", const QUrl & url = QUrl());

	QGSDownloadBase(const QGSDownloadBase & right) = default;

	QGSDownloadBase(QGSDownloadBase && right) = default;

	QGSDownloadBase & operator=(const QGSDownloadBase & right) = default;

	QGSDownloadBase & operator=(QGSDownloadBase && right) = default;

	virtual ~QGSDownloadBase();

	QGSDownloadBase & setSize(const int size);

	QGSDownloadBase & setSHA1(const QString & SHA1);

	QGSDownloadBase & setPath(const QString & path);

	QGSDownloadBase & setUrl(const QUrl & url);

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
	QGSDownloads(const QGSDownloadBase & artifact = QGSDownloadBase(), const QMap<QString, QGSDownloadBase> & classifiers = QMap<QString, QGSDownloadBase>());

	QGSDownloads(const QGSDownloads & right) = default;

	QGSDownloads(QGSDownloads && right) = default;

	QGSDownloads & operator=(const QGSDownloads & right) = default;

	QGSDownloads & operator=(QGSDownloads && right) = default;

	~QGSDownloads();

	QGSDownloads & setArtifact(const QGSDownloadBase & artifact);

	QGSDownloads & setClassifiers(const QMap<QString, QGSDownloadBase> & classifiers);

	QGSDownloadBase getArtifact()const;

	QMap<QString, QGSDownloadBase> getClassifiers()const;

	void clear();
public:
	QGSDownloadBase mArtifact;
	QMap<QString, QGSDownloadBase> mClassifiers;
};

Q_DECLARE_METATYPE(QGSDownloadBase)
Q_DECLARE_METATYPE(QGSDownloads)