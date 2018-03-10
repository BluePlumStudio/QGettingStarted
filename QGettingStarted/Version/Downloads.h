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

class Downloads
{
public:
	class Download
	{
	public:
		Download(const int size = 0, const QString & SHA1 = "", const QString & path = "", const QUrl & url = QUrl())
			:mSize(size), mSHA1(SHA1), mPath(path), mUrl(url)
		{

		}

		Download(const Download & right) = default;

		Download(Download && right) = default;

		Download & operator=(const Download & right) = default;

		Download & operator=(Download && right) = default;

		virtual ~Download()
		{

		}

		Download & setSize(const int size)
		{
			mSize = size;
			return *this;
		}

		Download & setSHA1(const QString & SHA1)
		{
			mSHA1 = SHA1;
			return *this;
		}

		Download & setPath(const QString & path)
		{
			mPath = path;
			return *this;
		}

		Download & setUrl(const QUrl & url)
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
	Downloads(Download & artifact = Download(), QMap<QString, Download> & classifiers = QMap<QString, Download>());

	Downloads(const Downloads & right) = default;

	Downloads(Downloads && right) = default;

	Downloads & operator=(const Downloads & right) = default;

	Downloads & operator=(Downloads && right) = default;

	~Downloads();

	Downloads & setArtifact(const Download & artifact);

	Downloads & setClassifiers(const QMap<QString, Download> & classifiers);

	Download getArtifact()const;

	QMap<QString, Download> getClassifiers()const;

	void clear();
public:
	Download mArtifact;
	QMap<QString, Download> mClassifiers;
};
