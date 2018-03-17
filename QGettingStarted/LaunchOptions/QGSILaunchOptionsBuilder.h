#pragma once

#include "QGSLaunchOptions.h"

class QGSILaunchOptionsBuilder 
{
public: 
	QGSILaunchOptionsBuilder();

	QGSILaunchOptionsBuilder(const QGSILaunchOptionsBuilder & right) = delete;

	QGSILaunchOptionsBuilder(QGSILaunchOptionsBuilder && right) = delete;

	QGSILaunchOptionsBuilder & operator=(const QGSILaunchOptionsBuilder & right) = delete;

	QGSILaunchOptionsBuilder & operator=(QGSILaunchOptionsBuilder && right) = delete;

	virtual ~QGSILaunchOptionsBuilder();
	
	virtual QGSLaunchOptions * getLaunchOptions() = 0;
	
	virtual QGSILaunchOptionsBuilder & setJavaPath(const QString & JavaPath) = 0;
	virtual QGSILaunchOptionsBuilder & setMaxMemory(const int maxMemory) = 0;
	virtual QGSILaunchOptionsBuilder & setMinMemory(const int minMemory) = 0;
	virtual QGSILaunchOptionsBuilder & setAuthInfo(const AuthInfo & authInfo) = 0;
	virtual QGSILaunchOptionsBuilder & setJVMArguments(const QString & JVMArguments) = 0;
	virtual QGSILaunchOptionsBuilder & setJVMArguments(const QStringList & JVMArgumentList) = 0;
	virtual QGSILaunchOptionsBuilder & setWrapper(const QString & wrapper) = 0;
	virtual QGSILaunchOptionsBuilder & setPreCalledCommands(const QString & preCalledCommands) = 0;
	virtual QGSILaunchOptionsBuilder & setServerInfo(const QGSLaunchOptions::ServerInfo & serverInfo) = 0;
	virtual QGSILaunchOptionsBuilder & setGameArguments(const QString & gameArguments) = 0;
	virtual QGSILaunchOptionsBuilder & setWindowSize(const QSize & windowSize) = 0;
	virtual QGSILaunchOptionsBuilder & setFullScreen(const bool fullScreen) = 0;
	virtual QGSILaunchOptionsBuilder & setMetaspaceSize(const int metaspaceSize) = 0;
	virtual QGSILaunchOptionsBuilder & setProxy(const QNetworkProxy & proxy) = 0;
	virtual QGSILaunchOptionsBuilder & setGeneratedJVMArguments(const bool generatedJVMArguments) = 0;
	virtual QGSILaunchOptionsBuilder & setLoggingPath(const QString & loggingPath) = 0;
protected: 
	QGSLaunchOptions * mLaunchOptionsPtr;
};
