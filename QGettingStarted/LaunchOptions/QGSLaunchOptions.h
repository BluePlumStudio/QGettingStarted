#pragma once

#include <QString>
#include <QSize>

#include "IAccountFactory.h"
#include "../Launcher/QGSGameDirectory.h"

class QGSLaunchOptions 
{
public:
	class ProxyInfo
	{
	private:
		QString mAddress;
		QString mPort;
		QString mUser;
		QString mPassword;
	};

	class ServerInfo
	{
	public:
		QString address;
		QString port;
	};
public:
	QGSLaunchOptions(QString JavaPath = "",
		int maxMemory = 512,
		int minMemory = 128,
		AuthInfo authInfo = AuthInfo(),
		QString JVMArguments = "",
		QString wrapper = "",
		QString preCalledCommands = "",
		ServerInfo serverInfo = ServerInfo(),
		QString gameArguments = "",
		QSize windowSize = QSize(854, 480),
		bool fullScreen = false,
		int metaspaceSize = 0,
		ProxyInfo proxyInfo = ProxyInfo(),
		bool generatedJVMArguments = true);

	QGSLaunchOptions(const QGSLaunchOptions & right) = default;

	QGSLaunchOptions(QGSLaunchOptions && right) = default;

	QGSLaunchOptions & operator=(const QGSLaunchOptions & right) = default;

	QGSLaunchOptions & operator=(QGSLaunchOptions && right) = default;

	~QGSLaunchOptions();

	QString getJavaPath()const;
	int getMaxMemory()const;
	int getMinMemory()const;
	AuthInfo getAuthInfo()const;
	QString getJVMArguments()const;
	QString getWrapper()const;
	QString getPreCalledCommands()const;
	ServerInfo getServerInfo()const;
	QString getGameArguments()const;
	QSize getWindowSize()const;
	bool getFullScreen()const;
	int getMetaspaceSize()const;
	ProxyInfo getProxyInfo()const;
	bool getGeneratedJVMArguments()const;

	QGSLaunchOptions & setJavaPath(const QString & javaPath);
	QGSLaunchOptions & setMaxMemory(const int maxMemory);
	QGSLaunchOptions & setMinMemory(const int minMemory);
	QGSLaunchOptions & setAuthInfo(const AuthInfo & authInfo);
	QGSLaunchOptions & setJVMArguments(const QString & JVMArguments);
	QGSLaunchOptions & setWrapper(const QString & wrapper);
	QGSLaunchOptions & setPreCalledCommands(const QString & preCalledCommands);
	QGSLaunchOptions & setServerInfo(const ServerInfo & serverInfo);
	QGSLaunchOptions & setGameArguments(const QString & gameArguments);
	QGSLaunchOptions & setWindowSize(const QSize & windowSize);
	QGSLaunchOptions & setFullScreen(const bool fullScreen);
	QGSLaunchOptions & setMetaspaceSize(const int metaspaceSize);
	QGSLaunchOptions & setProxyInfo(const ProxyInfo & proxyInfo);
	QGSLaunchOptions & setGeneratedJVMArguments(const bool generatedJVMArguments);
private: 
	QString mJavaPath;
	int mMaxMemory;
	int mMinMemory;
	AuthInfo mAuthInfo;
	QString mJVMArguments;
	QString mWrapper;
	QString mPreCalledCommands;
	ServerInfo mServerInfo;
	QString mGameArguments;
	QSize mWindowSize;
	bool mFullScreen;
	int mMetaspaceSize;
	ProxyInfo mProxyInfo;
	bool mGeneratedJVMArguments;
};
