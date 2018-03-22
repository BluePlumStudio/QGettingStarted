#include "QGSLiteLoaderVersionInfoList.h"
#include "Util/QGSExceptionVersionNotFound.h"

QGSLiteLoaderVersionReposity::QGSLiteLoaderVersionReposity(const QString & stream, const QString & type, const QUrl & url, const QString & classifier)
	:mStream(stream), mType(type), mUrl(url), mClassifier(classifier)
{

}

QGSLiteLoaderVersionReposity::~QGSLiteLoaderVersionReposity()
{

}

QString QGSLiteLoaderVersionReposity::getStream() const
{
	return mStream;
}

QString QGSLiteLoaderVersionReposity::getType() const
{
	return mType;
}

QUrl QGSLiteLoaderVersionReposity::getUrl() const
{
	return mUrl;
}

QString QGSLiteLoaderVersionReposity::getClassifier() const
{
	return mClassifier;
}

QGSLiteLoaderVersionReposity & QGSLiteLoaderVersionReposity::setStream(const QString & stream)
{
	mStream = stream;
	return *this;
}

QGSLiteLoaderVersionReposity & QGSLiteLoaderVersionReposity::setType(const QString & type)
{
	mType = type;
	return *this;
}

QGSLiteLoaderVersionReposity & QGSLiteLoaderVersionReposity::setUrl(const QUrl & url)
{
	mUrl = url;
	return *this;
}

QGSLiteLoaderVersionReposity & QGSLiteLoaderVersionReposity::setClassifier(const QString & classifier)
{
	mClassifier = classifier;
	return *this;
}

/**/

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

/**/

QGSLiteLoaderVersionInfo::QGSLiteLoaderVersionInfo()
{

}

QGSLiteLoaderVersionInfo::~QGSLiteLoaderVersionInfo()
{

}

QGSLiteLoaderVersionReposity QGSLiteLoaderVersionInfo::getLiteLoaderVersionReposity() const
{
	return mLiteLoaderVersionReposity;
}

QMap<QString, QGSLiteLoaderVersionMeta> QGSLiteLoaderVersionInfo::getLiteLoaderVersionSnapshotMetaMap()const
{
	return mLiteLoaderVersionSnapshotMetaMap;
}

QMap<QString, QGSLiteLoaderVersionMeta> QGSLiteLoaderVersionInfo::getLiteLoaderVersionArtefactMetaMap() const
{
	return mLiteLoaderVersionArtefactMetaMap;
}

QGSLiteLoaderVersionInfo & QGSLiteLoaderVersionInfo::setLiteLoaderVersionReposity(const QGSLiteLoaderVersionReposity & liteLoaderVersionReposity)
{
	mLiteLoaderVersionReposity = liteLoaderVersionReposity;
	return *this;
}

QGSLiteLoaderVersionInfo & QGSLiteLoaderVersionInfo::setLiteLoaderVersionSnapshotMetaMap(const QMap<QString, QGSLiteLoaderVersionMeta> & liteLoaderVersionSnapshotMetaMap)
{
	mLiteLoaderVersionSnapshotMetaMap = liteLoaderVersionSnapshotMetaMap;
	return *this;
}

QGSLiteLoaderVersionInfo & QGSLiteLoaderVersionInfo::setLiteLoaderVersionArtefactMetaMap(const QMap<QString, QGSLiteLoaderVersionMeta>& liteLoaderVersionArtefactMetaMap)
{
	mLiteLoaderVersionArtefactMetaMap = liteLoaderVersionArtefactMetaMap;
	return *this;
}

/**/

QGSLiteLoaderVersionInfoList::QGSLiteLoaderVersionInfoList()
{
}

QGSLiteLoaderVersionInfo & QGSLiteLoaderVersionInfoList::operator[](const int index)
{
	return *(mLiteLoaderVersionInfoMap.begin() + index);
}

QGSLiteLoaderVersionInfoList::~QGSLiteLoaderVersionInfoList()
{

}

bool QGSLiteLoaderVersionInfoList::addVersionInfo(const QString & version, const QGSLiteLoaderVersionInfo & versionInfo)
{
	if (mLiteLoaderVersionInfoMap.contains(version))
	{
		return false;
	}

	mLiteLoaderVersionInfoMap.insert(version, versionInfo);
	return true;
}

bool QGSLiteLoaderVersionInfoList::removeVersionInfo(const QString & version)
{
	if (!mLiteLoaderVersionInfoMap.contains(version))
	{
		return false;
	}

	mLiteLoaderVersionInfoMap.remove(version);
	return true;
}

bool QGSLiteLoaderVersionInfoList::containsVersionInfo(const QString & version)
{
	return mLiteLoaderVersionInfoMap.contains(version);
}

QGSLiteLoaderVersionInfo & QGSLiteLoaderVersionInfoList::getVersionInfo(const QString & version)
{
	return mLiteLoaderVersionInfoMap[version];
}

int QGSLiteLoaderVersionInfoList::size()const
{
	return mLiteLoaderVersionInfoMap.size();
}
