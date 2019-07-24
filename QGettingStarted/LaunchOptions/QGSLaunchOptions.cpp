#include "QGSLaunchOptions.h"

QGSServerInfo::QGSServerInfo(const QString & address, const QString & port)
	:mAddress(address), mPort(port)
{
	if (!QMetaType::isRegistered(QMetaType::type("QGSServerInfo")))
	{
		qRegisterMetaType<QGSServerInfo>("QGSServerInfo");
	}
}

QGSServerInfo::~QGSServerInfo()
{

}

QString QGSServerInfo::getAddress() const
{
	return mAddress;
}

QString QGSServerInfo::getPort() const
{
	return mPort;
}

QGSServerInfo & QGSServerInfo::setAddress(const QString & address)
{
	mAddress = address;
	return *this;
}

QGSServerInfo & QGSServerInfo::setPort(const QString & port)
{
	mPort = port;
	return *this;
}

/**/

QGSLaunchOptions::QGSLaunchOptions(
	QString JavaPath,
	int maxMemory,
	int minMemory,
	QGSAuthInfo authInfo,
	QString JVMArguments,
	QString wrapper,
	QString preCalledCommands,
	QGSServerInfo serverInfo,
	QString gameArguments,
	QSize windowSize,
	bool fullScreen,
	int metaspaceSize,
	QNetworkProxy proxy,
	bool generatedJVMArguments)

	:mJavaPath(JavaPath),
	mMaxMemory(maxMemory),
	mMinMemory(minMemory),
	mAuthInfo(authInfo),
	mJVMArguments(JVMArguments),
	mWrapper(wrapper),
	mPreCalledCommands(preCalledCommands),
	mServerInfo(serverInfo),
	mGameArguments(gameArguments),
	mWindowSize(windowSize),
	mMetaspaceSize(metaspaceSize),
	mProxy(proxy),
	mGeneratedJVMArguments(generatedJVMArguments)
{
	if (!QMetaType::isRegistered(QMetaType::type("QGSLaunchOptions")))
	{
		qRegisterMetaType<QGSLaunchOptions>("QGSLaunchOptions");
	}
}

QGSLaunchOptions::~QGSLaunchOptions()
{
}

QString QGSLaunchOptions::getJavaPath()const
{
	return mJavaPath;
}

int QGSLaunchOptions::getMaxMemory()const
{
	return mMaxMemory;
}

int QGSLaunchOptions::getMinMemory()const
{
	return mMinMemory;
}

QGSAuthInfo QGSLaunchOptions::getAuthInfo()const
{
	return mAuthInfo;
}

QString QGSLaunchOptions::getJVMArguments()const
{
	return mJVMArguments;
}

QString QGSLaunchOptions::getWrapper()const
{
	return mWrapper;
}

QString QGSLaunchOptions::getPreCalledCommands()const
{
	return mPreCalledCommands;
}

QGSServerInfo QGSLaunchOptions::getServerInfo()const
{
	return mServerInfo;
}

QString QGSLaunchOptions::getGameArguments()const
{
	return mGameArguments;
}

QSize QGSLaunchOptions::getWindowSize()const
{
	return mWindowSize;
}

bool QGSLaunchOptions::getFullScreen()const
{
	return mFullScreen;
}

int QGSLaunchOptions::getMetaspaceSize()const
{
	return mMetaspaceSize;
}

QNetworkProxy QGSLaunchOptions::getProxy()const
{
	return mProxy;
}

bool QGSLaunchOptions::getGeneratedJVMArguments()const
{
	return mGeneratedJVMArguments;
}
QString QGSLaunchOptions::getLoggingPath() const
{
	return mLoggingPath;
}

QMap<QString, QString> QGSLaunchOptions::getCustomMinecraftArguments() const
{
	return mCustomMinecraftArguments;
}

//

QGSLaunchOptions & QGSLaunchOptions::setJavaPath(const QString & JavaPath)
{
	mJavaPath = JavaPath;
	return *this;
}

QGSLaunchOptions & QGSLaunchOptions::setMaxMemory(const int maxMemory)
{
	mMaxMemory = maxMemory;
	return *this;
}

QGSLaunchOptions & QGSLaunchOptions::setMinMemory(const int minMemory)
{
	mMinMemory = minMemory;
	return *this;
}

QGSLaunchOptions & QGSLaunchOptions::setAuthInfo(const QGSAuthInfo & authInfo)
{
	mAuthInfo = authInfo;
	return *this;
}

QGSLaunchOptions & QGSLaunchOptions::setJVMArguments(const QString & JVMArguments)
{
	mJVMArguments = JVMArguments;
	return *this;
}

QGSLaunchOptions & QGSLaunchOptions::setWrapper(const QString & wrapper)
{
	mWrapper = wrapper;
	return *this;
}

QGSLaunchOptions & QGSLaunchOptions::setPreCalledCommands(const QString & preCalledCommands)
{
	mPreCalledCommands = preCalledCommands;
	return *this;
}

QGSLaunchOptions & QGSLaunchOptions::setServerInfo(const QGSServerInfo & serverInfo)
{
	mServerInfo = serverInfo;
	return *this;
}

QGSLaunchOptions & QGSLaunchOptions::setGameArguments(const QString & gameArguments)
{
	mGameArguments = gameArguments;
	return *this;
}

QGSLaunchOptions & QGSLaunchOptions::setWindowSize(const QSize & windowSize)
{
	mWindowSize = windowSize;
	return *this;
}

QGSLaunchOptions & QGSLaunchOptions::setFullScreen(const bool fullScreen)
{
	mFullScreen = fullScreen;
	return *this;
}

QGSLaunchOptions & QGSLaunchOptions::setMetaspaceSize(const int metaspaceSize)
{
	mMetaspaceSize = metaspaceSize;;
	return *this;
}

QGSLaunchOptions & QGSLaunchOptions::setProxy(const QNetworkProxy & proxy)
{
	mProxy = proxy;
	return *this;
}

QGSLaunchOptions & QGSLaunchOptions::setGeneratedJVMArguments(const bool generatedJVMArguments)
{
	mGeneratedJVMArguments = generatedJVMArguments;
	return *this;
}

QGSLaunchOptions & QGSLaunchOptions::setLoggingPath(const QString & loggingPath)
{
	mLoggingPath = loggingPath;
	return *this;
}

QGSLaunchOptions & QGSLaunchOptions::setCustomMinecraftArguments(const QMap<QString, QString>& customMinecraftArguments)
{
	mCustomMinecraftArguments = customMinecraftArguments;
	return *this;
}
