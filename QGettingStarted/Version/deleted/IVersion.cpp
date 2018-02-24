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
