#pragma once

#include "Launcher.h"

#include "GettingStart/GSLauncher.h"

#include "QGSGameBuilder.h"
#include "QGSGame.h"

#include <string>

#include <QDir>
#include <QSettings>
#include <QStringList>
#include <QSysInfo>
#include <QDebug>

class QGSLauncher:public Launcher
{
public:
	QGSLauncher();
	virtual ~QGSLauncher();
public:
	virtual QVector<QString>	getStringVector(Game * game, OptionFlags option, QString arg = "");
	virtual QString				getString(Game * game, OptionFlags option, QString arg = "");

	static bool getJavaPathVectorFromStorage(QVector<QString> & vector, QString baseDirectory);
	static bool getJavaPathVectorFromSystemSettings(QVector<QString> & vector);

private:
	gs::GSLauncher mLauncher;
};

