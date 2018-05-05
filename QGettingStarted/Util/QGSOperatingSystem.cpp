#include <QSysInfo>
#include <QCoreApplication>

#include "QGSOperatingSystem.h"

#include <QDir>

const QString QGSOperatingSystem::WINDOWS("windows");
const QString QGSOperatingSystem::LINUX("linux");
const QString QGSOperatingSystem::MACOS("osx");
const QString QGSOperatingSystem::UNKNOWN("unknown");

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

	mSeparator = QDir::separator();

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
	if (mCurrentCpuArchitecture == QGSCpuArchitecture::ARM64 ||
		mCurrentCpuArchitecture == QGSCpuArchitecture::IA64 ||
		mCurrentCpuArchitecture == QGSCpuArchitecture::MIPS64 ||
		mCurrentCpuArchitecture == QGSCpuArchitecture::POWER64 ||
		mCurrentCpuArchitecture == QGSCpuArchitecture::X86_64)
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