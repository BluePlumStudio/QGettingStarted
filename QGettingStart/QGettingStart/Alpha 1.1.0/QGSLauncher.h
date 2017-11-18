#pragma once

#include "Launcher.h"

#include "GettingStart/GSLauncher.h"

#include "QGSGameBuilder.h"
#include "QGSGame.h"

#include <string>

#include <QDir>

class QGSLauncher:public Launcher
{
public:
	QGSLauncher();
	virtual ~QGSLauncher();
public:
	virtual QVector<QString>	getStringVector(Game * game, Option option, QString arg = "");
	virtual QString				getString(Game * game, Option option, QString arg = "");

	static bool getJavaPathVector(QVector<QString> & vector, QString baseDirectory);

private:
	gs::GSLauncher mLauncher;
};

