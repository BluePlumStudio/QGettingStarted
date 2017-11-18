#pragma once

#include "GameBuilder.h"

#include <QVector>

#include <vector>

typedef int OptionFlags;

enum Option
{
	LAUNCH = 0x0001,
	LIBRARIES = 0x0002,
	LIBRARIES_MISSING = 0x0004,
	MINECRAFT_ARGUMENTS = 0x0008,
	JAVA_PATH = 0x0010,
	SYSTEM_SETTINGS = 0x0020,
};



class Launcher
{
public:
	Launcher()
	{

	}
	virtual ~Launcher()
	{

	}

public:
	virtual QVector<QString>	getStringVector(Game * game, OptionFlags option, QString arg = "") = 0;
	virtual QString				getString(Game * game, OptionFlags option, QString arg = "") = 0;
};

