#include "QGSLaunchOptionsBuilder.h"

QGSLaunchOptionsBuilder::QGSLaunchOptionsBuilder()
{
}

QGSLaunchOptionsBuilder::~QGSLaunchOptionsBuilder()
{
}

QGSLaunchOptions * QGSLaunchOptionsBuilder::getLaunchOptions()
{
    return mLaunchOptionsPtr;
}

QGSLaunchOptionsBuilder & QGSLaunchOptionsBuilder::setJavaPath(const QString & JavaPath)
{
	mLaunchOptionsPtr->setJavaPath(JavaPath);
	return *this;
}

QGSLaunchOptionsBuilder & QGSLaunchOptionsBuilder::setMaxMemory(const int maxMemory)
{
	mLaunchOptionsPtr->setMaxMemory(maxMemory);
	return *this;
}

QGSLaunchOptionsBuilder & QGSLaunchOptionsBuilder::setMinMemory(const int minMemory)
{
	mLaunchOptionsPtr->setMinMemory(minMemory);
	return *this;
}

QGSLaunchOptionsBuilder & QGSLaunchOptionsBuilder::setAuthInfo(const QGSAuthInfo & authInfo)
{
	mLaunchOptionsPtr->setAuthInfo(authInfo);
	return *this;
}

QGSLaunchOptionsBuilder & QGSLaunchOptionsBuilder::setJVMArguments(const QString & JVMArguments)
{
	mLaunchOptionsPtr->setJVMArguments(JVMArguments);
	return *this;
}

QGSLaunchOptionsBuilder & QGSLaunchOptionsBuilder::setJVMArguments(const QStringList & JVMArgumentList)
{
	mLaunchOptionsPtr->setJVMArguments(JVMArgumentList.join(" "));
	return *this;
}

QGSLaunchOptionsBuilder & QGSLaunchOptionsBuilder::setWrapper(const QString & wrapper)
{
	mLaunchOptionsPtr->setWrapper(wrapper);
	return *this;
}

QGSLaunchOptionsBuilder & QGSLaunchOptionsBuilder::setPreCalledCommands(const QString & preCalledCommands)
{
	mLaunchOptionsPtr->setPreCalledCommands(preCalledCommands);
	return *this;
}

QGSLaunchOptionsBuilder & QGSLaunchOptionsBuilder::setServerInfo(const QGSLaunchOptions::ServerInfo & serverInfo)
{
	mLaunchOptionsPtr->setServerInfo(serverInfo);
	return *this;
}

QGSLaunchOptionsBuilder & QGSLaunchOptionsBuilder::setGameArguments(const QString & gameArguments)
{
	mLaunchOptionsPtr->setGameArguments(gameArguments);
	return *this;
}

QGSLaunchOptionsBuilder & QGSLaunchOptionsBuilder::setWindowSize(const QSize & windowSize)
{
	mLaunchOptionsPtr->setWindowSize(windowSize);
	return *this;
}

QGSLaunchOptionsBuilder & QGSLaunchOptionsBuilder::setFullScreen(const bool fullScreen)
{
	mLaunchOptionsPtr->setFullScreen(fullScreen);
	return *this;
}

QGSLaunchOptionsBuilder & QGSLaunchOptionsBuilder::setMetaspaceSize(const int metaspaceSize)
{
	mLaunchOptionsPtr->setMetaspaceSize(metaspaceSize);
	return *this;
}

QGSLaunchOptionsBuilder & QGSLaunchOptionsBuilder::setProxy(const QNetworkProxy & proxy)
{
	mLaunchOptionsPtr->setProxy(proxy);
	return *this;
}

QGSLaunchOptionsBuilder & QGSLaunchOptionsBuilder::setGeneratedJVMArguments(const bool generatedJVMArguments)
{
	mLaunchOptionsPtr->setGeneratedJVMArguments(generatedJVMArguments);
	return *this;
}

QGSLaunchOptionsBuilder & QGSLaunchOptionsBuilder::setLoggingPath(const QString & loggingPath)
{
	mLaunchOptionsPtr->setLoggingPath(loggingPath);
	return *this;
}
