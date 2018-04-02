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
