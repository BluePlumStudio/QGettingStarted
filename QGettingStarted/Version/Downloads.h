#pragma once

#include <QString>
#include <QUrl>
#include <QMap>
#include <QStringList>

class Downloads
{
public:
	class Download
	{
	public:
		Download(const int size, const QString & SHA1, const QString & path, const QUrl & url) :mSize(size), mSHA1(SHA1), mPath(path), mUrl(url)
		{

		}

		~Download()
		{

		}

		inline Download & setSize(const int size)
		{
			mSize = size;
			return *this;
		}

		inline Download & setSHA1(const QString & SHA1)
		{
			mSHA1 = SHA1;
			return *this;
		}

		inline Download & setPath(const QString & path)
		{
			mPath = path;
			return *this;
		}

		inline Download & setUrl(const QUrl & url)
		{
			mUrl = url;
			return *this;
		}

		inline int getSize()const
		{
			return mSize;
		}

		inline QString getSHA1()const
		{
			return mSHA1;
		}

		inline QString getPath()const
		{
			return mPath;
		}

		inline QUrl getUrl()const
		{
			return mUrl;
		}

	protected:
		int mSize;
		QString mSHA1;
		QString mPath;
		QUrl mUrl;
	};
public:
	Download mArtifact;
	QMap<QString, Download> mClassifiers;
};
