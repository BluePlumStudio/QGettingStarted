#include "IVersionFlyweightFactory.h"
/**
 * @param gameDir
 * @param versionName
 * @return IVersion *
 */
IVersion * IVersionFlyweightFactory::createVersion(IGameDirectory & gameDir, const QString versionName) 
{
    return nullptr;
}

/**
 * @param gameDir
 * @param versionName
 * @return bool
 */
bool IVersionFlyweightFactory::containsVersion(IGameDirectory & gameDir, const QString versionName) 
{
    return false;
}