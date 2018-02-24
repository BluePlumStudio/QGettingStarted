#pragma once

#include <QSharedPointer>

#include "GeneralVersionPraseStrategy.h"

class QGSVersionPraseStrategyFactory
{
public:
	QGSVersionPraseStrategyFactory();

	QGSVersionPraseStrategyFactory(const QGSVersionPraseStrategyFactory & right) = delete;

	QGSVersionPraseStrategyFactory(QGSVersionPraseStrategyFactory && right) = delete;

	QGSVersionPraseStrategyFactory & operator=(const QGSVersionPraseStrategyFactory & right) = delete;

	QGSVersionPraseStrategyFactory & operator=(QGSVersionPraseStrategyFactory && right) = delete;

	~QGSVersionPraseStrategyFactory();

	const IVersionPraseStrategy & getVersionPraseStrategy(QJsonDocument & jsonDocument)const;

	bool containsVersionPraseStrategy(const int minimumLauncherVersion)const;

private:
	QMap<int, QSharedPointer<IVersionPraseStrategy>> mMapVersionPraseStrategys;
};

