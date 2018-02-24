#include "Version.h"

Version::Version()
{

}

Version::~Version()
{

}

QString Version::getId()const
{
	return mId;
}

QString Version::getMinecraftArguments()const
{
	return mMinecraftArguments;
}

Arguments Version::getArguments()const
{
	return mArguments;
}

QString Version::getMainClass()const
{
	return mMainClass;
}

QString Version::getInheritsFrom()const
{
	return mInheritsFrom;
}

QString Version::getJar()const
{
	return mJar;
}

AssetIndex Version::getAssetIndex()const
{
	return mAssetIndex;
}

QString Version::getAssets()const
{
	return mAssets;
}

QList<Library> Version::getLibraries()const
{
	return mLibraries;
}

QMap<QString, Downloads::Download> Version::getDownloads()const
{
	return mDownloads;
}

QMap<QString, Logging> Version::getLogging()const
{
	return mLogging;
}

QString Version::getType()const
{
	return mType;
}

QString Version::getTime()const
{
	return mTime;
}

QString Version::getReleaseTime()const
{
	return mReleaseTime;
}

QString Version::getProcessArguments()const
{
	return mProcessArguments;
}

int Version::getMinimumLauncherVersion()const
{
	return  mMinimumLauncherVersion;
}


Version & Version::setId(const QString & id)
{
	mId = id;
	return *this;
}

Version & Version::setMinecraftArguments(const QString & minecraftArguments)
{
	mMinecraftArguments = minecraftArguments;
	return *this;
}

Version & Version::setArguments(const Arguments & arguments)
{
	mArguments = arguments;
	return *this;
}

Version & Version::setMainClass(const QString & mainClass)
{
	mMainClass = mainClass;
	return *this;
}

Version & Version::setInheritsFrom(const QString & inheritsFrom)
{
	mInheritsFrom = inheritsFrom;
	return *this;
}

Version & Version::setJar(const QString & jar)
{
	mJar = jar;
	return *this;
}

Version & Version::setAssetIndex(const AssetIndex & assetIndex)
{
	mAssetIndex = assetIndex;
	return *this;
}

Version & Version::setAssets(const QString & assets)
{
	mAssets = assets;
	return *this;
}

Version & Version::setLibraries(const QList<Library> & libraries)
{
	mLibraries = libraries;
	return *this;
}

Version & Version::setDownloads(const QMap<QString, Downloads::Download> & downloads)
{
	mDownloads = downloads;
	return *this;
}

Version & Version::setLogging(const QMap<QString, Logging> & logging)
{
	mLogging = logging;
	return *this;
}

Version & Version::setType(const QString & type)
{
	mType = type;
	return *this;
}

Version & Version::setTime(const QString & time)
{
	mTime = time;
	return *this;
}

Version & Version::setReleaseTime(const QString & releaseTime)
{
	mReleaseTime = releaseTime;
	return *this;
}

Version & Version::setProcessArguments(const QString & processArguments)
{
	mProcessArguments = processArguments;
	return *this;
}

Version & Version::setMinimumLauncherVersion(const int minimumLauncherVersion)
{
	mMinimumLauncherVersion = minimumLauncherVersion;
	return *this;
}

void Version::clear()
{
	mId.clear();
	mMinecraftArguments.clear();
	mArguments.clear();
	mMainClass.clear();
	mInheritsFrom.clear();
	mJar.clear();
	mAssetIndex.clear();
	mAssets.clear();
	mLibraries.clear();
	mDownloads.clear();
	mLogging.clear();
	mType.clear();
	mTime.clear();
	mReleaseTime.clear();
	mProcessArguments.clear();
	mMinimumLauncherVersion = 0;
}