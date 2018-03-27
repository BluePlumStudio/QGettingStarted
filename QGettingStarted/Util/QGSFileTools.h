#pragma once

#define QUAZIP_STATIC

#include "QuaZip/JlCompress.h"

class QGSFileTools
{
public:
	static QGSFileTools & getInstance();

	QGSFileTools(const QGSFileTools & right) = delete;

	QGSFileTools(QGSFileTools && right) = delete;

	QGSFileTools & operator=(const QGSFileTools & right) = delete;

	QGSFileTools & operator=(QGSFileTools && right) = delete;

	~QGSFileTools();

    static bool compressDirectory(const QString & file, const QString & directory, bool recursive = true);

    static QStringList extractDirectory(const QString & file, const QString & directory);

	static bool removeDirectory(const QString & absolutPath);
private:
	QGSFileTools();
};
