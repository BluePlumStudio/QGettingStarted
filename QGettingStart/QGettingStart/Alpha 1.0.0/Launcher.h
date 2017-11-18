#pragma once

#include "GameBuilder.h"

#include <QVector>

#include <vector>

enum Option
{
	LAUNCH,
	LIBRARIES,
	LIBRARIES_MISSING,
	MINECRAFT_ARGUMENTS
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
	virtual QVector<QString>	getStringVector(Game * game, Option option) = 0;
	virtual QString				getString(Game * game, Option option) = 0;
};

