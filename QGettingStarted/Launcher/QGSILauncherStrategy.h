#pragma once

#include <QString>

#include "../GameVersion/QGSRules.h"
#include "../GameVersion/QGSGameVersion.h"
#include "../LaunchOptions/QGSLaunchOptionsBuilder.h"

namespace QGSLauncherError
{
	typedef int ErrorFlags;

	static const int Ok = 0x01;
	static const int ErrorUnknown = 0x02;
	static const int WarningJavaPathNotIncluded = 0x04;
	static const int WarningNativePathNotIncluded = 0x08;
	static const int WarningNativesCompressError = 0x10;
	static const int WarningAssetDirectoryGenerationFailure = 0x20;
	static const int ErrorUserTypeNotIncluded = 0x40;
	static const int ErrorAuthUuidNotIncluded = 0x80;
	static const int ErrorAuthAccessTokenNotIncluded = 0x100;
	static const int ErrorPlayerNameNotIncluded = 0x200;
	static const int ErrorNullPointer = 0x400;
	static const int ErrorJarFileNotFound = 0x800;
}

/**

* @brief Æô¶¯Æ÷²ßÂÔ£¨³éÏó£©

*/
class QGSILauncherStrategy 
{
public: 
	QGSILauncherStrategy();

	QGSILauncherStrategy(const QGSILauncherStrategy & right) = delete;

	QGSILauncherStrategy(QGSILauncherStrategy && right) = delete;

	QGSILauncherStrategy & operator=(const QGSILauncherStrategy & right) = delete;

	QGSILauncherStrategy & operator=(QGSILauncherStrategy && right) = delete;

	virtual ~QGSILauncherStrategy();
	
	virtual QGSLauncherError::ErrorFlags generateLaunchCommand(const QGSGameVersion & version,
		QGSGameDirectory & gameDirectory,
		const QGSLaunchOptions * launchOptions,
		QString & command) = 0;
protected:
	bool isRulesAllowing(const QGSRules & rules);
private:
    inline QString praseOsVersion(QString osVersion);
};
