#pragma once

#include "QGSILaunchOptionsBuilder.h"
#include "QGSLaunchOptions.h"

class QGSLaunchOptionsBuilder: public QGSILaunchOptionsBuilder 
{
public: 
	QGSLaunchOptionsBuilder();

	QGSLaunchOptionsBuilder(const QGSLaunchOptionsBuilder & right) = delete;

	QGSLaunchOptionsBuilder(QGSLaunchOptionsBuilder && right) = delete;

	QGSLaunchOptionsBuilder & operator=(const QGSLaunchOptionsBuilder & right) = delete;

	QGSLaunchOptionsBuilder & operator=(QGSLaunchOptionsBuilder && right) = delete;

	virtual ~QGSLaunchOptionsBuilder();
	
	virtual QGSLaunchOptions * getLaunchOptions()override;

	virtual QGSLaunchOptionsBuilder & setJavaPath(const QString & JavaPath)override;
	virtual QGSLaunchOptionsBuilder & setMaxMemory(const int maxMemory)override;
	virtual QGSLaunchOptionsBuilder & setMinMemory(const int minMemory)override;
	virtual QGSLaunchOptionsBuilder & setAuthInfo(const QGSAuthInfo & authInfo)override;
	virtual QGSLaunchOptionsBuilder & setJVMArguments(const QString & JVMArguments)override;
	virtual QGSLaunchOptionsBuilder & setJVMArguments(const QStringList & JVMArgumentList)override;
	virtual QGSLaunchOptionsBuilder & setWrapper(const QString & wrapper)override;
	virtual QGSLaunchOptionsBuilder & setPreCalledCommands(const QString & preCalledCommands)override;
	virtual QGSLaunchOptionsBuilder & setServerInfo(const QGSServerInfo & serverInfo)override;
	virtual QGSLaunchOptionsBuilder & setGameArguments(const QString & gameArguments)override;
	virtual QGSLaunchOptionsBuilder & setWindowSize(const QSize & windowSize)override;
	virtual QGSLaunchOptionsBuilder & setFullScreen(const bool fullScreen)override;
	virtual QGSLaunchOptionsBuilder & setMetaspaceSize(const int metaspaceSize)override;
	virtual QGSLaunchOptionsBuilder & setProxy(const QNetworkProxy & proxy)override;
	virtual QGSLaunchOptionsBuilder & setGeneratedJVMArguments(const bool generatedJVMArguments)override;
	virtual QGSLaunchOptionsBuilder & setLoggingPath(const QString & loggingPath)override;
	virtual QGSLaunchOptionsBuilder & setCustomMinecraftArguments(const QMap<QString, QString> & customMinecraftArguments);

};