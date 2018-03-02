#pragma once

#include "QGSILauncher.h"

class GeneralLauncher :public QGSILauncher
{
public:
	GeneralLauncher(const QString version, QGSGameDirectory & gameDirectory);

	GeneralLauncher(const GeneralLauncher & right) = delete;

	GeneralLauncher(GeneralLauncher && right) = delete;

	GeneralLauncher & operator=(const GeneralLauncher & right) = delete;

	GeneralLauncher & operator=(GeneralLauncher && right) = delete;

	virtual ~GeneralLauncher();

	virtual Error generateLaunchCommand(const QGSLaunchOptions * launchOptions, QString & command)override;
private:

};
