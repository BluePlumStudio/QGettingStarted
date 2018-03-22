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

class QGSDownloads
{
public:
	class QGSIDownload
	{
	public:
		QGSIDownload(const int size = 0, const QString & SHA1 = "", const QString & path = "", const QUrl & url = QUrl())
			:mSize(size), mSHA1(SHA1), mPath(path), mUrl(url)
		{

		}

		QGSIDownload(const QGSIDownload & right) = default;

		QGSIDownload(QGSIDownload && right) = default;

		QGSIDownload & operator=(const QGSIDownload & right) = default;

		QGSIDownload & operator=(QGSIDownload && right) = default;

		virtual ~QGSIDownload()
		{

		}

		QGSIDownload & setSize(const int size)
		{
			mSize = size;
			return *this;
		}

		QGSIDownload & setSHA1(const QString & SHA1)
		{
			mSHA1 = SHA1;
			return *this;
		}

		QGSIDownload & setPath(const QString & path)
		{
			mPath = path;
			return *this;
		}

		QGSIDownload & setUrl(const QUrl & url)
		{
			mUrl = url;
			return *this;
		}

		int getSize()const
		{
			return mSize;
		}

		QString getSHA1()const
		{
			return mSHA1;
		}

		QString getPath()const
		{
			return mPath;
		}

		QUrl getUrl()const
		{
			return mUrl;
		}

		void clear()
		{
			mSize = 0;
			mSHA1.clear();
			mPath.clear();
			mUrl.clear();
		}

	protected:
		int mSize;
		QString mSHA1;
		QString mPath;
		QUrl mUrl;
	};
public:
	QGSDownloads(QGSIDownload & artifact = QGSIDownload(), QMap<QString, QGSIDownload> & classifiers = QMap<QString, QGSIDownload>());

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
