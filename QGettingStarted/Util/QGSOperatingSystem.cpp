#include <QSysInfo>

#include "QGSOperatingSystem.h"

namespace CpuArchitecture
{
	const QString ARM{ "arm" };
	const QString ARM64{ "arm64" };
	const QString I386{ "i386" };
	const QString IA64{ "ia64" };
	const QString MIPS{ "mips" };
	const QString MIPS64{ "mips64" };
	const QString POWER{ "power" };
	const QString POWER64{ "power64" };
	const QString SPARC{ "sparc" };
	const QString SPARCV9{ "sparcv9" };
	const QString X86_64{ "x86_64" };
}

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

QChar QGSOperatingSystem::getSeparator()const
{
	return mSeparator;
}