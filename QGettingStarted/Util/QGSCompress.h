#pragma once

#include <QStringList>

#include "QGSExceptionCompress.h"
#include "QuaZip/quazip_global.h"
#include "QuaZip/JlCompress.h"

class QGSCompress
{
public:
	static QGSCompress & getInstance();

	QGSCompress(const QGSCompress & right) = delete;

	QGSCompress(QGSCompress && right) = delete;

	QGSCompress & operator=(const QGSCompress & right) = delete;

	QGSCompress & operator=(QGSCompress && right) = delete;

	~QGSCompress();

	static bool compressDirectory(QString & file, QString & directory, bool recursive = true);

	static QStringList extractDirectory(QString & file, QString & directory);
private:
	QGSCompress();

};