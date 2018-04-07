#pragma once

#include <QString>
#include <QObject>

namespace OS
{
	const QString WINDOWS("windows");
	const QString LINUX("linux");
	const QString MACOS("osx");
	const QString UNKNOWN("unknown");
}

namespace CpuArchitecture
{
	const QString ARM("arm");
	const QString ARM64("arm64");
	const QString I386("i386");
	const QString IA64("ia64");
	const QString MIPS("mips");
	const QString MIPS64("mips64");
	const QString POWER("power");
	const QString POWER64("power64");
	const QString SPARC("sparc");
	const QString SPARCV9("sparcv9");
	const QString X86_64("x86_64");
}

class QGSOperatingSystem :public QObject
{
	Q_OBJECT

private:
	QGSOperatingSystem(QObject * parent = nullptr);

	QGSOperatingSystem(const QGSOperatingSystem & right) = default;

	QGSOperatingSystem(QGSOperatingSystem && right) = default;

	QGSOperatingSystem & operator=(const QGSOperatingSystem & right) = default;

	QGSOperatingSystem & operator=(QGSOperatingSystem && right) = default;

	virtual ~QGSOperatingSystem();
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

	quint8 getCurrentCpuArchitectureNumber()const;

	QChar getSeperator()const;
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
