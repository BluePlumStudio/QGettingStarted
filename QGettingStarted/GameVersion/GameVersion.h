#pragma once

#include <QString>
#include <QMap>

#include "Arguments.h"
#include "AssetIndex.h"
#include "Logging.h"
#include "Library.h"
#include "AssetIndexInfo.h"

namespace VersionType
{
	const QString RELEASE("release");
	const QString SNAPSHOT("snapshot");
	const QString MODIFIED("modified");
	const QString OLD_BETA("old-beta");
	const QString OLD_ALPHA("old-alpha");
	const QString UNKNOWN("unknown");
}

class GameVersion
{
public:
	GameVersion();

	GameVersion(const GameVersion & right) = default;

	GameVersion(GameVersion && right) = default;

	GameVersion & operator=(const GameVersion & right) = default;

	GameVersion & operator=(GameVersion && right) = default;

	~GameVersion();

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

	GameVersion & setId(const QString & id);
	GameVersion & setMinecraftArguments(const QString & minecraftArguments);
	GameVersion & setArguments(const Arguments & arguments);
	GameVersion & setMainClass(const QString & mainClass);
	GameVersion & setInheritsFrom(const QString & inheritsFrom);
	GameVersion & setJar(const QString & jar);
	GameVersion & setAssetIndex(const AssetIndex & assetIndex);
	GameVersion & setAssets(const QString & assets);
	GameVersion & setLibraries(const QList<Library> & libraries);
	GameVersion & setDownloads(const QMap<QString, Downloads::Download> & downloads);
	GameVersion & setLogging(const QMap<QString, Logging> & logging);
	GameVersion & setType(const QString & type);
	GameVersion & setTime(const QString & time);
	GameVersion & setReleaseTime(const QString & releaseTime);
	GameVersion & setProcessArguments(const QString & processArguments);
	GameVersion & setMinimumLauncherVersion(const int minimumLauncherVersion);

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

