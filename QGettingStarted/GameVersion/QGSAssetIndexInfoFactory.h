#pragma once

#include <QObject>
#include <QByteArray>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

#include "AssetIndexInfo.h"

class QGSAssetIndexInfoFactory
{
public:
	QGSAssetIndexInfoFactory();

	QGSAssetIndexInfoFactory(const QGSAssetIndexInfoFactory & right) = delete;

	QGSAssetIndexInfoFactory(QGSAssetIndexInfoFactory && right) = delete;

	QGSAssetIndexInfoFactory & operator=(const QGSAssetIndexInfoFactory & right) = delete;

	QGSAssetIndexInfoFactory & operator=(QGSAssetIndexInfoFactory && right) = delete;

	~QGSAssetIndexInfoFactory();

	AssetIndexInfo createAssetIndexInfo(const QByteArray & jsonData);
};
