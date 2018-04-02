#pragma once

#include <QObject>
#include <QByteArray>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

#include "QGSOptifineVersionInfoList.h"

class QGSOptifineVersionInfoListFactory :public QObject
{
	Q_OBJECT

public:
	QGSOptifineVersionInfoListFactory(QObject * parent = nullptr);

	QGSOptifineVersionInfoListFactory(const QGSOptifineVersionInfoListFactory & right) = delete;

	QGSOptifineVersionInfoListFactory(QGSOptifineVersionInfoListFactory && right) = delete;

	QGSOptifineVersionInfoListFactory & operator=(const QGSOptifineVersionInfoListFactory & right) = delete;

	QGSOptifineVersionInfoListFactory & operator=(QGSOptifineVersionInfoListFactory && right) = delete;

	~QGSOptifineVersionInfoListFactory();

	QGSOptifineVersionInfoList createOptifineVersionInfoList(const QByteArray & jsonData);
};
