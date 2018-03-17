#pragma once

#include <QDir>
#include <QFile>
#include <QVector>

#include "../GameVersion/GameVersion.h"

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

	const GameVersion & getVersion(const QString & version);

	const GameVersion & addVersion(const QString version);

	bool containsVersion(const QString & version)const;

	QFile * generateGameVersionJarFile(const QString & version, const bool withAbsolutePath = true)const;

	QFile * generateGameVersionJsonFile(const QString & version, const bool withAbsolutePath = true)const;

	QFile * generateAssetIndexJsonFile(const AssetIndex & assetIndex, const bool withAbsolutePath = true)const;

	QFile * generateLibraryFile(const Library & library, const bool withAbsolutePath = true)const;

	QVector<QFile *> generateLibraryFiles(const QList<Library> & libraryList, const bool withAbsolutePath = true)const;

	QDir generateNativesDirectory(const QString & version, const bool withAbsolutePath = true)const;

	QDir getBaseDir()const;

	static QString praseLibraryName(const Library & library);
	
	/*need to be updated*/
	bool generateAssetsDirectory(QString version, const AssetIndex & assetIndex, QDir & dir);

	QDir generateAssetsDirectory(const bool withAbsolutePath = true);

	QFile * generateAssetObjectFile(const AssetObject & assetObject, const bool withAbsolutePath = true);
private:
	void init();

private:
	QMap<QString, GameVersion> mVersionMap;
	QDir mBaseDir;
};

