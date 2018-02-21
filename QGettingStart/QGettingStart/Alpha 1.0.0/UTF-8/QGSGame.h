#pragma once

#include "Game.h"
#include "Exception.h"

#include "GettingStart/GSGame.h"

class QGSGame:public Game
{
public:
	friend class QGSGameBuilder;
	friend class QGSLauncher;

	QGSGame();
	virtual ~QGSGame();
public:
	/*获取游戏版本*/
	virtual QString getGameVersion();
	/*获取游戏路径（绝对/相对）*/
	virtual QString getGamePath();
	/*获取Java路径*/
	virtual QString getJavaPath();
	/*获取Native文件夹路径*/
	virtual QString getNativePath();
	/*获取用户名*/
	virtual QString getPlayerName();
	/*获取用户类型*/
	virtual QString getUserType();
	/*获取额外参数*/
	virtual QString getExtraArgument();
	/*获取最小内存*/
	virtual int getXmn();
	/*获取最大内存*/
	virtual int getXmx();
private:
	gs::GSGame game;
};
