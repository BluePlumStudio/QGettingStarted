#pragma once

#include <QStringList>
#include <QObject>

#include "zlib/zlib.h"
#include "zlib/zip.h"
#include "zlib/unzip.h"
#include "zlib/crypt.h"
#include "zlib/ioapi.h"
#include "zlib/iowin32.h"
#include "zlib/mztools.h"
#include "zlib/zconf.h"

class QGSFileTools :public QObject
{
	Q_OBJECT

public:
	static QGSFileTools & getInstance();

	QGSFileTools(const QGSFileTools & right) = delete;

	QGSFileTools(QGSFileTools && right) = delete;

	QGSFileTools & operator=(const QGSFileTools & right) = delete;

	QGSFileTools & operator=(QGSFileTools && right) = delete;

	virtual ~QGSFileTools();

    //static bool compressDirectory(const QString & file, const QString & directory, bool recursive = true);

	static QStringList extractDirectory(const QString & file, const QString & directory, const QString & password = QString());

	static bool removeDirectory(const QString & absolutPath);

	static QMap<QString, QString> getJavaPathListFromSystemSettings();
private:
	QGSFileTools(QObject * parent = nullptr);
};
