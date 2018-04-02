#pragma once

#include <QMap>
#include <QVector>
#include <QUrl>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QList>

#include "QGSOptifineVersionInfo.h"

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

Q_DECLARE_METATYPE(QGSOptifineVersionInfoList)