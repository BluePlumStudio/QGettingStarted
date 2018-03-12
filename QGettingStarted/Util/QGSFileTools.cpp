#include "QGSFileTools.h"

QGSFileTools::QGSFileTools()
{
}

QGSFileTools & QGSFileTools::getInstance()
{
	static QGSFileTools instance;
	return instance;
}

QGSFileTools::~QGSFileTools()
{
}

bool QGSFileTools::compressDirectory(QString & file, QString & directory, bool recursive)
{
	bool ret = true;

	try
	{
		ret = JlCompress::compressDir(file, directory);
	}
	catch (...)
	{
		ret = false;
	}

	return ret;
}

QStringList QGSFileTools::extractDirectory(QString & file, QString & directory)
{
	QStringList ret;

	try
	{
		ret = JlCompress::extractDir(file, directory);
	}
	catch (...)
	{
		ret.clear();
	}

	return ret;
}

bool QGSFileTools::removeDirectory(const QString & absolutPath)
{
	return QFile::remove(absolutPath);
}
