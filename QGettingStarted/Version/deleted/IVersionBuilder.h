#pragma once

#include "Version.h"

class IVersionBuilder
{
public:
	IVersionBuilder();

	IVersionBuilder(const IVersionBuilder & right) = delete;

	IVersionBuilder(IVersionBuilder && right) = delete;

	IVersionBuilder & operator=(const IVersionBuilder & right) = delete;

	IVersionBuilder & operator=(IVersionBuilder && right) = delete;

	~IVersionBuilder();

	virtual IVersionBuilder & setId(const QString & id) = 0;
	virtual IVersionBuilder & setMinecraftArguments(const QString & minecraftArguments) = 0;
	virtual IVersionBuilder & setArguments(const Arguments & arguments) = 0;
	virtual IVersionBuilder & setMainClass(const QString & mainClass) = 0;
	virtual IVersionBuilder & setInheritsFrom(const QString & inheritsFrom) = 0;
	virtual IVersionBuilder & setJar(const QString & jar) = 0;
	virtual IVersionBuilder & setAssetIndex(const AssetIndex & assetIndex) = 0;
	virtual IVersionBuilder & setAssets(const QString & assets) = 0;
	virtual IVersionBuilder & setLibraries(const QList<Library> & libraries) = 0;
	virtual IVersionBuilder & setDownloads(const QMap<QString, Downloads::Download> & downloads) = 0;
	virtual IVersionBuilder & setLogging(const QMap<QString, Logging> & logging) = 0;
	virtual IVersionBuilder & setType(const QString & type) = 0;
	virtual IVersionBuilder & setTime(const QString & time) = 0;
	virtual IVersionBuilder & setReleaseTime(const QString & releaseTime) = 0;
	virtual IVersionBuilder & setProcessArguments(const QString & processArguments) = 0;
	virtual IVersionBuilder & setMinimumLauncherVersion(const int minimumLauncherVersion) = 0;

	virtual Version * getVersion() = 0;

private:

};
