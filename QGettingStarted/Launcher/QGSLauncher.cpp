#include "QGSLauncher.h"
#include "QGSGeneralLauncherStrategy.h"

QGSLauncher::QGSLauncher(const Version & version, QGSGameDirectory & gameDirectory) :mVersion(version), mGameDirectory(gameDirectory)
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

QGSILauncherStrategy::Error QGSLauncher::generateLaunchCommand(const QGSLaunchOptions * launchOptions, QString & command)
{
	return launcherStrategy->generateLaunchCommand(mVersion, mGameDirectory, launchOptions, command);
}
