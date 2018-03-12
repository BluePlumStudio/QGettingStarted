#pragma once

#include <QString>
#include <QMap>
#include <QVector>
#include <QUrl>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QList>

class VersionInfo
{
public:
	VersionInfo(const QString & id = "", const QString & type = "", const QString & time = "", const QString & releaseTime = "", const QUrl & url = QUrl());

	VersionInfo(const VersionInfo & right) = default;

	VersionInfo(VersionInfo && right) = default;

	VersionInfo & operator=(const VersionInfo & right) = default;

	VersionInfo & operator=(VersionInfo && right) = default;

	bool operator<(const VersionInfo & right)const;

	~VersionInfo();

	QString getId()const;
	QString getType()const;
	QString getTime()const;
	QString getReleaseTime()const;
	QUrl getUrl()const;

	VersionInfo & setId(const QString & id);
	VersionInfo & setType(const QString & type);
	VersionInfo & setTime(const QString & time);
	VersionInfo & setReleaseTime(const QString & releaseTime);
	VersionInfo & setUrl(const QUrl & url);

private:
	QString mId;
	QString mType;
	QString mTime;
	QString mReleaseTime;
	QUrl mUrl;
};

class VersionInfoList
{
public:
	VersionInfoList(QFile & manifestFile);

	VersionInfoList(const VersionInfoList & right) = default;

	VersionInfoList(VersionInfoList && right) = default;

	VersionInfoList & operator=(const VersionInfoList & right) = default;

	VersionInfoList & operator=(VersionInfoList && right) = default;

	VersionInfo & operator[](const int index);

	~VersionInfoList();

	QString getLatestSnapshot()const;

	QString getLatestRelease()const;

	const VersionInfo & getVersionInfo(const QString & version);

	bool addVersionInfo(const VersionInfo & versionInfo);

	bool removeVersionInfo(const QString & version);

	bool containsVersionInfo(const QString & version);

	int size();
private:
	void init(QFile & manifestFile);
	bool praseLatest(QJsonObject & jsonObject);
	bool praseVersions(QJsonObject & jsonObject);
	void sort();
	QVector<VersionInfo>::iterator findVersionInfo(const QString & version);
private:
	QVector<VersionInfo> mVersionInfoVector;
	QString mLatestRelease;
	QString mLatestSnapshot;
};
