#pragma once

#include "Launcher.h"

#include "GettingStart/GSLauncher.h"

#include "QGSGameBuilder.h"
#include "QGSGame.h"

#include <string>

class QGSLauncher:public Launcher
{
public:
	QGSLauncher();
	virtual ~QGSLauncher();
public:
	virtual QVector<QString>	getStringVector(Game * game, Option option);
	virtual QString				getString(Game * game, Option option);

private:
	gs::GSLauncher mLauncher;
};

