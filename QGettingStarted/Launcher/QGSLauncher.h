#pragma once

#include <QString>

#include "../Version/Version.h"
#include "../LaunchOptions/QGSLaunchOptionsBuilder.h"

class QGSLauncher {
public:
	enum class Error 
	{ 
		OK, UNKNOWN_ERROR, 
		JSON_LIBRARIES_NOT_INCLUDED, 
		JSON_MINECRAFT_ARGUMENTS_NOT_INCLUDED, 
		MINECRAFT_ARGUMENTS_VARIABLE_NOT_INCLUDED, 
		JAVA_PATH_NOT_INCLUDED, 
		NATIVE_PATH_NOT_INCLUDED, 
		PLAYER_NAME_NOT_INCLUDED, 
		USER_TYPE_NOT_INCLUDED, 
		XMX_AND_XMN, 
		POINTER_IS_NULL 
	};

public: 
	
	/**
	 * @param version
	 * @param launchOptions
	 * @param command
	 */
	Error generateLaunchCommand(const Version & version, const ILaunchOptions & launchOptions, QString & command);
};
