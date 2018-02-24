#include "QGSVersionFlyweightFactory.h"

QGSVersionFlyweightFactory::QGSVersionFlyweightFactory()
{

}

QGSVersionFlyweightFactory::~QGSVersionFlyweightFactory()
{

}

QGSVersion * QGSVersionFlyweightFactory::createVersion(IGameDirectory & gameDir, const QString versionName) 
{
    return nullptr;
}

bool QGSVersionFlyweightFactory::containsVersion(IGameDirectory & gameDir, const QString versionName)
{
	return true;
}