#pragma once

#include <QMap>
#include <QVector>
#include <QFile>
#include <QList>

#include "QGSGameVersionInfo.h"

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

Q_DECLARE_METATYPE(QGSGameVersionInfoList)