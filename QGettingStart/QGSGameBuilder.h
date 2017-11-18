#pragma once

#include "QGSAbstractGameBuilder.h"
#include "QGSAbstractGame.h"
#include "../QGettingStart_Util/Exception.h"

#include "QGSGame.h"

//#include "GettingStart/GSGame.h"

class QGSGameBuilder:public QGSAbstractGameBuilder
{
public:
	QGSGameBuilder();
	virtual ~QGSGameBuilder();
public:
	/*设置游戏版本*/
	virtual bool setGameVersion(QString gameVersion);
	/*设置游戏路径（绝对/相对）*/
	virtual bool setGamePath(QString gamePath);
	/*设置Java路径*/
	virtual bool setJavaPath(QString JavaPath);
	/*设置Native文件夹路径*/
	virtual bool setNativePath(QString nativePath);
	/*设置用户名*/
	virtual bool setPlayerName(QString playerName);
	/*设置用户类型*/
	virtual bool setUserType(QString userType);
	/*设置accessToken*/
	virtual bool setAccessToken(const QString & accessToken);
	/*设置clientToken*/
	virtual bool setClientToken(const QString & clientToken);
	/*设置JVM参数*/
	virtual bool setJVMArgument(QString JVMArgument);
	/*设置前置指令*/
	virtual bool setPreInstruction(QString preInstruction);
	/*设置直入服务器地址*/
	virtual bool setServerAddress(QString serverAddress);
	/*设置游戏参数*/
	virtual bool setGameArgument(QString gameArgument);
	/*设置最小内存*/
	virtual bool setXmn(int Xmn);
	/*设置最大内存*/
	virtual bool setXmx(int Xmx);
	/*获取游戏*/
	virtual QGSGame * getGame(QGSAbstractGameBuilder::GameBuilderError * gameError = nullptr);
private:
	QGSAbstractGameBuilder::GameBuilderError initGame();
	void gameInherit(QGSGame * childGame, QGSGame * fatherGame);
private:
	QGSGame * mGame;
	QStringList mGameVersionList;
};

