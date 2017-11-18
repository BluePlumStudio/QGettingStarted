#pragma once

#include "QGSAbstractLauncher.h"

//#include "GettingStart/GSLauncher.h"

#include "QGSGameBuilder.h"
#include "QGSGame.h"
#include "QGSUtil.h"

#include <string>

#include <QDir>
#include <QSettings>
#include <QStringList>
#include <QSysInfo>
#include <QDebug>



class QGSLauncher:public QGSAbstractLauncher
{
	
public:
	QGSLauncher();
	virtual ~QGSLauncher();
public:
	virtual QGSAbstractLauncher::LauncherError getLaunchString(QGSAbstractGame * game, QString & item);
public:

private:
	//gs::GSLauncher mLauncher;
};

