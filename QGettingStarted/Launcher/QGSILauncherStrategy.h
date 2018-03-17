#pragma once

#include <QString>

#include "../GameVersion/Rules.h"
#include "../GameVersion/GameVersion.h"
#include "../LaunchOptions/QGSLaunchOptionsBuilder.h"

namespace LauncherError
{
	typedef int ErrorFlags;

	static const int Ok = 0x01;
	static const int UnknownError = 0x02;
	static const int JsonLibrariesNotIncluded = 0x04;
	static const int JsonMinecraftArgumentsNot_included = 0x08;
	static const int MinecraftArgumentsVariableNotIncluded;
	static const int JavaPathNotIncluded;
	static const int NativePathNotIncluded;
	static const int PlayerNameNotIncluded;
	static const int UserTypeNotIncluded;
	static const int AuthUuidNotIncluded;
	static const int AuthAccessTokenNotIncluded;
	static const int NativesCompressError;
	static const int InvalidMemorySize;
	static const int NullPointer;
	static const int JarFileNotFound;
	static const int AssetFirectoryGenerateFailure;
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
	
	virtual LauncherError::ErrorFlags generateLaunchCommand(const GameVersion & version,
		QGSGameDirectory & gameDirectory,
		const QGSLaunchOptions * launchOptions,
		QString & command) = 0;
protected:
	bool isRulesAllowing(const Rules & rules);
private:
	inline QString praseOsVersion(QString & osVersion);
};
