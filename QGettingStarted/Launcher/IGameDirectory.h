#pragma once

#include <QDir>
#include <QMap>

#include "../Version/Version.h"

class IGameDirectory
{
public:
	IGameDirectory(const QDir & baseDir);

	IGameDirectory(QDir && baseDir);

	IGameDirectory(const IGameDirectory & right) = delete;

	IGameDirectory & operator=(const IGameDirectory & right) = delete;

	IGameDirectory & operator=(IGameDirectory && right) = delete;

	virtual ~IGameDirectory();

	virtual const Version & getVersion(const QString & version) = 0;

	virtual bool containsVersion(const QString & version)const = 0;

protected:
	QDir mBaseDir;
};

