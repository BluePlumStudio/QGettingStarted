#pragma once

#include <QString>
#include <QMap>
#include <QVector>
#include <QUrl>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QList>

#include "Library.h"

class LiteLoaderVersionReposity
{
public:
	LiteLoaderVersionReposity(const QString & stream = "", const QString & type = "", const QUrl & url = QUrl(), const QString & classifier = "");

	LiteLoaderVersionReposity(const LiteLoaderVersionReposity & right) = default;

	LiteLoaderVersionReposity(LiteLoaderVersionReposity && right) = default;

	LiteLoaderVersionReposity & operator=(const LiteLoaderVersionReposity & right) = default;

	LiteLoaderVersionReposity & operator=(LiteLoaderVersionReposity && right) = default;

	~LiteLoaderVersionReposity();

	QString getStream()const;
	QString getType()const;
	QUrl getUrl()const;
	QString getClassifier()const;

	LiteLoaderVersionReposity & setStream(const QString & stream);
	LiteLoaderVersionReposity & setType(const QString & type);
	LiteLoaderVersionReposity & setUrl(const QUrl & url);
	LiteLoaderVersionReposity & setClassifier(const QString & classifier);
private:
	QString mStream;
	QString mType;
	QUrl mUrl;
	QString mClassifier;
};

class LiteLoaderVersionMeta
{
public:
	LiteLoaderVersionMeta();

	LiteLoaderVersionMeta(const LiteLoaderVersionMeta & right) = default;

	LiteLoaderVersionMeta(LiteLoaderVersionMeta && right) = default;

	LiteLoaderVersionMeta & operator=(const LiteLoaderVersionMeta & right) = default;

	LiteLoaderVersionMeta & operator=(LiteLoaderVersionMeta && right) = default;

	~LiteLoaderVersionMeta();

	QString getTweakClass()const;
	QList<Library> getLibraries()const;
	QString getSrcJar()const;
	QString getMcpJar()const;
	QString getStream()const;
	QString getFile()const;
	QString getVersion()const;
	QString getBuild()const;
	QString getMd5()const;
	QString getTimestamp()const;
	int getLastSuccessfulBuild()const;

	LiteLoaderVersionMeta & setTweakClass(const QString & tweakClass);
	LiteLoaderVersionMeta & setLibraries(const QList<Library> & libraries);
	LiteLoaderVersionMeta & setSrcJar(const QString & srcJar);
	LiteLoaderVersionMeta & setMcpJar(const QString & mcpJar);
	LiteLoaderVersionMeta & setStream(const QString & stream);
	LiteLoaderVersionMeta & setFile(const QString & file);
	LiteLoaderVersionMeta & setVersion(const QString & version);
	LiteLoaderVersionMeta & setBuild(const QString & build);
	LiteLoaderVersionMeta & setMd5(const QString & md5);
	LiteLoaderVersionMeta & setTimestamp(const QString & timestamp);
	LiteLoaderVersionMeta & setLastSuccessfulBuild(const int lastSuccessfulBuild);
private:
	QString mTweakClass;
	QList<Library> mLibraries;
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

class LiteLoaderVersionInfo
{
public:
	LiteLoaderVersionInfo();

	LiteLoaderVersionInfo(const LiteLoaderVersionInfo & right) = default;

	LiteLoaderVersionInfo(LiteLoaderVersionInfo && right) = default;

	LiteLoaderVersionInfo & operator=(const LiteLoaderVersionInfo & right) = default;

	LiteLoaderVersionInfo & operator=(LiteLoaderVersionInfo && right) = default;

	~LiteLoaderVersionInfo();

	LiteLoaderVersionReposity getLiteLoaderVersionReposity()const;
	QMap<QString, LiteLoaderVersionMeta> getLiteLoaderVersionSnapshotMetaMap()const;
	QMap<QString, LiteLoaderVersionMeta> getLiteLoaderVersionArtefactMetaMap()const;

	LiteLoaderVersionInfo & setLiteLoaderVersionReposity(const LiteLoaderVersionReposity & liteLoaderVersionReposity);
	LiteLoaderVersionInfo & setLiteLoaderVersionSnapshotMetaMap(const QMap<QString, LiteLoaderVersionMeta> & liteLoaderVersionSnapshotMetaMap);
	LiteLoaderVersionInfo & setLiteLoaderVersionArtefactMetaMap(const QMap<QString, LiteLoaderVersionMeta> & liteLoaderVersionArtefactMetaMap);
private:
	LiteLoaderVersionReposity mLiteLoaderVersionReposity;
	QMap<QString, LiteLoaderVersionMeta> mLiteLoaderVersionSnapshotMetaMap;
	QMap<QString, LiteLoaderVersionMeta> mLiteLoaderVersionArtefactMetaMap;
};

class LiteLoaderVersionInfoList
{
public:
	LiteLoaderVersionInfoList();

	LiteLoaderVersionInfoList(const LiteLoaderVersionInfoList & right) = default;

	LiteLoaderVersionInfoList(LiteLoaderVersionInfoList && right) = default;

	LiteLoaderVersionInfoList & operator=(const LiteLoaderVersionInfoList & right) = default;

	LiteLoaderVersionInfoList & operator=(LiteLoaderVersionInfoList && right) = default;

	LiteLoaderVersionInfo & operator[](const int index);

	~LiteLoaderVersionInfoList();

	bool addVersionInfo(const QString & version, const LiteLoaderVersionInfo & versionInfo);

	bool removeVersionInfo(const QString & version);

	bool containsVersionInfo(const QString & version);

	LiteLoaderVersionInfo & getVersionInfo(const QString & version);

	int size()const;
private:
	QMap<QString, LiteLoaderVersionInfo> mLiteLoaderVersionInfoMap;
};
