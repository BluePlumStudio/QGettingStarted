#pragma once

#include <QString>

#include "../Version/Rules.h"
#include "../Version/Version.h"
#include "../LaunchOptions/QGSLaunchOptionsBuilder.h"

class QGSILauncher 
{
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
		POINTER_IS_NULL,
		JAR_FILE_NOT_FOUND
	};

public: 
	QGSILauncher(const QString version, QGSGameDirectory & gameDirectory);

	QGSILauncher(const QGSILauncher & right) = delete;

	QGSILauncher(QGSILauncher && right) = delete;

	QGSILauncher & operator=(const QGSILauncher & right) = delete;

	QGSILauncher & operator=(QGSILauncher && right) = delete;

	virtual ~QGSILauncher();
	
	virtual Error generateLaunchCommand(const QGSLaunchOptions & launchOptions, QString & command) = 0;
protected:
	bool isRulesAllowing(const Rules & rules);
private:
	inline QString praseOsVersion(QString & osVersion);
protected:
	QString mVersion;
	QGSGameDirectory & mGameDirectory;
};
