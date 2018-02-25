#pragma once

#include <QDir>
#include <QFile>

#include "../Version/Version.h"

class QGSGameDirectory 
{
public:
	QGSGameDirectory(const QDir & baseDir);

	QGSGameDirectory(QDir && baseDir);

	QGSGameDirectory(const QGSGameDirectory & right) = delete;

	QGSGameDirectory & operator=(const QGSGameDirectory & right) = delete;

	QGSGameDirectory & operator=(QGSGameDirectory && right) = delete;

	~QGSGameDirectory();

	const Version & getVersion(const QString & version);

	bool containsVersion(const QString & version)const;

	QFile * getVersionJarFile(const QString & version)const;

	QFile * getLibraryFile(const Library & library)const;

	QDir getNativesDirectory(const QString & version)const;

	QDir getBaseDir()const;

	QDir getAssetDirectory(const QString & version, const AssetIndex & assetIndex);
private:
	void init();

	const Version & addVersion(const QString & version);
private:
	QMap<QString, Version> mMapVersions;
	QDir mBaseDir;
};

