#pragma once

#include <QString>
#include <QMap>
#include <QMetaType>

#include "QGSArguments.h"
#include "QGSAssetIndex.h"
#include "QGSLogging.h"
#include "QGSLibrary.h"
#include "QGSAssetIndexInfo.h"

namespace VersionType
{
	const QString RELEASE("release");
	const QString SNAPSHOT("snapshot");
	const QString MODIFIED("modified");
	const QString OLD_BETA("old-beta");
	const QString OLD_ALPHA("old-alpha");
	const QString UNKNOWN("unknown");
}

class QGSGameVersion
{
public:
	QGSGameVersion();

	QGSGameVersion(const QGSGameVersion & right) = default;

	QGSGameVersion(QGSGameVersion && right) = default;

	QGSGameVersion & operator=(const QGSGameVersion & right) = default;

	QGSGameVersion & operator=(QGSGameVersion && right) = default;

	~QGSGameVersion();

	QString getId()const;
	QString getMinecraftArguments()const;
	QGSArguments getArguments()const;
	QString getMainClass()const;
	QString getInheritsFrom()const;
	QString getJar()const;
	QGSAssetIndex getAssetIndex()const;
	QString getAssets()const;
	QList<QGSLibrary> getLibraries()const;
	QMap<QString, QGSDownloadBase> getDownloads()const;
	QMap<QString, QGSLogging> getLogging()const;
	QString getType()const;
	QString getTime()const;
	QString getReleaseTime()const;
	QString getProcessArguments()const;
	int getMinimumLauncherVersion()const;

	QGSGameVersion & setId(const QString & id);
	QGSGameVersion & setMinecraftArguments(const QString & minecraftArguments);
	QGSGameVersion & setArguments(const QGSArguments & arguments);
	QGSGameVersion & setMainClass(const QString & mainClass);
	QGSGameVersion & setInheritsFrom(const QString & inheritsFrom);
	QGSGameVersion & setJar(const QString & jar);
	QGSGameVersion & setAssetIndex(const QGSAssetIndex & assetIndex);
	QGSGameVersion & setAssets(const QString & assets);
	QGSGameVersion & setLibraries(const QList<QGSLibrary> & libraries);
	QGSGameVersion & setDownloads(const QMap<QString, QGSDownloadBase> & downloads);
	QGSGameVersion & setLogging(const QMap<QString, QGSLogging> & logging);
	QGSGameVersion & setType(const QString & type);
	QGSGameVersion & setTime(const QString & time);
	QGSGameVersion & setReleaseTime(const QString & releaseTime);
	QGSGameVersion & setProcessArguments(const QString & processArguments);
	QGSGameVersion & setMinimumLauncherVersion(const int minimumLauncherVersion);

	void clear();
private:
	QString mId;
	QString mMinecraftArguments;
	QGSArguments mArguments;
	QString mMainClass;
	QString mInheritsFrom;
	QString mJar;
	QGSAssetIndex mAssetIndex;
	QString mAssets;
	QList<QGSLibrary> mLibraries;
	QMap<QString, QGSDownloadBase> mDownloads;
	QMap<QString, QGSLogging> mLogging;
	QString mType;
	QString mTime;
	QString mReleaseTime;
	QString mProcessArguments;
	int mMinimumLauncherVersion;
};


Q_DECLARE_METATYPE(QGSGameVersion)