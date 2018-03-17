#pragma once

#include <QObject>
#include <QByteArray>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

#include "GameVersionInfoList.h"

class QGSGameVersionInfoListFactory
{
public:
	QGSGameVersionInfoListFactory();

	QGSGameVersionInfoListFactory(const QGSGameVersionInfoListFactory & right) = delete;

	QGSGameVersionInfoListFactory(QGSGameVersionInfoListFactory && right) = delete;

	QGSGameVersionInfoListFactory & operator=(const QGSGameVersionInfoListFactory & right) = delete;

	QGSGameVersionInfoListFactory & operator=(QGSGameVersionInfoListFactory && right) = delete;

	~QGSGameVersionInfoListFactory();

	GameVersionInfoList createGameVersionInfoList(const QByteArray & jsonData);
};
