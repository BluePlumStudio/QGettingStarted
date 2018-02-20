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

class IVersion 
{
protected:
	QString mId;
	QString mMinecraftArguments;
	Arguments mArguments;
	QString mMainClass;
	QString mInheritsFrom;
	//QString mJar;
	AssetIndex mAssetIndex;
	QString assets;
	QList<Library> libraries;
	//QList<CompatibilityRule> mCompatibilityRules;
	QMap<QString, Downloads::Download> mDownloads;
	QMap<QString, Logging> mLogging;
	QString mType;
	QString mTime;
	QString mReleaseTime;
	QString mProcessArguments;
	int mMinimumLauncherVersion;
};
