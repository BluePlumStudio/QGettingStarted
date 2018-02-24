#pragma once

#include <QString>

namespace OS
{
	const QString WINDOWS("windows");
	const QString LINUX("linux");
	const QString MACOS("osx");
	const QString UNKNOWN("unknown");
}

class QGSOperatingSystem 
{
private:
	QGSOperatingSystem();
	~QGSOperatingSystem();
public:
	static QGSOperatingSystem & getInstance();

	QString getBuildAbi()const;

	QString getBuildCpuArchitecture()const;

	QString getCurrentCpuArchitecture()const;

	QString getKernelType()const;

	QString getKernelVersion()const;

	QString getMachineHostName()const;

	QString getPrettyProductName()const;

	QString getProductType()const;

	QString getProductVersion()const;

	QChar getSeparator()const;
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

	QChar mSeparator;
};
