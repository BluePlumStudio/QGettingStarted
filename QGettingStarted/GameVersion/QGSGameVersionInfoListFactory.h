#pragma once

#include <QObject>
#include <QByteArray>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

#include "QGSGameVersionInfoList.h"

class QGSGameVersionInfoListFactory :public QObject
{
	Q_OBJECT

public:
	QGSGameVersionInfoListFactory(QObject * parent = nullptr);

	QGSGameVersionInfoListFactory(const QGSGameVersionInfoListFactory & right) = delete;

	QGSGameVersionInfoListFactory(QGSGameVersionInfoListFactory && right) = delete;

	QGSGameVersionInfoListFactory & operator=(const QGSGameVersionInfoListFactory & right) = delete;

	QGSGameVersionInfoListFactory & operator=(QGSGameVersionInfoListFactory && right) = delete;

	~QGSGameVersionInfoListFactory();

	QGSGameVersionInfoList createGameVersionInfoList(const QByteArray & jsonData);
};
