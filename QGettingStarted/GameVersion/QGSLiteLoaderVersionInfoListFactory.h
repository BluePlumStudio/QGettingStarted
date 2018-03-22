#pragma once

#include <QObject>
#include <QByteArray>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

#include "QGSLiteLoaderVersionInfoList.h"

class QGSLiteLoaderVersionInfoListFactory
{
public:
	QGSLiteLoaderVersionInfoListFactory();

	QGSLiteLoaderVersionInfoListFactory(const QGSLiteLoaderVersionInfoListFactory & right) = delete;

	QGSLiteLoaderVersionInfoListFactory(QGSLiteLoaderVersionInfoListFactory && right) = delete;

	QGSLiteLoaderVersionInfoListFactory & operator=(const QGSLiteLoaderVersionInfoListFactory & right) = delete;

	QGSLiteLoaderVersionInfoListFactory & operator=(QGSLiteLoaderVersionInfoListFactory && right) = delete;

	~QGSLiteLoaderVersionInfoListFactory();

	QGSLiteLoaderVersionInfoList createLiteLoaderVersionInfoList(const QByteArray & jsonData);
private:
	inline QGSLibrary praseLiteLoaderVersionMetaLibrary(QJsonObject & object)const;
	inline QGSLiteLoaderVersionMeta praseLiteLoaderVersionMeta(QJsonObject & object);
};
