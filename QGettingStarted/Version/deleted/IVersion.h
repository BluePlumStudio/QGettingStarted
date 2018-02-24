#pragma once

#include <QString>

#include "Arguments.h"
#include "AssetIndex.h"
#include "Logging.h"
#include "Library.h"

namespace VersionType
{
	const QString RELEASE("release");
	const QString SNAPSHOT("snapshot");
	const QString MODIFIED("modified");
	const QString OLD_BETA("old-beta");
	const QString OLD_ALPHA("old-alpha");
	const QString UNKNOWN("unknown");
}

class Version 
{
public:
	Version();

	Version(const Version & right) = default;

	Version(Version && right) = default;

	Version & operator=(const Version & right) = default;

	Version & operator=(Version && right) = default;

	inline QString getId()const;
	inline QString getMinecraftArguments()const;
	inline Arguments getArguments()const;
	inline QString getMainClass()const;
	inline QString getInheritsFrom()const;
	inline QString getJar()const;
	inline AssetIndex getAssetIndex()const;
	inline QString getAssets()const;
	inline QList<Library> getLibraries()const;
	inline QMap<QString, Downloads::Download> getDownloads()const;
	inline QMap<QString, Logging> getLogging()const;
	inline QString getType()const;
	inline QString getTime()const;
	inline QString getReleaseTime()const;
	inline QString getProcessArguments()const;
	inline int getMinimumLauncherVersion()const;
	//
	virtual Version & setId(const QString & id) = 0;
	virtual Version & setMinecraftArguments(const QString & minecraftArguments) = 0;
	virtual Version & setArguments(const Arguments & arguments) = 0;
	virtual Version & setMainClass(const QString & mainClass) = 0;
	virtual Version & setInheritsFrom(const QString & inheritsFrom) = 0;
	virtual Version & setJar(const QString & jar) = 0;
	virtual Version & setAssetIndex(const AssetIndex & assetIndex) = 0;
	virtual Version & setAssets(const QString & assets) = 0;
	virtual Version & setLibraries(const QList<Library> & libraries) = 0;
	virtual Version & setDownloads(const QMap<QString, Downloads::Download> & downloads) = 0;
	virtual Version & setLogging(const QMap<QString, Logging> & logging) = 0;
	virtual Version & setType(const QString & type) = 0;
	virtual Version & setTime(const QString & time) = 0;
	virtual Version & setReleaseTime(const QString & releaseTime) = 0;
	virtual Version & setProcessArguments(const QString & processArguments) = 0;
	virtual Version & setMinimumLauncherVersion(const int minimumLauncherVersion) = 0;

	~Version();
protected:
	QString mId;
	QString mMinecraftArguments;
	Arguments mArguments;
	QString mMainClass;
	QString mInheritsFrom;
	QString mJar;
	AssetIndex mAssetIndex;
	QString mAssets;
	QList<Library> mLibraries;
	QMap<QString, Downloads::Download> mDownloads;
	QMap<QString, Logging> mLogging;
	QString mType;
	QString mTime;
	QString mReleaseTime;
	QString mProcessArguments;
	int mMinimumLauncherVersion;

	//QList<CompatibilityRule> mCompatibilityRules;
};
