#pragma once

#include <QString>
#include <QJsonDocument>

#include "../GameVersion/QGSGameVersion.h"

class QGSIGameVersionPraseStrategy 
{
public:
	QGSIGameVersionPraseStrategy(const int minimunLaunchVersion = 0);

	QGSIGameVersionPraseStrategy(const QGSIGameVersionPraseStrategy & right) = default;

	QGSIGameVersionPraseStrategy(QGSIGameVersionPraseStrategy && right) = default;

	QGSIGameVersionPraseStrategy & operator=(const QGSIGameVersionPraseStrategy & right) = default;

	QGSIGameVersionPraseStrategy & operator=(QGSIGameVersionPraseStrategy && right) = default;

	virtual ~QGSIGameVersionPraseStrategy();

	virtual void praseVersion(QGSGameVersion & version, QJsonDocument & jsonDocument)const = 0;

protected: 
	int mMinimunLaunchVersion;
};
