#pragma once

#include "QGSILauncherStrategy.h"

class QGSGeneralLauncherStrategy :public QGSILauncherStrategy
{
public:
	QGSGeneralLauncherStrategy();

	QGSGeneralLauncherStrategy(const QGSGeneralLauncherStrategy & right) = delete;

	QGSGeneralLauncherStrategy(QGSGeneralLauncherStrategy && right) = delete;

	QGSGeneralLauncherStrategy & operator=(const QGSGeneralLauncherStrategy & right) = delete;

	QGSGeneralLauncherStrategy & operator=(QGSGeneralLauncherStrategy && right) = delete;

	virtual ~QGSGeneralLauncherStrategy();

	virtual LauncherError::ErrorFlags generateLaunchCommand(const QGSGameVersion & version,
		QGSGameDirectory & gameDirectory,
		const QGSLaunchOptions * launchOptions,
		QString & command)override;
private:

};
