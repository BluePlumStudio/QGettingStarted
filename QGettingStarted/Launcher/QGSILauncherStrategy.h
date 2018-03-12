#pragma once

#include <QString>

#include "../Version/Rules.h"
#include "../Version/Version.h"
#include "../LaunchOptions/QGSLaunchOptionsBuilder.h"

namespace LauncherError
{
	typedef int ErrorFlags;

	const static int OK = 0x01;
	const static int UNKNOWN_ERROR = 0x02;
	const static int JSON_LIBRARIES_NOT_INCLUDED = 0x04;
	const static int JSON_MINECRAFT_ARGUMENTS_NOT_INCLUDED = 0x08;
	const static int MINECRAFT_ARGUMENTS_VARIABLE_NOT_INCLUDED;
	const static int JAVA_PATH_NOT_INCLUDED;
	const static int NATIVE_PATH_NOT_INCLUDED;
	const static int PLAYER_NAME_NOT_INCLUDED;
	const static int USER_TYPE_NOT_INCLUDED;
	const static int NATIVES_COMPRESS_ERROR;
	const static int XMX_AND_XMN;
	const static int POINTER_IS_NULL;
	const static int JAR_FILE_NOT_FOUND;
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
	
	virtual LauncherError::ErrorFlags generateLaunchCommand(const Version & version,
		QGSGameDirectory & gameDirectory,
		const QGSLaunchOptions * launchOptions,
		QString & command) = 0;
protected:
	bool isRulesAllowing(const Rules & rules);
private:
	inline QString praseOsVersion(QString & osVersion);
};
