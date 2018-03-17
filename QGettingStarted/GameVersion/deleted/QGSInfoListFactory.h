#pragma once

#include <QObject>
#include <QByteArray>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

#include "GameVersionInfoListFactory.h"
#include "ForgeVersionInfoListFactory.h"
#include "LiteLoaderVersionInfoListFactory.h"
#include "AssetInfoListFactory.h"

class QGSInfoListFactory
{
public:
	QGSInfoListFactory();

	QGSInfoListFactory(const QGSInfoListFactory & right) = delete;

	QGSInfoListFactory(QGSInfoListFactory && right) = delete;

	QGSInfoListFactory & operator=(const QGSInfoListFactory & right) = delete;

	QGSInfoListFactory & operator=(QGSInfoListFactory && right) = delete;

	~QGSInfoListFactory();

	GameVersionInfoList createGameVersionInfoList(const QByteArray & jsonData);

	ForgeVersionInfoList createForgeVersionInfoList(const QByteArray & jsonData, int offset = 1, int limit = 0);

	LiteLoaderVersionInfoList createLiteLoaderVersionInfoList(const QByteArray & jsonData);

	AssetInfoList createAssetInfoList(const QByteArray & jsonData);
private:
	inline void praseForgeVersionInfoListStd(QJsonObject & jsonObject, int offset, int limit, ForgeVersionInfoList & forgeVersionInfoList);
	inline void praseForgeVersionInfoListBMCLAPI(QJsonArray & jsonArray, int offset, int limit, ForgeVersionInfoList & forgeVersionInfoList);

	inline Library praseLiteLoaderVersionMetaLibrary(QJsonObject & object)const;
	inline LiteLoaderVersionMeta praseLiteLoaderVersionMeta(QJsonObject & object);
};
