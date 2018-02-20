#include <QSysInfo>

#include "OperatingSystem.h"

OperatingSystem::OperatingSystem()
{
	mBuildAbi = QSysInfo::buildAbi();
	mBuildCpuArchitecture = QSysInfo::buildCpuArchitecture();
	mCurrentCpuArchitecture = QSysInfo::currentCpuArchitecture();
	mKernelType = QSysInfo::kernelType();
	mKernelVersion = QSysInfo::kernelVersion();
	mMachineHostName = QSysInfo::machineHostName();
	mPrettyProductName = QSysInfo::prettyProductName();
	mProductType = QSysInfo::productType();
	mProductVersion = QSysInfo::productVersion();
}

OperatingSystem::~OperatingSystem()
{

}

OperatingSystem & OperatingSystem::getInstance()
{
	static OperatingSystem instance;
	return instance;
}

QString OperatingSystem::getBuildAbi()const
{
	return mBuildAbi;
}

QString OperatingSystem::getBuildCpuArchitecture()const
{
	return mBuildCpuArchitecture;
}

QString OperatingSystem::getCurrentCpuArchitecture()const
{
	return mCurrentCpuArchitecture;
}

QString OperatingSystem::getKernelType()const
{
	return mKernelType;
}

QString OperatingSystem::getKernelVersion()const
{
	return mKernelVersion;
}

QString OperatingSystem::getMachineHostName()const
{
	return mMachineHostName;
}

QString OperatingSystem::getPrettyProductName()const
{
	return mPrettyProductName;
}

QString OperatingSystem::getProductType()const
{
	return mProductType;
}

QString OperatingSystem::getProductVersion()const
{
	return mProductVersion;
}