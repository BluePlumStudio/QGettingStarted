#pragma once

#include <QString>

#include "../GameVersion/QGSRules.h"
#include "../GameVersion/QGSGameVersion.h"
#include "../LaunchOptions/QGSLaunchOptionsBuilder.h"

namespace LauncherError
{
	typedef int ErrorFlags;

	static const int Ok = 0x01;
	static const int UnknownError = 0x02;
	static const int JsonLibrariesNotIncluded = 0x04;
	static const int JsonMinecraftArgumentsNot_included = 0x08;
	static const int MinecraftArgumentsVariableNotIncluded = 0x10;
	static const int JavaPathNotIncluded = 0x20;
	static const int NativePathNotIncluded = 0x40;
	static const int PlayerNameNotIncluded = 0x80;
	static const int UserTypeNotIncluded = 0x100;
	static const int AuthUuidNotIncluded = 0x200;
	static const int AuthAccessTokenNotIncluded = 0x400;
	static const int NativesCompressError = 0x800;
	static const int InvalidMemorySize = 0x1000;
	static const int NullPointer = 0x2000;
	static const int JarFileNotFound = 0x4000;
	static const int AssetFirectoryGenerateFailure = 0x8000;
}

class QGSILauncherStrategy 
{
public: 
	QGSILauncherStrategy();

	QGSILauncherStrategy(const QGSILauncherStrategy & right) = delete;

	QGSILauncherStrategy(QGSILauncherStrategy && right) = delete;

	QGSILauncherStrategy & operator=(const QGSILauncherStrategy & right) = delete;

	QGSILauncherStrategy & operator=(QGSILauncherStrategy && right) = delete;

	virtual ~QGSILauncherStrategy();
	
	virtual LauncherError::ErrorFlags generateLaunchCommand(const QGSGameVersion & version,
		QGSGameDirectory & gameDirectory,
		const QGSLaunchOptions * launchOptions,
		QString & command) = 0;
protected:
	bool isRulesAllowing(const QGSRules & rules);
private:
    inline QString praseOsVersion(QString osVersion);
};
