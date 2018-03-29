#pragma once

#include <QList>
#include <QString>

#include "QGSLibrary.h"

class QGSLiteLoaderVersionMeta
{
public:
	QGSLiteLoaderVersionMeta();

	QGSLiteLoaderVersionMeta(const QGSLiteLoaderVersionMeta & right) = default;

	QGSLiteLoaderVersionMeta(QGSLiteLoaderVersionMeta && right) = default;

	QGSLiteLoaderVersionMeta & operator=(const QGSLiteLoaderVersionMeta & right) = default;

	QGSLiteLoaderVersionMeta & operator=(QGSLiteLoaderVersionMeta && right) = default;

	~QGSLiteLoaderVersionMeta();

	QString getTweakClass()const;
	QList<QGSLibrary> getLibraries()const;
	QString getSrcJar()const;
	QString getMcpJar()const;
	QString getStream()const;
	QString getFile()const;
	QString getVersion()const;
	QString getBuild()const;
	QString getMd5()const;
	QString getTimestamp()const;
	int getLastSuccessfulBuild()const;

	QGSLiteLoaderVersionMeta & setTweakClass(const QString & tweakClass);
	QGSLiteLoaderVersionMeta & setLibraries(const QList<QGSLibrary> & libraries);
	QGSLiteLoaderVersionMeta & setSrcJar(const QString & srcJar);
	QGSLiteLoaderVersionMeta & setMcpJar(const QString & mcpJar);
	QGSLiteLoaderVersionMeta & setStream(const QString & stream);
	QGSLiteLoaderVersionMeta & setFile(const QString & file);
	QGSLiteLoaderVersionMeta & setVersion(const QString & version);
	QGSLiteLoaderVersionMeta & setBuild(const QString & build);
	QGSLiteLoaderVersionMeta & setMd5(const QString & md5);
	QGSLiteLoaderVersionMeta & setTimestamp(const QString & timestamp);
	QGSLiteLoaderVersionMeta & setLastSuccessfulBuild(const int lastSuccessfulBuild);
private:
	QString mTweakClass;
	QList<QGSLibrary> mLibraries;
	QString mSrcJar;
	QString mMcpJar;
	QString mStream;
	QString mFile;
	QString mVersion;
	QString mBuild;
	QString mMd5;
	QString mTimestamp;
	int mLastSuccessfulBuild;
};
