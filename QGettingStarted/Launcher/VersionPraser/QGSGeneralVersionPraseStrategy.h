#pragma once

#include "QGSIVersionPraseStrategy.h"

class QGSGeneralVersionPraseStrategy :public QGSIVersionPraseStrategy
{
public:
	QGSGeneralVersionPraseStrategy(const int minimunLaunchVersion = 0);

	QGSGeneralVersionPraseStrategy(const QGSGeneralVersionPraseStrategy & right) = default;

	QGSGeneralVersionPraseStrategy(QGSGeneralVersionPraseStrategy && right) = default;

	QGSGeneralVersionPraseStrategy & operator=(const QGSGeneralVersionPraseStrategy & right) = default;

	QGSGeneralVersionPraseStrategy & operator=(QGSGeneralVersionPraseStrategy && right) = default;

	virtual ~QGSGeneralVersionPraseStrategy();

	virtual void praseVersion(Version & version, QJsonDocument & jsonDocument)const override;

};
