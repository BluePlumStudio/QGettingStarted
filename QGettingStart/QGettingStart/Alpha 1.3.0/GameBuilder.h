#pragma once

#include <QString>

#include "Game.h"

class GameBuilder
{
public:
	GameBuilder()
	{

	}
	virtual ~GameBuilder()
	{

	}

public:
	/*设置游戏版本*/
	virtual bool setGameVersion(QString gameVersion) = 0;
	/*设置游戏路径（绝对/相对）*/
	virtual bool setGamePath(QString gamePath) = 0;
	/*设置Java路径*/
	virtual bool setJavaPath(QString javaPath) = 0;
	/*设置Native文件夹路径*/
	virtual bool setNativePath(QString nativePath) = 0;
	/*设置用户名*/
	virtual bool setPlayerName(QString playerName) = 0;
	/*设置用户类型*/
	virtual bool setUserType(QString userType) = 0;
	/*设置额外参数*/
	//virtual bool setExtraArgument(QString extraArgument) = 0;
	/*设置JVM参数*/
	virtual bool setJVMArgument(QString JVMArgument) = 0;
	/*设置前置指令*/
	virtual bool setPreInstruction(QString preInstruction) = 0;
	/*设置直入服务器地址*/
	virtual bool setServerAddress(QString serverAddress) = 0;
	/*设置游戏参数*/
	virtual bool setGameArgument(QString gameArgument) = 0;
	/*设置最小内存*/
	virtual bool setXmn(int Xmn) = 0;
	/*设置最大内存*/
	virtual bool setXmx(int Xmx) = 0;
	/*获取游戏*/
	virtual Game * getGame() = 0;
};

