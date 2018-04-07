#include <QSysInfo>
#include <QCoreApplication>

#include "QGSOperatingSystem.h"

QGSOperatingSystem::QGSOperatingSystem(QObject * parent) :QObject(parent)
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
	static QGSOperatingSystem instance(QCoreApplication::instance());
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

quint8 QGSOperatingSystem::getCurrentCpuArchitectureNumber() const
{
	if (mCurrentCpuArchitecture == CpuArchitecture::ARM64 ||
		mCurrentCpuArchitecture == CpuArchitecture::IA64 ||
		mCurrentCpuArchitecture == CpuArchitecture::MIPS64 ||
		mCurrentCpuArchitecture == CpuArchitecture::POWER64 ||
		mCurrentCpuArchitecture == CpuArchitecture::X86_64)
	{
		return 64;
	}
	else
	{
		return 32;
	}
}

QChar QGSOperatingSystem::getSeperator()const
{
	return mSeparator;
}