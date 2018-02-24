#pragma once

#include <QString>
#include <QMap>

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

	~Version();

	QString getId()const;
	QString getMinecraftArguments()const;
	Arguments getArguments()const;
	QString getMainClass()const;
	QString getInheritsFrom()const;
	QString getJar()const;
	AssetIndex getAssetIndex()const;
	QString getAssets()const;
	QList<Library> getLibraries()const;
	QMap<QString, Downloads::Download> getDownloads()const;
	QMap<QString, Logging> getLogging()const;
	QString getType()const;
	QString getTime()const;
	QString getReleaseTime()const;
	QString getProcessArguments()const;
	int getMinimumLauncherVersion()const;

	Version & setId(const QString & id);
	Version & setMinecraftArguments(const QString & minecraftArguments);
	Version & setArguments(const Arguments & arguments);
	Version & setMainClass(const QString & mainClass);
	Version & setInheritsFrom(const QString & inheritsFrom);
	Version & setJar(const QString & jar);
	Version & setAssetIndex(const AssetIndex & assetIndex);
	Version & setAssets(const QString & assets);
	Version & setLibraries(const QList<Library> & libraries);
	Version & setDownloads(const QMap<QString, Downloads::Download> & downloads);
	Version & setLogging(const QMap<QString, Logging> & logging);
	Version & setType(const QString & type);
	Version & setTime(const QString & time);
	Version & setReleaseTime(const QString & releaseTime);
	Version & setProcessArguments(const QString & processArguments);
	Version & setMinimumLauncherVersion(const int minimumLauncherVersion);

	void clear();
private:
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
};

