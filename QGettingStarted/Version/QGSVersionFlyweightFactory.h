#pragma once

#include <QString>
#include <QMap>

#include "IVersionFlyweightFactory.h"
#include "QGSVersion.h"

class QGSVersionFlyweightFactory: public IVersionFlyweightFactory 
{
public: 
	QGSVersionFlyweightFactory();

	virtual ~QGSVersionFlyweightFactory();

	QGSVersion * createVersion(IGameDirectory & gameDir, const QString versionName);

	bool containsVersion(IGameDirectory & gameDir, const QString versionName);
private:
	QMap<QString, QGSVersion> mMapVersion;
};

