#pragma once

#include <QString>
#include <QMap>
#include <QVector>
#include <QUrl>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QList>

class GameVersionInfo
{
public:
	GameVersionInfo(const QString & id = "", const QString & type = "", const QString & time = "", const QString & releaseTime = "", const QUrl & url = QUrl());

	GameVersionInfo(const GameVersionInfo & right) = default;

	GameVersionInfo(GameVersionInfo && right) = default;

	GameVersionInfo & operator=(const GameVersionInfo & right) = default;

	GameVersionInfo & operator=(GameVersionInfo && right) = default;

	bool operator<(const GameVersionInfo & right)const;

	bool operator>(const GameVersionInfo & right)const;

	bool operator==(const GameVersionInfo & right)const;

	~GameVersionInfo();

	QString getId()const;
	QString getType()const;
	QString getTime()const;
	QString getReleaseTime()const;
	QUrl getUrl()const;

	GameVersionInfo & setId(const QString & id);
	GameVersionInfo & setType(const QString & type);
	GameVersionInfo & setTime(const QString & time);
	GameVersionInfo & setReleaseTime(const QString & releaseTime);
	GameVersionInfo & setUrl(const QUrl & url);

private:
	QString mId;
	QString mType;
	QString mTime;
	QString mReleaseTime;
	QUrl mUrl;
};

class GameVersionInfoList
{
public:
	GameVersionInfoList();

	GameVersionInfoList(const GameVersionInfoList & right) = default;

	GameVersionInfoList(GameVersionInfoList && right) = default;

	GameVersionInfoList & operator=(const GameVersionInfoList & right) = default;

	GameVersionInfoList & operator=(GameVersionInfoList && right) = default;

	GameVersionInfo & operator[](const int index);

	~GameVersionInfoList();

	QString getLatestSnapshot()const;

	QString getLatestRelease()const;

	GameVersionInfoList & setLatestSnapshot(const QString & snapshot);

	GameVersionInfoList & setLatestRelease(const QString & release);

	GameVersionInfo & getVersionInfo(const QString & version);

	bool addVersionInfo(const GameVersionInfo & versionInfo);

	bool removeVersionInfo(const QString & version);

	bool containsVersionInfo(const QString & version);

	int size();
private:
	void sort();
	QVector<GameVersionInfo>::iterator findGameVersionInfo(const QString & version);
private:
	QVector<GameVersionInfo> mGameVersionInfoVector;
	QString mLatestRelease;
	QString mLatestSnapshot;
};
