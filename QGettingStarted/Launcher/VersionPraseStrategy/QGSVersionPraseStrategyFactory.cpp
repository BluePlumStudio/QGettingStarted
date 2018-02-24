#include <QJsonObject>

#include "QGSVersionPraseStrategyFactory.h"

QGSVersionPraseStrategyFactory::QGSVersionPraseStrategyFactory()
{
	mMapVersionPraseStrategys[0] = QSharedPointer<IVersionPraseStrategy>(new GeneralVersionPraseStrategy(0));
}

QGSVersionPraseStrategyFactory::~QGSVersionPraseStrategyFactory()
{
}

const IVersionPraseStrategy & QGSVersionPraseStrategyFactory::getVersionPraseStrategy(QJsonDocument & jsonDocument)const
{
	QJsonObject object = jsonDocument.object();
	int minimumLauncherVersion =
		object.contains("minimumLauncherVersion") ?
		object.value("minimumLauncherVersion").toInt() : 0;

	if(!containsVersionPraseStrategy(minimumLauncherVersion))
	{
		minimumLauncherVersion = 0;
	}
	
	return *(mMapVersionPraseStrategys[minimumLauncherVersion]);
}

bool QGSVersionPraseStrategyFactory::containsVersionPraseStrategy(const int minimumLauncherVersion)const
{
	return mMapVersionPraseStrategys.contains(minimumLauncherVersion);
}