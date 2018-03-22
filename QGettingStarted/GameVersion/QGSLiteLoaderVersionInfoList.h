#pragma once

#include <QString>
#include <QMap>
#include <QVector>
#include <QUrl>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QList>

#include "QGSLibrary.h"

class QGSLiteLoaderVersionReposity
{
public:
	QGSLiteLoaderVersionReposity(const QString & stream = "", const QString & type = "", const QUrl & url = QUrl(), const QString & classifier = "");

	QGSLiteLoaderVersionReposity(const QGSLiteLoaderVersionReposity & right) = default;

	QGSLiteLoaderVersionReposity(QGSLiteLoaderVersionReposity && right) = default;

	QGSLiteLoaderVersionReposity & operator=(const QGSLiteLoaderVersionReposity & right) = default;

	QGSLiteLoaderVersionReposity & operator=(QGSLiteLoaderVersionReposity && right) = default;

	~QGSLiteLoaderVersionReposity();

	QString getStream()const;
	QString getType()const;
	QUrl getUrl()const;
	QString getClassifier()const;

	QGSLiteLoaderVersionReposity & setStream(const QString & stream);
	QGSLiteLoaderVersionReposity & setType(const QString & type);
	QGSLiteLoaderVersionReposity & setUrl(const QUrl & url);
	QGSLiteLoaderVersionReposity & setClassifier(const QString & classifier);
private:
	QString mStream;
	QString mType;
	QUrl mUrl;
	QString mClassifier;
};

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

class QGSLiteLoaderVersionInfo
{
public:
	QGSLiteLoaderVersionInfo();

	QGSLiteLoaderVersionInfo(const QGSLiteLoaderVersionInfo & right) = default;

	QGSLiteLoaderVersionInfo(QGSLiteLoaderVersionInfo && right) = default;

	QGSLiteLoaderVersionInfo & operator=(const QGSLiteLoaderVersionInfo & right) = default;

	QGSLiteLoaderVersionInfo & operator=(QGSLiteLoaderVersionInfo && right) = default;

	~QGSLiteLoaderVersionInfo();

	QGSLiteLoaderVersionReposity getLiteLoaderVersionReposity()const;
	QMap<QString, QGSLiteLoaderVersionMeta> getLiteLoaderVersionSnapshotMetaMap()const;
	QMap<QString, QGSLiteLoaderVersionMeta> getLiteLoaderVersionArtefactMetaMap()const;

	QGSLiteLoaderVersionInfo & setLiteLoaderVersionReposity(const QGSLiteLoaderVersionReposity & liteLoaderVersionReposity);
	QGSLiteLoaderVersionInfo & setLiteLoaderVersionSnapshotMetaMap(const QMap<QString, QGSLiteLoaderVersionMeta> & liteLoaderVersionSnapshotMetaMap);
	QGSLiteLoaderVersionInfo & setLiteLoaderVersionArtefactMetaMap(const QMap<QString, QGSLiteLoaderVersionMeta> & liteLoaderVersionArtefactMetaMap);
private:
	QGSLiteLoaderVersionReposity mLiteLoaderVersionReposity;
	QMap<QString, QGSLiteLoaderVersionMeta> mLiteLoaderVersionSnapshotMetaMap;
	QMap<QString, QGSLiteLoaderVersionMeta> mLiteLoaderVersionArtefactMetaMap;
};

class QGSLiteLoaderVersionInfoList
{
public:
	QGSLiteLoaderVersionInfoList();

	QGSLiteLoaderVersionInfoList(const QGSLiteLoaderVersionInfoList & right) = default;

	QGSLiteLoaderVersionInfoList(QGSLiteLoaderVersionInfoList && right) = default;

	QGSLiteLoaderVersionInfoList & operator=(const QGSLiteLoaderVersionInfoList & right) = default;

	QGSLiteLoaderVersionInfoList & operator=(QGSLiteLoaderVersionInfoList && right) = default;

	QGSLiteLoaderVersionInfo & operator[](const int index);

	~QGSLiteLoaderVersionInfoList();

	bool addVersionInfo(const QString & version, const QGSLiteLoaderVersionInfo & versionInfo);

	bool removeVersionInfo(const QString & version);

	bool containsVersionInfo(const QString & version);

	QGSLiteLoaderVersionInfo & getVersionInfo(const QString & version);

	int size()const;
private:
	QMap<QString, QGSLiteLoaderVersionInfo> mLiteLoaderVersionInfoMap;
};
