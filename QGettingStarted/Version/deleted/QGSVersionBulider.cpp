#include "QGSVersionBulider.h"

QGSVersionBulider::QGSVersionBulider() :mVersionPtr(new Version())
{

}

QGSVersionBulider::~QGSVersionBulider()
{

}

QGSVersionBulider & QGSVersionBulider::setId(const QString & id)
{
	mVersionPtr->setId(id);
	return *this;
}

QGSVersionBulider & QGSVersionBulider::setMinecraftArguments(const QString & minecraftArguments)
{
	mVersionPtr->setMinecraftArguments(minecraftArguments);
	return *this;
}

QGSVersionBulider & QGSVersionBulider::setArguments(const Arguments & arguments)
{
	mVersionPtr->setArguments(arguments);
	return *this;
}

QGSVersionBulider & QGSVersionBulider::setMainClass(const QString & mainClass)
{
	mVersionPtr->setMainClass(mainClass);
	return *this;
}

QGSVersionBulider & QGSVersionBulider::setInheritsFrom(const QString & inheritsFrom)
{
	mVersionPtr->setInheritsFrom(inheritsFrom);
	return *this;
}

QGSVersionBulider & QGSVersionBulider::setJar(const QString & jar)
{
	mVersionPtr->setJar(jar);
	return *this;
}

QGSVersionBulider & QGSVersionBulider::setAssetIndex(const AssetIndex & assetIndex)
{
	mVersionPtr->setAssetIndex(assetIndex);
	return *this;
}

QGSVersionBulider & QGSVersionBulider::setAssets(const QString & assets)
{
	mVersionPtr->setAssets(assets);
	return *this;
}

QGSVersionBulider & QGSVersionBulider::setLibraries(const QList<Library> & libraries)
{
	mVersionPtr->setLibraries(libraries);
	return *this;
}

QGSVersionBulider & QGSVersionBulider::setDownloads(const QMap<QString, Downloads::Download> & downloads)
{
	mVersionPtr->setDownloads(downloads);
	return *this;
}

QGSVersionBulider & QGSVersionBulider::setLogging(const QMap<QString, Logging> & logging)
{
	mVersionPtr->setLogging(logging);
	return *this;
}

QGSVersionBulider & QGSVersionBulider::setType(const QString & type)
{
	mVersionPtr->setType(type);
	return *this;
}

QGSVersionBulider & QGSVersionBulider::setTime(const QString & time)
{
	mVersionPtr->setTime(time);
	return *this;
}

QGSVersionBulider & QGSVersionBulider::setReleaseTime(const QString & releaseTime)
{
	mVersionPtr->setReleaseTime(releaseTime);
	return *this;
}

QGSVersionBulider & QGSVersionBulider::setProcessArguments(const QString & processArguments)
{
	mVersionPtr->setProcessArguments(processArguments);
	return *this;
}

QGSVersionBulider & QGSVersionBulider::setMinimumLauncherVersion(const int minimumLauncherVersion)
{
	mVersionPtr->setMinimumLauncherVersion(minimumLauncherVersion);
	return *this;
}

Version * QGSVersionBulider::getVersion()
{
	return mVersionPtr;
}