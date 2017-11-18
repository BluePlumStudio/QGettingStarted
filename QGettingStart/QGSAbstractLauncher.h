#pragma once

#include "QGSAbstractGameBuilder.h"
#include "../QGettingStart_Util/Exception.h"

#include <QVector>

#include <vector>

class QGSAbstractLauncher
{
public:
	class LauncherError
	{
	public:
		typedef uint ErrorFlags;
	public:
		enum Error
		{
			NO_ERROR = 0x01,
			UNKNOWN_ERROR = 0x02,
			JSON_LIBRARIES_NOT_INCLUDED = 0x04,
			JSON_MINECRAFT_ARGUMENTS_NOT_INCLUDED = 0x08,
			MINECRAFT_ARGUMENTS_VARIABLE_NOT_INCLUDED = 0x10,
			JAVA_PATH_NOT_INCLUDED = 0x20,
			NATIVE_PATH_NOT_INCLUDED = 0x30,
			PLAYER_NAME_NOT_INCLUDED = 0x40,
			USER_TYPE_NOT_INCLUDED = 0x50,
			XMX_LESS_THAN_XMN = 0x60,
			XMX_LESS_TOO_SMALL = 0x70,
			XMN_LESS_THAN_OR_EQUAL_TO_0 = 0x80,
			POINTER_IS_NULL = 0x90,
		};
	public:
		LauncherError(QString errorMessage = "", ErrorFlags launchError = Error::NO_ERROR) :
			mErrorMessage(errorMessage), mLaunchError(launchError)
		{

		}

		~LauncherError()
		{

		}

	public:
		QString mErrorMessage;
		ErrorFlags mLaunchError;
	};
public:
	enum Option
	{
		LAUNCH = 0x0001,
		LIBRARIES = 0x0002,
		LIBRARIES_MISSING = 0x0004,
		MINECRAFT_ARGUMENTS = 0x0008,
		JAVA_PATH = 0x0010,
		SYSTEM_SETTINGS = 0x0020,
	};
public:
	QGSAbstractLauncher()
	{

	}
	virtual ~QGSAbstractLauncher()
	{

	}

public:
	virtual QGSAbstractLauncher::LauncherError getLaunchString(QGSAbstractGame * game, QString & item) = 0;
};

