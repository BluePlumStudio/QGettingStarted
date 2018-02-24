#pragma once

#include "IGameDirectory.h"

class QGSGameDirectory: public IGameDirectory 
{
public:
	QGSGameDirectory(const QDir & baseDir);

	QGSGameDirectory(QDir && baseDir);

	QGSGameDirectory(const QGSGameDirectory & right) = delete;

	QGSGameDirectory & operator=(const QGSGameDirectory & right) = delete;

	QGSGameDirectory & operator=(QGSGameDirectory && right) = delete;

	virtual ~QGSGameDirectory();

	virtual const Version & getVersion(const QString & version)override;

	virtual bool containsVersion(const QString & version)const override;
private:
	void init();

	const Version & addVersion(const QString & version);
private:
	QMap<QString, Version> mMapVersions;
};

