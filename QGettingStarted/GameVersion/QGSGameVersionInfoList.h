#pragma once

#include <QString>
#include <QMap>
#include <QVector>
#include <QUrl>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QList>

class QGSGameVersionInfo
{
public:
	QGSGameVersionInfo(const QString & id = "", const QString & type = "", const QString & time = "", const QString & releaseTime = "", const QUrl & url = QUrl());

	QGSGameVersionInfo(const QGSGameVersionInfo & right) = default;

	QGSGameVersionInfo(QGSGameVersionInfo && right) = default;

	QGSGameVersionInfo & operator=(const QGSGameVersionInfo & right) = default;

	QGSGameVersionInfo & operator=(QGSGameVersionInfo && right) = default;

	bool operator<(const QGSGameVersionInfo & right)const;

	bool operator>(const QGSGameVersionInfo & right)const;

	bool operator==(const QGSGameVersionInfo & right)const;

	~QGSGameVersionInfo();

	QString getId()const;
	QString getType()const;
	QString getTime()const;
	QString getReleaseTime()const;
	QUrl getUrl()const;

	QGSGameVersionInfo & setId(const QString & id);
	QGSGameVersionInfo & setType(const QString & type);
	QGSGameVersionInfo & setTime(const QString & time);
	QGSGameVersionInfo & setReleaseTime(const QString & releaseTime);
	QGSGameVersionInfo & setUrl(const QUrl & url);

private:
	QString mId;
	QString mType;
	QString mTime;
	QString mReleaseTime;
	QUrl mUrl;
};

class QGSGameVersionInfoList
{
public:
	QGSGameVersionInfoList();

	QGSGameVersionInfoList(const QGSGameVersionInfoList & right) = default;

	QGSGameVersionInfoList(QGSGameVersionInfoList && right) = default;

	QGSGameVersionInfoList & operator=(const QGSGameVersionInfoList & right) = default;

	QGSGameVersionInfoList & operator=(QGSGameVersionInfoList && right) = default;

	QGSGameVersionInfo & operator[](const int index);

	~QGSGameVersionInfoList();

	QString getLatestSnapshot()const;

	QString getLatestRelease()const;

	QGSGameVersionInfoList & setLatestSnapshot(const QString & snapshot);

	QGSGameVersionInfoList & setLatestRelease(const QString & release);

	QGSGameVersionInfo & getVersionInfo(const QString & version);

	bool addVersionInfo(const QGSGameVersionInfo & versionInfo);

	bool removeVersionInfo(const QString & version);

	bool containsVersionInfo(const QString & version);

	int size();
private:
	void sort();
	QVector<QGSGameVersionInfo>::iterator findGameVersionInfo(const QString & version);
private:
	QVector<QGSGameVersionInfo> mGameVersionInfoVector;
	QString mLatestRelease;
	QString mLatestSnapshot;
};
