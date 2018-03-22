#pragma once

#include <QString>
#include <QMap>
#include <QVector>
#include <QUrl>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QList>

class QGSOptifineVersionInfo
{
public:
	QGSOptifineVersionInfo(const QString & id = "",
		const QString & mcversion = "",
		const QString & type = "",
		const QString & patch = "",
		const QString & fileName = "");

	QGSOptifineVersionInfo(const QGSOptifineVersionInfo & right) = default;

	QGSOptifineVersionInfo(QGSOptifineVersionInfo && right) = default;

	QGSOptifineVersionInfo & operator=(const QGSOptifineVersionInfo & right) = default;

	QGSOptifineVersionInfo & operator=(QGSOptifineVersionInfo && right) = default;

	bool operator<(const QGSOptifineVersionInfo & right)const;

	bool operator>(const QGSOptifineVersionInfo & right)const;

	bool operator==(const QGSOptifineVersionInfo & right)const;

	~QGSOptifineVersionInfo();

	QString getId()const;
	QString getMcversion()const;
	QString getType()const;
	QString getPatch()const;
	QString getFileName()const;

	QGSOptifineVersionInfo & setId(const QString & id);
	QGSOptifineVersionInfo & setMcversion(const QString & mcversion);
	QGSOptifineVersionInfo & setType(const QString & type);
	QGSOptifineVersionInfo & setPatch(const QString & patch);
	QGSOptifineVersionInfo & setFileName(const QString & fileName);
private:
	QString mId;
	QString mMcversion;
	QString mType;
	QString mPatch;
	QString mFileName;
};


class QGSOptifineVersionInfoList
{
public:
	QGSOptifineVersionInfoList();

	QGSOptifineVersionInfoList(const QGSOptifineVersionInfoList & right) = default;

	QGSOptifineVersionInfoList(QGSOptifineVersionInfoList && right) = default;

	QGSOptifineVersionInfoList & operator=(const QGSOptifineVersionInfoList & right) = default;

	QGSOptifineVersionInfoList & operator=(QGSOptifineVersionInfoList && right) = default;

	QGSOptifineVersionInfo & operator[](const int index);

	~QGSOptifineVersionInfoList();

	QList<QGSOptifineVersionInfo> getVersionInfoList(const QString & mcversion);

	bool addVersionInfo(const QGSOptifineVersionInfo & versionInfo);

	int size();
private:
	void sort();
private:
	QVector<QGSOptifineVersionInfo> mOptifineVersionInfoVector;
};
