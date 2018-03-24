#pragma once

#include <QString>
#include <QSize>

#include "QGSIAccountFactory.h"
#include "../Launcher/QGSGameDirectory.h"

class QGSServerInfo
{
public:
	QGSServerInfo(const QString & address = "", const QString & port = "25565");

	~QGSServerInfo();

	QString getAddress()const;

	QString getPort()const;

	QGSServerInfo & setAddress(const QString & address);

	QGSServerInfo & setPort(const QString & port);
private:
	QString mAddress;
	QString mPort;
};

class QGSLaunchOptions 
{
public:
	QGSLaunchOptions(QString JavaPath = "",
		int maxMemory = 512,
		int minMemory = 128,
		QGSAuthInfo authInfo = QGSAuthInfo(),
		QString JVMArguments = "",
		QString wrapper = "",
		QString preCalledCommands = "",
		QGSServerInfo serverInfo = QGSServerInfo(),
		QString gameArguments = "",
		QSize windowSize = QSize(854, 480),
		bool fullScreen = false,
		int metaspaceSize = 0,
		QNetworkProxy proxy = QNetworkProxy::NoProxy,
		bool generatedJVMArguments = true);

	QGSLaunchOptions(const QGSLaunchOptions & right) = default;

	QGSLaunchOptions(QGSLaunchOptions && right) = default;

	QGSLaunchOptions & operator=(const QGSLaunchOptions & right) = default;

	QGSLaunchOptions & operator=(QGSLaunchOptions && right) = default;

	~QGSLaunchOptions();

	QString getJavaPath()const;
	int getMaxMemory()const;
	int getMinMemory()const;
	QGSAuthInfo getAuthInfo()const;
	QString getJVMArguments()const;
	QString getWrapper()const;
	QString getPreCalledCommands()const;
	QGSServerInfo getServerInfo()const;
	QString getGameArguments()const;
	QSize getWindowSize()const;
	bool getFullScreen()const;
	int getMetaspaceSize()const;
	QNetworkProxy getProxy()const;
	bool getGeneratedJVMArguments()const;
	QString getLoggingPath()const;
	QMap<QString, QString> getCustomMinecraftArguments()const;

	QGSLaunchOptions & setJavaPath(const QString & JavaPath);
	QGSLaunchOptions & setMaxMemory(const int maxMemory);
	QGSLaunchOptions & setMinMemory(const int minMemory);
	QGSLaunchOptions & setAuthInfo(const QGSAuthInfo & authInfo);
	QGSLaunchOptions & setJVMArguments(const QString & JVMArguments);
	QGSLaunchOptions & setWrapper(const QString & wrapper);
	QGSLaunchOptions & setPreCalledCommands(const QString & preCalledCommands);
	QGSLaunchOptions & setServerInfo(const QGSServerInfo & serverInfo);
	QGSLaunchOptions & setGameArguments(const QString & gameArguments);
	QGSLaunchOptions & setWindowSize(const QSize & windowSize);
	QGSLaunchOptions & setFullScreen(const bool fullScreen);
	QGSLaunchOptions & setMetaspaceSize(const int metaspaceSize);
	QGSLaunchOptions & setProxy(const QNetworkProxy & proxy);
	QGSLaunchOptions & setGeneratedJVMArguments(const bool generatedJVMArguments);
	QGSLaunchOptions & setLoggingPath(const QString & loggingPath);
	QGSLaunchOptions & setCustomMinecraftArguments(const QMap<QString, QString> & customMinecraftArguments);
private:
	QString mJavaPath;
	int mMaxMemory;
	int mMinMemory;
	QGSAuthInfo mAuthInfo;
	QString mJVMArguments;
	QString mWrapper;
	QString mPreCalledCommands;
	QGSServerInfo mServerInfo;
	QString mGameArguments;
	QSize mWindowSize;
	bool mFullScreen;
	int mMetaspaceSize;
	QNetworkProxy mProxy;
	bool mGeneratedJVMArguments;
	QString mLoggingPath;
	QMap<QString, QString> mCustomMinecraftArguments;
};
