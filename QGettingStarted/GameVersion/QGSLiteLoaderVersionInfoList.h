#pragma once

#include <QString>
#include <QMap>
#include <QVector>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QList>

#include "QGSLiteLoaderVersionInfo.h"

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

	QGSLiteLoaderVersionInfo getLiteLoaderVersionInfo(const int index);

	const QGSLiteLoaderVersionInfo & at(const int index);

	bool addVersionInfo(const QString & version, const QGSLiteLoaderVersionInfo & versionInfo);

	bool removeVersionInfo(const QString & version);

	bool containsVersionInfo(const QString & version);

	QGSLiteLoaderVersionInfo & getVersionInfo(const QString & version);

	int size()const;
private:
	QMap<QString, QGSLiteLoaderVersionInfo> mLiteLoaderVersionInfoMap;
};

Q_DECLARE_METATYPE(QGSLiteLoaderVersionInfoList)