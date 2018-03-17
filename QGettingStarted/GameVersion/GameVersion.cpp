#include "GameVersion.h"

GameVersion::GameVersion()
{

}

GameVersion::~GameVersion()
{

}

QString GameVersion::getId()const
{
	return mId;
}

QString GameVersion::getMinecraftArguments()const
{
	return mMinecraftArguments;
}

Arguments GameVersion::getArguments()const
{
	return mArguments;
}

QString GameVersion::getMainClass()const
{
	return mMainClass;
}

QString GameVersion::getInheritsFrom()const
{
	return mInheritsFrom;
}

QString GameVersion::getJar()const
{
	return mJar;
}

AssetIndex GameVersion::getAssetIndex()const
{
	return mAssetIndex;
}

QString GameVersion::getAssets()const
{
	return mAssets;
}

QList<Library> GameVersion::getLibraries()const
{
	return mLibraries;
}

QMap<QString, Downloads::Download> GameVersion::getDownloads()const
{
	return mDownloads;
}

QMap<QString, Logging> GameVersion::getLogging()const
{
	return mLogging;
}

QString GameVersion::getType()const
{
	return mType;
}

QString GameVersion::getTime()const
{
	return mTime;
}

QString GameVersion::getReleaseTime()const
{
	return mReleaseTime;
}

QString GameVersion::getProcessArguments()const
{
	return mProcessArguments;
}

int GameVersion::getMinimumLauncherVersion()const
{
	return  mMinimumLauncherVersion;
}


GameVersion & GameVersion::setId(const QString & id)
{
	mId = id;
	return *this;
}

GameVersion & GameVersion::setMinecraftArguments(const QString & minecraftArguments)
{
	mMinecraftArguments = minecraftArguments;
	return *this;
}

GameVersion & GameVersion::setArguments(const Arguments & arguments)
{
	mArguments = arguments;
	return *this;
}

GameVersion & GameVersion::setMainClass(const QString & mainClass)
{
	mMainClass = mainClass;
	return *this;
}

GameVersion & GameVersion::setInheritsFrom(const QString & inheritsFrom)
{
	mInheritsFrom = inheritsFrom;
	return *this;
}

GameVersion & GameVersion::setJar(const QString & jar)
{
	mJar = jar;
	return *this;
}

GameVersion & GameVersion::setAssetIndex(const AssetIndex & assetIndex)
{
	mAssetIndex = assetIndex;
	return *this;
}

GameVersion & GameVersion::setAssets(const QString & assets)
{
	mAssets = assets;
	return *this;
}

GameVersion & GameVersion::setLibraries(const QList<Library> & libraries)
{
	mLibraries = libraries;
	return *this;
}

GameVersion & GameVersion::setDownloads(const QMap<QString, Downloads::Download> & downloads)
{
	mDownloads = downloads;
	return *this;
}

GameVersion & GameVersion::setLogging(const QMap<QString, Logging> & logging)
{
	mLogging = logging;
	return *this;
}

GameVersion & GameVersion::setType(const QString & type)
{
	mType = type;
	return *this;
}

GameVersion & GameVersion::setTime(const QString & time)
{
	mTime = time;
	return *this;
}

GameVersion & GameVersion::setReleaseTime(const QString & releaseTime)
{
	mReleaseTime = releaseTime;
	return *this;
}

GameVersion & GameVersion::setProcessArguments(const QString & processArguments)
{
	mProcessArguments = processArguments;
	return *this;
}

GameVersion & GameVersion::setMinimumLauncherVersion(const int minimumLauncherVersion)
{
	mMinimumLauncherVersion = minimumLauncherVersion;
	return *this;
}

void GameVersion::clear()
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