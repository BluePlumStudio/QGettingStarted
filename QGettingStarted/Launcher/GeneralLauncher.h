#pragma once

#include "ILauncher.h"

class GeneralLauncher :public ILauncher
{
public:
	GeneralLauncher(const QString & version, QGSGameDirectory & gameDirectory);

	GeneralLauncher(const GeneralLauncher & right) = delete;

	GeneralLauncher(GeneralLauncher && right) = delete;

	GeneralLauncher & operator=(const GeneralLauncher & right) = delete;

	GeneralLauncher & operator=(GeneralLauncher && right) = delete;

	virtual ~GeneralLauncher();

	Error generateLaunchCommand(const QGSLaunchOptions & launchOptions, QString & command);
private:

};
