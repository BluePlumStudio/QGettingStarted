#include "LiteLoaderVersionInfoList.h"
#include "Util/QGSExceptionVersionNotFound.h"

LiteLoaderVersionReposity::LiteLoaderVersionReposity(const QString & stream, const QString & type, const QUrl & url, const QString & classifier)
	:mStream(stream), mType(type), mUrl(url), mClassifier(classifier)
{

}

LiteLoaderVersionReposity::~LiteLoaderVersionReposity()
{

}

QString LiteLoaderVersionReposity::getStream() const
{
	return mStream;
}

QString LiteLoaderVersionReposity::getType() const
{
	return mType;
}

QUrl LiteLoaderVersionReposity::getUrl() const
{
	return mUrl;
}

QString LiteLoaderVersionReposity::getClassifier() const
{
	return mClassifier;
}

LiteLoaderVersionReposity & LiteLoaderVersionReposity::setStream(const QString & stream)
{
	mStream = stream;
	return *this;
}

LiteLoaderVersionReposity & LiteLoaderVersionReposity::setType(const QString & type)
{
	mType = type;
	return *this;
}

LiteLoaderVersionReposity & LiteLoaderVersionReposity::setUrl(const QUrl & url)
{
	mUrl = url;
	return *this;
}

LiteLoaderVersionReposity & LiteLoaderVersionReposity::setClassifier(const QString & classifier)
{
	mClassifier = classifier;
	return *this;
}

/**/

LiteLoaderVersionMeta::LiteLoaderVersionMeta()
	:mTweakClass(""), mSrcJar(""), mMcpJar(""), mStream(""), mFile(""), mVersion(""), mBuild(""), mMd5(""), mTimestamp(""), mLastSuccessfulBuild(0)
{

}

LiteLoaderVersionMeta::~LiteLoaderVersionMeta()
{

}

QString LiteLoaderVersionMeta::getTweakClass() const
{
	return mTweakClass;
}

QList<Library> LiteLoaderVersionMeta::getLibraries() const
{
	return mLibraries;
}

QString LiteLoaderVersionMeta::getSrcJar() const
{
	return mSrcJar;
}

QString LiteLoaderVersionMeta::getMcpJar() const
{
	return mMcpJar;
}

QString LiteLoaderVersionMeta::getStream() const
{
	return mStream;
}

QString LiteLoaderVersionMeta::getFile() const
{
	return mFile;
}

QString LiteLoaderVersionMeta::getVersion() const
{
	return mVersion;
}

QString LiteLoaderVersionMeta::getBuild() const
{
	return mBuild;
}

QString LiteLoaderVersionMeta::getMd5() const
{
	return mMd5;
}

QString LiteLoaderVersionMeta::getTimestamp() const
{
	return mTimestamp;
}

int LiteLoaderVersionMeta::getLastSuccessfulBuild() const
{
	return mLastSuccessfulBuild;
}

LiteLoaderVersionMeta & LiteLoaderVersionMeta::setTweakClass(const QString & tweakClass)
{
	mTweakClass = tweakClass;
	return *this;
}

LiteLoaderVersionMeta & LiteLoaderVersionMeta::setLibraries(const QList<Library>& libraries)
{
	mLibraries = libraries;
	return *this;
}

LiteLoaderVersionMeta & LiteLoaderVersionMeta::setSrcJar(const QString & srcJar)
{
	mSrcJar = srcJar;
	return *this;
}

LiteLoaderVersionMeta & LiteLoaderVersionMeta::setMcpJar(const QString & mcpJar)
{
	mMcpJar = mcpJar;
	return *this;
}

LiteLoaderVersionMeta & LiteLoaderVersionMeta::setStream(const QString & stream)
{
	mStream = stream;
	return *this;
}

LiteLoaderVersionMeta & LiteLoaderVersionMeta::setFile(const QString & file)
{
	mFile = file;
	return *this;
}

LiteLoaderVersionMeta & LiteLoaderVersionMeta::setVersion(const QString & version)
{
	mVersion = version;
	return *this;
}

