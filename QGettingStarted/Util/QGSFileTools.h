#pragma once

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

	static bool compressDirectory(QString & file, QString & directory, bool recursive = true);

	static QStringList extractDirectory(QString & file, QString & directory);

	static bool removeDirectory(const QString & absolutPath);
private:
	QGSFileTools();
};
