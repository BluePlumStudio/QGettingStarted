#pragma once

#include <QObject>
#include <QByteArray>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

#include "QGSAssetIndexInfo.h"

class QGSAssetIndexInfoFactory :public QObject
{
	Q_OBJECT

public:
	QGSAssetIndexInfoFactory(QObject * parent = nullptr);

	QGSAssetIndexInfoFactory(const QGSAssetIndexInfoFactory & right) = delete;

	QGSAssetIndexInfoFactory(QGSAssetIndexInfoFactory && right) = delete;

	QGSAssetIndexInfoFactory & operator=(const QGSAssetIndexInfoFactory & right) = delete;

	QGSAssetIndexInfoFactory & operator=(QGSAssetIndexInfoFactory && right) = delete;

	~QGSAssetIndexInfoFactory();

	QGSAssetIndexInfo createAssetIndexInfo(const QByteArray & jsonData);
};
