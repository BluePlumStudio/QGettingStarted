#include "QGSLiteLoaderVersionMeta.h"

QGSLiteLoaderVersionMeta::QGSLiteLoaderVersionMeta()
	:mTweakClass(""), mSrcJar(""), mMcpJar(""), mStream(""), mFile(""), mVersion(""), mBuild(""), mMd5(""), mTimestamp(""), mLastSuccessfulBuild(0)
{

}

QGSLiteLoaderVersionMeta::~QGSLiteLoaderVersionMeta()
{

}

QString QGSLiteLoaderVersionMeta::getTweakClass() const
{
	return mTweakClass;
}

QList<QGSLibrary> QGSLiteLoaderVersionMeta::getLibraries() const
{
	return mLibraries;
}

QString QGSLiteLoaderVersionMeta::getSrcJar() const
{
	return mSrcJar;
}

QString QGSLiteLoaderVersionMeta::getMcpJar() const
{
	return mMcpJar;
}

QString QGSLiteLoaderVersionMeta::getStream() const
{
	return mStream;
}

QString QGSLiteLoaderVersionMeta::getFile() const
{
	return mFile;
}

QString QGSLiteLoaderVersionMeta::getVersion() const
{
	return mVersion;
}

QString QGSLiteLoaderVersionMeta::getBuild() const
{
	return mBuild;
}

QString QGSLiteLoaderVersionMeta::getMd5() const
{
	return mMd5;
}

QString QGSLiteLoaderVersionMeta::getTimestamp() const
{
	return mTimestamp;
}

int QGSLiteLoaderVersionMeta::getLastSuccessfulBuild() const
{
	return mLastSuccessfulBuild;
}

QGSLiteLoaderVersionMeta & QGSLiteLoaderVersionMeta::setTweakClass(const QString & tweakClass)
{
	mTweakClass = tweakClass;
	return *this;
}

QGSLiteLoaderVersionMeta & QGSLiteLoaderVersionMeta::setLibraries(const QList<QGSLibrary>& libraries)
{
	mLibraries = libraries;
	return *this;
}

QGSLiteLoaderVersionMeta & QGSLiteLoaderVersionMeta::setSrcJar(const QString & srcJar)
{
	mSrcJar = srcJar;
	return *this;
}

QGSLiteLoaderVersionMeta & QGSLiteLoaderVersionMeta::setMcpJar(const QString & mcpJar)
{
	mMcpJar = mcpJar;
	return *this;
}

QGSLiteLoaderVersionMeta & QGSLiteLoaderVersionMeta::setStream(const QString & stream)
{
	mStream = stream;
	return *this;
}

QGSLiteLoaderVersionMeta & QGSLiteLoaderVersionMeta::setFile(const QString & file)
{
	mFile = file;
	return *this;
}

QGSLiteLoaderVersionMeta & QGSLiteLoaderVersionMeta::setVersion(const QString & version)
{
	mVersion = version;
	return *this;
}

QGSLiteLoaderVersionMeta & QGSLiteLoaderVersionMeta::setBuild(const QString & build)
{
	mBuild = build;
	return *this;
}

QGSLiteLoaderVersionMeta & QGSLiteLoaderVersionMeta::setMd5(const QString & md5)
{
	mMd5 = md5;
	return *this;
}

QGSLiteLoaderVersionMeta & QGSLiteLoaderVersionMeta::setTimestamp(const QString & timestamp)
{
	mTimestamp = timestamp;
	return *this;
}

QGSLiteLoaderVersionMeta & QGSLiteLoaderVersionMeta::setLastSuccessfulBuild(const int lastSuccessfulBuild)
{
	mLastSuccessfulBuild = lastSuccessfulBuild;
	return *this;
}
