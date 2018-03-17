#pragma once

#include "IVersionBuilder.h"
#include "Version.h"

class QGSVersionBulider :public IVersionBuilder
{
public:
	QGSVersionBulider();

	QGSVersionBulider(const QGSVersionBulider & right) = delete;

	QGSVersionBulider(QGSVersionBulider && right) = delete;

	QGSVersionBulider & operator=(const QGSVersionBulider & right) = delete;

	QGSVersionBulider & operator=(QGSVersionBulider && right) = delete;

	~QGSVersionBulider();

	virtual QGSVersionBulider & setId(const QString & id);
	virtual QGSVersionBulider & setMinecraftArguments(const QString & minecraftArguments);
	virtual QGSVersionBulider & setArguments(const Arguments & arguments);
	virtual QGSVersionBulider & setMainClass(const QString & mainClass);
	virtual QGSVersionBulider & setInheritsFrom(const QString & inheritsFrom);
	virtual QGSVersionBulider & setJar(const QString & jar);
	virtual QGSVersionBulider & setAssetIndex(const AssetIndex & assetIndex);
	virtual QGSVersionBulider & setAssets(const QString & assets);
	virtual QGSVersionBulider & setLibraries(const QList<Library> & libraries);
	virtual QGSVersionBulider & setDownloads(const QMap<QString, Downloads::Download> & downloads);
	virtual QGSVersionBulider & setLogging(const QMap<QString, Logging> & logging);
	virtual QGSVersionBulider & setType(const QString & type);
	virtual QGSVersionBulider & setTime(const QString & time);
	virtual QGSVersionBulider & setReleaseTime(const QString & releaseTime);
	virtual QGSVersionBulider & setProcessArguments(const QString & processArguments);
	virtual QGSVersionBulider & setMinimumLauncherVersion(const int minimumLauncherVersion);

	virtual Version * getVersion();

private:
	Version * mVersionPtr;
};

