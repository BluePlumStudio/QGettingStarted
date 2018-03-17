#pragma once

#include <QSharedPointer>

#include "QGSILauncherStrategy.h"
#include "QGSGameDirectory.h"

class QGSLauncher
{
public:
	QGSLauncher(const GameVersion & version, QGSGameDirectory & gameDirectory);

	QGSLauncher(const QGSLauncher & right) = delete;

	QGSLauncher(QGSLauncher && right) = delete;

	QGSLauncher & operator=(const QGSLauncher & right) = delete;

	QGSLauncher & operator=(QGSLauncher && right) = delete;

	~QGSLauncher();

	virtual LauncherError::ErrorFlags generateLaunchCommand(const QGSLaunchOptions * launchOptions, QString & command);
private:
	QGSILauncherStrategy * launcherStrategy;
	const GameVersion & mVersion;
	QGSGameDirectory mGameDirectory;
};

