#include "QGSLauncher.h"
#include "QGSGeneralLauncherStrategy.h"

QGSLauncher::QGSLauncher()
{
}

QGSLauncher::~QGSLauncher()
{

}

LauncherError::ErrorFlags QGSLauncher::generateLaunchCommand(const QGSGameVersion & version, QGSGameDirectory & gameDirectory, const QGSLaunchOptions * launchOptions, QString & command)
{
	QGSGeneralLauncherStrategy launcherStrategy;

	return launcherStrategy.generateLaunchCommand(version, gameDirectory, launchOptions, command);
}