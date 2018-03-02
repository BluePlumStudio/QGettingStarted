#pragma once

#include "QGSILauncher.h"
#include "QGSGameDirectory.h"

class QGSLauncherFactory
{
public:
	QGSLauncherFactory();

	QGSLauncherFactory(const QGSLauncherFactory & right) = delete;

	QGSLauncherFactory(QGSLauncherFactory && right) = delete;

	QGSLauncherFactory & operator=(const QGSLauncherFactory & right) = delete;

	QGSLauncherFactory & operator=(QGSLauncherFactory && right) = delete;

	~QGSLauncherFactory();

	QGSILauncher * createLauncher(const QString & version, QGSGameDirectory & gameDirectory)const;

private:

};

