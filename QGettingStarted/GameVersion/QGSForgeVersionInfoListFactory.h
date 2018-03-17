#pragma once

#include <QObject>
#include <QByteArray>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

#include "ForgeVersionInfoList.h"

class QGSForgeVersionInfoListFactory
{
public:
	QGSForgeVersionInfoListFactory();

	QGSForgeVersionInfoListFactory(const QGSForgeVersionInfoListFactory & right) = delete;

	QGSForgeVersionInfoListFactory(QGSForgeVersionInfoListFactory && right) = delete;

	QGSForgeVersionInfoListFactory & operator=(const QGSForgeVersionInfoListFactory & right) = delete;

	QGSForgeVersionInfoListFactory & operator=(QGSForgeVersionInfoListFactory && right) = delete;

	~QGSForgeVersionInfoListFactory();

	ForgeVersionInfoList createForgeVersionInfoList(const QByteArray & jsonData, int offset = 1, int limit = 0);
private:
	inline void praseForgeVersionInfoListStd(QJsonObject & jsonObject, int offset, int limit, ForgeVersionInfoList & forgeVersionInfoList);
	inline void praseForgeVersionInfoListBMCLAPI(QJsonArray & jsonArray, int offset, int limit, ForgeVersionInfoList & forgeVersionInfoList);

};
