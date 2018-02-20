#pragma once

#include <QString>
#include <QMap>

#include "IVersionFlyweightFactory.h"
#include "QGSVersion.h"

class QGSVersionFlyweightFactory: public IVersionFlyweightFactory 
{
public: 
	
	/**
	 * @param gameDir
	 * @param versionName
	 */
	QGSVersion * createVersion(IGameDirectory & gameDir, const QString versionName);
};

