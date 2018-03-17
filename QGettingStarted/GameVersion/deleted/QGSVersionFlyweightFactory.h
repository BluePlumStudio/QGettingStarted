#pragma once

#include <QString>
#include <QMap>

#include "IVersionFlyweightFactory.h"
#include "QGSVersion.h"

class QGSVersionFlyweightFactory: public IVersionFlyweightFactory 
{
public: 
	QGSVersionFlyweightFactory();

	QGSVersionFlyweightFactory(const QGSVersionFlyweightFactory & right) = default;

	QGSVersionFlyweightFactory(QGSVersionFlyweightFactory && right) = default;

	QGSVersionFlyweightFactory & operator=(const QGSVersionFlyweightFactory & right) = default;

	QGSVersionFlyweightFactory & operator=(QGSVersionFlyweightFactory && right) = default;

	virtual ~QGSVersionFlyweightFactory();

	QGSVersion * createVersion(IGameDirectory & gameDir, const QString versionName);

	bool containsVersion(IGameDirectory & gameDir, const QString versionName);
private:
	QMap<QString, QGSVersion> mMapVersions;
};

