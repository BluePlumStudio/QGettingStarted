#include "QGSDownloads.h"

QGSDownloadBase::QGSDownloadBase(const int size, const QString & SHA1, const QString & path, const QUrl & url)
	:mSize(size), mSHA1(SHA1), mPath(path), mUrl(url)
{
}

QGSDownloadBase::~QGSDownloadBase()
{

}

QGSDownloadBase & QGSDownloadBase::setSize(const int size)
{
	mSize = size;
	return *this;
}

QGSDownloadBase & QGSDownloadBase::setSHA1(const QString & SHA1)
{
	mSHA1 = SHA1;
	return *this;
}

QGSDownloadBase & QGSDownloadBase::setPath(const QString & path)
{
	mPath = path;
	return *this;
}

QGSDownloadBase & QGSDownloadBase::setUrl(const QUrl & url)
{
	mUrl = url;
	return *this;
}

int QGSDownloadBase::getSize()const
{
	return mSize;
}

QString QGSDownloadBase::getSHA1()const
{
	return mSHA1;
}

QString QGSDownloadBase::getPath()const
{
	return mPath;
}

QUrl QGSDownloadBase::getUrl()const
{
	return mUrl;
}

void QGSDownloadBase::clear()
{
	mSize = 0;
	mSHA1.clear();
	mPath.clear();
	mUrl.clear();
}

/**/

QGSDownloads::QGSDownloads(const QGSDownloadBase & artifact, const QMap<QString, QGSDownloadBase> & classifiers)
	:mArtifact(artifact), mClassifiers(classifiers)
{

}

QGSDownloads::~QGSDownloads()
{

}

QGSDownloads & QGSDownloads::setArtifact(const QGSDownloadBase & artifact)
{
	mArtifact = artifact;
	return *this;
}

QGSDownloads & QGSDownloads::setClassifiers(const QMap<QString, QGSDownloadBase> & classifiers)
{
	mClassifiers = classifiers;
	return *this;
}

QGSDownloadBase QGSDownloads::getArtifact()const
{
	return mArtifact;
}

QMap<QString, QGSDownloadBase> QGSDownloads::getClassifiers()const
{
	return mClassifiers;
}

void QGSDownloads::clear()
{
	mArtifact.clear();
	mClassifiers.clear();
}
