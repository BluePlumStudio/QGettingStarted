#pragma once

#include <QString>
#include <QSize>

#include "../Launcher/IGameDirectory.h"
#include "IAuthenticator.h"

class ILaunchOptions 
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

protected: 
	IGameDirectory & mGameDir;
	QString mJavaPath;
	int mMaxMemory;
	int mMinMemory;
	IAuthenticator::AuthenticationInfo & mAuthenticationInfo;
	QString mJVMArguments;
	QString mWrapper;
	QString mPreCalledCommands;
	ServerInfo mServerInfo;
	QString mGameArguments;
	QSize mWindowSize;
	QString mClientToken;
	bool mFullScreen;
	int mMetaspaceSize;
	ProxyInfo mProxyInfo;
	bool mGeneratedJVMArguments;
};
