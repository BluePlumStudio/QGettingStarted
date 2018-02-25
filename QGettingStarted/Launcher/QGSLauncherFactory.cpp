#include "QGSLauncherFactory.h"
#include "GeneralLauncher.h"

QGSLauncherFactory::QGSLauncherFactory()
{
}

QGSLauncherFactory::~QGSLauncherFactory()
{
}

ILauncher * QGSLauncherFactory::createLauncher(const QString & version, QGSGameDirectory & gameDirectory)const
{
	return new GeneralLauncher(version, gameDirectory);
}
