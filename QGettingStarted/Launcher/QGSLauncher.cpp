#include "QGSLauncher.h"
#include "QGSGeneralLauncherStrategy.h"

QGSLauncher::QGSLauncher(QObject * parent) :QObject(parent)
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