#pragma once

#include <QString>

namespace Natives
{
	const QString WINDOWS("windows");
	const QString LINUX("linux");
	const QString MACOS("osx");
}

class OperatingSystem 
{
private:
	OperatingSystem();
	~OperatingSystem();
public:
	static OperatingSystem & getInstance();

	QString getBuildAbi()const;

	QString getBuildCpuArchitecture()const;

	QString getCurrentCpuArchitecture()const;

	QString getKernelType()const;

	QString getKernelVersion()const;

	QString getMachineHostName()const;

	QString getPrettyProductName()const;

	QString getProductType()const;

	QString getProductVersion()const;
private: 
	QString mBuildAbi;
	QString mBuildCpuArchitecture;
	QString mCurrentCpuArchitecture;
	QString mKernelType;
	QString mKernelVersion;
	QString mMachineHostName;
	QString mPrettyProductName;
	QString mProductType;
	QString mProductVersion;
};