LiteLoaderVersionMeta & LiteLoaderVersionMeta::setBuild(const QString & build)
{
	mBuild = build;
	return *this;
}

LiteLoaderVersionMeta & LiteLoaderVersionMeta::setMd5(const QString & md5)
{
	mMd5 = md5;
	return *this;
}

LiteLoaderVersionMeta & LiteLoaderVersionMeta::setTimestamp(const QString & timestamp)
{
	mTimestamp = timestamp;
	return *this;
}

LiteLoaderVersionMeta & LiteLoaderVersionMeta::setLastSuccessfulBuild(const int lastSuccessfulBuild)
{
	mLastSuccessfulBuild = lastSuccessfulBuild;
	return *this;
}

/**/

LiteLoaderVersionInfo::LiteLoaderVersionInfo()
{

}

LiteLoaderVersionInfo::~LiteLoaderVersionInfo()
{

}

LiteLoaderVersionReposity LiteLoaderVersionInfo::getLiteLoaderVersionReposity() const
{
	return mLiteLoaderVersionReposity;
}

QMap<QString, LiteLoaderVersionMeta> LiteLoaderVersionInfo::getLiteLoaderVersionSnapshotMetaMap()const
{
	return mLiteLoaderVersionSnapshotMetaMap;
}

QMap<QString, LiteLoaderVersionMeta> LiteLoaderVersionInfo::getLiteLoaderVersionArtefactMetaMap() const
{
	return mLiteLoaderVersionArtefactMetaMap;
}

LiteLoaderVersionInfo & LiteLoaderVersionInfo::setLiteLoaderVersionReposity(const LiteLoaderVersionReposity & liteLoaderVersionReposity)
{
	mLiteLoaderVersionReposity = liteLoaderVersionReposity;
	return *this;
}

LiteLoaderVersionInfo & LiteLoaderVersionInfo::setLiteLoaderVersionSnapshotMetaMap(const QMap<QString, LiteLoaderVersionMeta> & liteLoaderVersionSnapshotMetaMap)
{
	mLiteLoaderVersionSnapshotMetaMap = liteLoaderVersionSnapshotMetaMap;
	return *this;
}

LiteLoaderVersionInfo & LiteLoaderVersionInfo::setLiteLoaderVersionArtefactMetaMap(const QMap<QString, LiteLoaderVersionMeta>& liteLoaderVersionArtefactMetaMap)
{
	mLiteLoaderVersionArtefactMetaMap = liteLoaderVersionArtefactMetaMap;
	return *this;
}

/**/

LiteLoaderVersionInfoList::LiteLoaderVersionInfoList()
{
}

LiteLoaderVersionInfo & LiteLoaderVersionInfoList::operator[](const int index)
{
	return *(mLiteLoaderVersionInfoMap.begin() + index);
}

LiteLoaderVersionInfoList::~LiteLoaderVersionInfoList()
{

}

bool LiteLoaderVersionInfoList::addVersionInfo(const QString & version, const LiteLoaderVersionInfo & versionInfo)
{
	if (mLiteLoaderVersionInfoMap.contains(version))
	{
		return false;
	}

	mLiteLoaderVersionInfoMap.insert(version, versionInfo);
	return true;
}

bool LiteLoaderVersionInfoList::removeVersionInfo(const QString & version)
{
	if (!mLiteLoaderVersionInfoMap.contains(version))
	{
		return false;
	}

	mLiteLoaderVersionInfoMap.remove(version);
	return true;
}

bool LiteLoaderVersionInfoList::containsVersionInfo(const QString & version)
{
	return mLiteLoaderVersionInfoMap.contains(version);
}

LiteLoaderVersionInfo & LiteLoaderVersionInfoList::getVersionInfo(const QString & version)
{
	return mLiteLoaderVersionInfoMap[version];
}

int LiteLoaderVersionInfoList::size()const
{
	return mLiteLoaderVersionInfoMap.size();
}
