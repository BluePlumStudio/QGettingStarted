#pragma once

#include <QString>

#include "../Version/Rules.h"
#include "../Version/Version.h"
#include "../LaunchOptions/QGSLaunchOptionsBuilder.h"

class QGSILauncherStrategy 
{
public:
	enum class Error 
	{ 
		OK, 
		UNKNOWN_ERROR, 
		JSON_LIBRARIES_NOT_INCLUDED, 
		JSON_MINECRAFT_ARGUMENTS_NOT_INCLUDED, 
		MINECRAFT_ARGUMENTS_VARIABLE_NOT_INCLUDED, 
		JAVA_PATH_NOT_INCLUDED, 
		NATIVE_PATH_NOT_INCLUDED, 
		PLAYER_NAME_NOT_INCLUDED, 
		USER_TYPE_NOT_INCLUDED, 
		XMX_AND_XMN, 
		POINTER_IS_NULL,
		JAR_FILE_NOT_FOUND
	};

public: 
	QGSILauncherStrategy();

	QGSILauncherStrategy(const QGSILauncherStrategy & right) = delete;

	QGSILauncherStrategy(QGSILauncherStrategy && right) = delete;

	QGSILauncherStrategy & operator=(const QGSILauncherStrategy & right) = delete;

	QGSILauncherStrategy & operator=(QGSILauncherStrategy && right) = delete;

	virtual ~QGSILauncherStrategy();
	
	virtual Error generateLaunchCommand(const Version & version,
		QGSGameDirectory & gameDirectory,
		const QGSLaunchOptions * launchOptions,
		QString & command) = 0;
protected:
	bool isRulesAllowing(const Rules & rules);
private:
	inline QString praseOsVersion(QString & osVersion);
};
