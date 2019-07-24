#include "QGSGameVersion.h"

QGSGameVersion::QGSGameVersion()
{
	if (!QMetaType::isRegistered(QMetaType::type("QGSGameVersion")))
	{
		qRegisterMetaType<QGSGameVersion>("QGSGameVersion");
	}
}

QGSGameVersion::~QGSGameVersion()
{

}

QString QGSGameVersion::getId()const
{
	return mId;
}

QString QGSGameVersion::getMinecraftArguments()const
{
	return mMinecraftArguments;
}

QGSArguments QGSGameVersion::getArguments()const
{
	return mArguments;
}

QString QGSGameVersion::getMainClass()const
{
	return mMainClass;
}

QString QGSGameVersion::getInheritsFrom()const
{
	return mInheritsFrom;
}

QString QGSGameVersion::getJar()const
{
	return mJar;
}

QGSAssetIndex QGSGameVersion::getAssetIndex()const
{
	return mAssetIndex;
}

QString QGSGameVersion::getAssets()const
{
	return mAssets;
}

QList<QGSLibrary> QGSGameVersion::getLibraries()const
{
	return mLibraries;
}

QMap<QString, QGSDownloadBase> QGSGameVersion::getDownloads()const
{
	return mDownloads;
}

QMap<QString, QGSLogging> QGSGameVersion::getLogging()const
{
	return mLogging;
}

QString QGSGameVersion::getType()const
{
	return mType;
}

QString QGSGameVersion::getTime()const
{
	return mTime;
}

QString QGSGameVersion::getReleaseTime()const
{
	return mReleaseTime;
}

QString QGSGameVersion::getProcessArguments()const
{
	return mProcessArguments;
}

int QGSGameVersion::getMinimumLauncherVersion()const
{
	return  mMinimumLauncherVersion;
}


QGSGameVersion & QGSGameVersion::setId(const QString & id)
{
	mId = id;
	return *this;
}

QGSGameVersion & QGSGameVersion::setMinecraftArguments(const QString & minecraftArguments)
{
	mMinecraftArguments = minecraftArguments;
	return *this;
}

QGSGameVersion & QGSGameVersion::setArguments(const QGSArguments & arguments)
{
	mArguments = arguments;
	return *this;
}

QGSGameVersion & QGSGameVersion::setMainClass(const QString & mainClass)
{
	mMainClass = mainClass;
	return *this;
}

QGSGameVersion & QGSGameVersion::setInheritsFrom(const QString & inheritsFrom)
{
	mInheritsFrom = inheritsFrom;
	return *this;
}

QGSGameVersion & QGSGameVersion::setJar(const QString & jar)
{
	mJar = jar;
	return *this;
}

QGSGameVersion & QGSGameVersion::setAssetIndex(const QGSAssetIndex & assetIndex)
{
	mAssetIndex = assetIndex;
	return *this;
}

QGSGameVersion & QGSGameVersion::setAssets(const QString & assets)
{
	mAssets = assets;
	return *this;
}

QGSGameVersion & QGSGameVersion::setLibraries(const QList<QGSLibrary> & libraries)
{
	mLibraries = libraries;
	return *this;
}

QGSGameVersion & QGSGameVersion::setDownloads(const QMap<QString, QGSDownloadBase> & downloads)
{
	mDownloads = downloads;
	return *this;
}

QGSGameVersion & QGSGameVersion::setLogging(const QMap<QString, QGSLogging> & logging)
{
	mLogging = logging;
	return *this;
}

QGSGameVersion & QGSGameVersion::setType(const QString & type)
{
	mType = type;
	return *this;
}

QGSGameVersion & QGSGameVersion::setTime(const QString & time)
{
	mTime = time;
	return *this;
}

QGSGameVersion & QGSGameVersion::setReleaseTime(const QString & releaseTime)
{
	mReleaseTime = releaseTime;
	return *this;
}

QGSGameVersion & QGSGameVersion::setProcessArguments(const QString & processArguments)
{
	mProcessArguments = processArguments;
	return *this;
}

QGSGameVersion & QGSGameVersion::setMinimumLauncherVersion(const int minimumLauncherVersion)
{
	mMinimumLauncherVersion = minimumLauncherVersion;
	return *this;
}

void QGSGameVersion::clear()
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