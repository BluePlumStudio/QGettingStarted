#pragma once

#include "QGSIGameVersionPraseStrategy.h"

class QGSGeneralGameVersionPraseStrategy :public QGSIGameVersionPraseStrategy
{
public:
	QGSGeneralGameVersionPraseStrategy(const int minimunLaunchVersion = 0);

	QGSGeneralGameVersionPraseStrategy(const QGSGeneralGameVersionPraseStrategy & right) = default;

	QGSGeneralGameVersionPraseStrategy(QGSGeneralGameVersionPraseStrategy && right) = default;

	QGSGeneralGameVersionPraseStrategy & operator=(const QGSGeneralGameVersionPraseStrategy & right) = default;

	QGSGeneralGameVersionPraseStrategy & operator=(QGSGeneralGameVersionPraseStrategy && right) = default;

	virtual ~QGSGeneralGameVersionPraseStrategy();

	virtual void praseVersion(GameVersion & version, QJsonDocument & jsonDocument)const override;

};
