#include "QGSDownloads.h"

QGSIDownload::QGSIDownload(const int size, const QString & SHA1, const QString & path, const QUrl & url)
	:mSize(size), mSHA1(SHA1), mPath(path), mUrl(url)
{

}

QGSIDownload::~QGSIDownload()
{

}

QGSIDownload & QGSIDownload::setSize(const int size)
{
	mSize = size;
	return *this;
}

QGSIDownload & QGSIDownload::setSHA1(const QString & SHA1)
{
	mSHA1 = SHA1;
	return *this;
}

QGSIDownload & QGSIDownload::setPath(const QString & path)
{
	mPath = path;
	return *this;
}

QGSIDownload & QGSIDownload::setUrl(const QUrl & url)
{
	mUrl = url;
	return *this;
}

int QGSIDownload::getSize()const
{
	return mSize;
}

QString QGSIDownload::getSHA1()const
{
	return mSHA1;
}

QString QGSIDownload::getPath()const
{
	return mPath;
}

QUrl QGSIDownload::getUrl()const
{
	return mUrl;
}

void QGSIDownload::clear()
{
	mSize = 0;
	mSHA1.clear();
	mPath.clear();
	mUrl.clear();
}

/**/

QGSDownloads::QGSDownloads(const QGSIDownload & artifact, const QMap<QString, QGSIDownload> & classifiers)
	:mArtifact(artifact), mClassifiers(classifiers)
{

}

QGSDownloads::~QGSDownloads()
{

}

QGSDownloads & QGSDownloads::setArtifact(const QGSIDownload & artifact)
{
	mArtifact = artifact;
	return *this;
}

QGSDownloads & QGSDownloads::setClassifiers(const QMap<QString, QGSIDownload> & classifiers)
{
	mClassifiers = classifiers;
	return *this;
}

QGSIDownload QGSDownloads::getArtifact()const
{
	return mArtifact;
}

QMap<QString, QGSIDownload> QGSDownloads::getClassifiers()const
{
	return mClassifiers;
}

void QGSDownloads::clear()
{
	mArtifact.clear();
	mClassifiers.clear();
}
