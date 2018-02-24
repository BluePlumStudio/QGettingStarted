#pragma once

#include <QString>
#include <QMap>

#include "IVersion.h"
#include "../Launcher/IGameDirectory.h"

class IVersionFlyweightFactory 
{
public:
	IVersionFlyweightFactory();

	IVersionFlyweightFactory(const IVersionFlyweightFactory & right) = default;

	IVersionFlyweightFactory(IVersionFlyweightFactory && right) = default;

	IVersionFlyweightFactory & operator=(const IVersionFlyweightFactory & right) = default;

	IVersionFlyweightFactory & operator=(IVersionFlyweightFactory && right) = default;

	virtual ~IVersionFlyweightFactory();

	virtual IVersion * createVersion(IGameDirectory & gameDir, const QString versionName) = 0;
	
	virtual bool containsVersion(IGameDirectory & gameDir, const QString versionName) = 0;
private:

};
