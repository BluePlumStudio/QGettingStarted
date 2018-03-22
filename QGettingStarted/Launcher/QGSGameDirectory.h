#pragma once

#include <QDir>
#include <QFile>
#include <QVector>

#include "../GameVersion/QGSGameVersion.h"

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

	const QGSGameVersion & addVersion(const QString version);

	bool containsVersion(const QString & version)const;

	QFile * generateGameVersionJarFile(const QString & version, const bool withAbsolutePath = true)const;

	QFile * generateGameVersionJsonFile(const QString & version, const bool withAbsolutePath = true)const;

	QFile * generateAssetIndexJsonFile(const QGSAssetIndex & assetIndex, const bool withAbsolutePath = true)const;

	QFile * generateLibraryFile(const QGSLibrary & library, const bool withAbsolutePath = true)const;

	QVector<QFile *> generateLibraryFiles(const QList<QGSLibrary> & libraryList, const bool withAbsolutePath = true)const;

	QDir generateNativesDirectory(const QString & version, const bool withAbsolutePath = true)const;

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

