#pragma once

#include <QObject>
#include <QByteArray>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

#include "QGSForgeVersionInfoList.h"

class QGSForgeVersionInfoListFactory
{
public:
	QGSForgeVersionInfoListFactory();

	QGSForgeVersionInfoListFactory(const QGSForgeVersionInfoListFactory & right) = delete;

	QGSForgeVersionInfoListFactory(QGSForgeVersionInfoListFactory && right) = delete;

	QGSForgeVersionInfoListFactory & operator=(const QGSForgeVersionInfoListFactory & right) = delete;

	QGSForgeVersionInfoListFactory & operator=(QGSForgeVersionInfoListFactory && right) = delete;

	~QGSForgeVersionInfoListFactory();

	QGSForgeVersionInfoList createForgeVersionInfoList(const QByteArray & jsonData, int offset = 1, int limit = 0);
private:
    inline void praseForgeVersionInfoListStd(const QJsonObject & jsonObject, int offset, int limit, QGSForgeVersionInfoList & forgeVersionInfoList);
    inline void praseForgeVersionInfoListBMCLAPI(const QJsonArray & jsonArray, int offset, int limit, QGSForgeVersionInfoList & forgeVersionInfoList);

};
