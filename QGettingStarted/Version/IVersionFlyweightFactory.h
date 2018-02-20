#pragma once

#include <QString>
#include <QMap>

#include "IVersion.h"
#include "../Launcher/IGameDirectory.h"

class IVersionFlyweightFactory 
{
public: 
	/**
	 * @param gameDir
	 * @param versionName
	 */
	IVersion * createVersion(IGameDirectory & gameDir, const QString versionName);
	
	/**
	 * @param gameDir
	 * @param versionName
	 */
	bool containsVersion(IGameDirectory & gameDir, const QString versionName);
};
