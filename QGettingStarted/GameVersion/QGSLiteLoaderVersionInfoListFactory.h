#pragma once

#include <QObject>
#include <QByteArray>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

#include "LiteLoaderVersionInfoList.h"

class QGSLiteLoaderVersionInfoListFactory
{
public:
	QGSLiteLoaderVersionInfoListFactory();

	QGSLiteLoaderVersionInfoListFactory(const QGSLiteLoaderVersionInfoListFactory & right) = delete;

	QGSLiteLoaderVersionInfoListFactory(QGSLiteLoaderVersionInfoListFactory && right) = delete;

	QGSLiteLoaderVersionInfoListFactory & operator=(const QGSLiteLoaderVersionInfoListFactory & right) = delete;

	QGSLiteLoaderVersionInfoListFactory & operator=(QGSLiteLoaderVersionInfoListFactory && right) = delete;

	~QGSLiteLoaderVersionInfoListFactory();

	LiteLoaderVersionInfoList createLiteLoaderVersionInfoList(const QByteArray & jsonData);
private:
	inline Library praseLiteLoaderVersionMetaLibrary(QJsonObject & object)const;
	inline LiteLoaderVersionMeta praseLiteLoaderVersionMeta(QJsonObject & object);
};
