#pragma once

#include <QString>
#include <QMap>
#include <QVector>
#include <QUrl>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QList>

class OptifineVersionInfo
{
public:
	OptifineVersionInfo(const QString & id = "",
		const QString & mcversion = "",
		const QString & type = "",
		const QString & patch = "",
		const QString & fileName = "");

	OptifineVersionInfo(const OptifineVersionInfo & right) = default;

	OptifineVersionInfo(OptifineVersionInfo && right) = default;

	OptifineVersionInfo & operator=(const OptifineVersionInfo & right) = default;

	OptifineVersionInfo & operator=(OptifineVersionInfo && right) = default;

	bool operator<(const OptifineVersionInfo & right)const;

	bool operator>(const OptifineVersionInfo & right)const;

	bool operator==(const OptifineVersionInfo & right)const;

	~OptifineVersionInfo();

	QString getId()const;
	QString getMcversion()const;
	QString getType()const;
	QString getPatch()const;
	QString getFileName()const;

	OptifineVersionInfo & setId(const QString & id);
	OptifineVersionInfo & setMcversion(const QString & mcversion);
	OptifineVersionInfo & setType(const QString & type);
	OptifineVersionInfo & setPatch(const QString & patch);
	OptifineVersionInfo & setFileName(const QString & fileName);
private:
	QString mId;
	QString mMcversion;
	QString mType;
	QString mPatch;
	QString mFileName;
};


class OptifineVersionInfoList
{
public:
	OptifineVersionInfoList();

	OptifineVersionInfoList(const OptifineVersionInfoList & right) = default;

	OptifineVersionInfoList(OptifineVersionInfoList && right) = default;

	OptifineVersionInfoList & operator=(const OptifineVersionInfoList & right) = default;

	OptifineVersionInfoList & operator=(OptifineVersionInfoList && right) = default;

	OptifineVersionInfo & operator[](const int index);

	~OptifineVersionInfoList();

	QList<OptifineVersionInfo> getVersionInfoList(const QString & mcversion);

	bool addVersionInfo(const OptifineVersionInfo & versionInfo);

	int size();
private:
	void sort();
private:
	QVector<OptifineVersionInfo> mOptifineVersionInfoVector;
};
