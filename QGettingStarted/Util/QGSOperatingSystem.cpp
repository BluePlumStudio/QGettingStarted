#include <QSysInfo>

#include "QGSOperatingSystem.h"

QGSOperatingSystem::QGSOperatingSystem()
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

#ifdef Q_OS_WIN
	mSeparator = '\\';
#elif
	mSeparator = '/';
#endif
}

QGSOperatingSystem::~QGSOperatingSystem()
{

}

QGSOperatingSystem & QGSOperatingSystem::getInstance()
{
	static QGSOperatingSystem instance;
	return instance;
}

QString QGSOperatingSystem::getBuildAbi()const
{
	return mBuildAbi;
}

QString QGSOperatingSystem::getBuildCpuArchitecture()const
{
	return mBuildCpuArchitecture;
}

QString QGSOperatingSystem::getCurrentCpuArchitecture()const
{
	return mCurrentCpuArchitecture;
}

QString QGSOperatingSystem::getKernelType()const
{
	return mKernelType;
}

QString QGSOperatingSystem::getKernelVersion()const
{
	return mKernelVersion;
}

QString QGSOperatingSystem::getMachineHostName()const
{
	return mMachineHostName;
}

QString QGSOperatingSystem::getPrettyProductName()const
{
	return mPrettyProductName;
}

QString QGSOperatingSystem::getProductType()const
{
	return mProductType;
}

QString QGSOperatingSystem::getProductVersion()const
{
	return mProductVersion;
}

QChar QGSOperatingSystem::getSeparator()const
{
	return mSeparator;
}