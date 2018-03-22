#include "QGSLauncher.h"
#include "QGSGeneralLauncherStrategy.h"

QGSLauncher::QGSLauncher(const QGSGameVersion & version, QGSGameDirectory & gameDirectory) :mVersion(version), mGameDirectory(gameDirectory)
{
	launcherStrategy = new QGSGeneralLauncherStrategy;
}

QGSLauncher::~QGSLauncher()
{
	if (!launcherStrategy)
	{
		delete launcherStrategy;
	}
}

LauncherError::ErrorFlags QGSLauncher::generateLaunchCommand(const QGSLaunchOptions * launchOptions, QString & command)
{
	return launcherStrategy->generateLaunchCommand(mVersion, mGameDirectory, launchOptions, command);
}
