#pragma once

#include <QDir>
#include <QFile>
#include <QVector>

#include "../GameVersion/QGSGameVersion.h"
#include "../GameVersion/QGSGameVersionInfoList.h"

class QGSGameDirectory 
{
public:
	QGSGameDirectory(const QDir & baseDir);

	QGSGameDirectory(QDir && baseDir);

	QGSGameDirectory(const QGSGameDirectory & right) = default;

	QGSGameDirectory(QGSGameDirectory && right) = default;

	QGSGameDirectory & operator=(const QGSGameDirectory & right) = default;

	QGSGameDirectory & operator=(QGSGameDirectory && right) = default;

	~QGSGameDirectory();

	const QGSGameVersion & getVersion(const QString & version);

	const QGSGameVersion & getVersion(const QGSGameVersionInfo & gameVersionInfo);

	const QGSGameVersion & addVersion(const QString version);

	const QGSGameVersion & addVersion(const QGSGameVersionInfo & gameVersionInfo);

	bool containsVersion(const QString & version)const;

	bool containsVersion(const QGSGameVersionInfo & gameVersionInfo)const;

	QFile * generateGameVersionJarFile(const QString & version, const bool withAbsolutePath = true)const;

	QFile * generateGameVersionJarFile(const QGSGameVersionInfo & gameVersionInfo, const bool withAbsolutePath = true)const;

	QFile * generateGameVersionJsonFile(const QString & version, const bool withAbsolutePath = true)const;

	QFile * generateGameVersionJsonFile(const QGSGameVersionInfo & gameVersionInfo, const bool withAbsolutePath = true)const;

	QFile * generateAssetIndexJsonFile(const QGSAssetIndex & assetIndex, const bool withAbsolutePath = true)const;

	QFile * generateAssetIndexJsonFile(const QString & version, const bool withAbsolutePath = true);

	QFile * generateAssetIndexJsonFile(const QGSGameVersionInfo & gameVersionInfo, const bool withAbsolutePath = true);

	QFile * generateLibraryFile(const QGSLibrary & library, const bool withAbsolutePath = true)const;

	QVector<QFile *> generateLibraryFiles(const QList<QGSLibrary> & libraryList, const bool withAbsolutePath = true)const;

	QDir generateNativesDirectory(const QString & version, const bool withAbsolutePath = true)const;

	QDir generateNativesDirectory(const QGSGameVersionInfo & gameVersionInfo, const bool withAbsolutePath = true)const;

	QDir getBaseDir()const;

	static QString praseLibraryName(const QGSLibrary & library);
	
	/*need to be updated*/
	bool generateAssetsDirectory(QString version, const QGSAssetIndex & assetIndex, QDir & dir);

	QDir generateAssetsDirectory(const bool withAbsolutePath = true);

	QFile * generateAssetObjectFile(const QGSAssetObject & assetObject, const bool withAbsolutePath = true);
private:
	void init();

private:
	QMap<QString, QGSGameVersion> mVersionMap;
	QDir mBaseDir;
};

