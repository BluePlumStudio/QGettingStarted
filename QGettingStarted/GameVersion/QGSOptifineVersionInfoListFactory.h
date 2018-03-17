#pragma once

#include <QObject>
#include <QByteArray>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

#include "OptifineVersionInfoList.h"

class QGSOptifineVersionInfoListFactory
{
public:
	QGSOptifineVersionInfoListFactory();

	QGSOptifineVersionInfoListFactory(const QGSOptifineVersionInfoListFactory & right) = delete;

	QGSOptifineVersionInfoListFactory(QGSOptifineVersionInfoListFactory && right) = delete;

	QGSOptifineVersionInfoListFactory & operator=(const QGSOptifineVersionInfoListFactory & right) = delete;

	QGSOptifineVersionInfoListFactory & operator=(QGSOptifineVersionInfoListFactory && right) = delete;

	~QGSOptifineVersionInfoListFactory();

	OptifineVersionInfoList createOptifineVersionInfoList(const QByteArray & jsonData);
};
