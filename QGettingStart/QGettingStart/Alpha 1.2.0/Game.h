#pragma once

#include <QString>

class Game
{
public:
	Game()
	{

	}
	virtual ~Game()
	{

	}
public:
	/*获取游戏版本*/
	virtual QString getGameVersion() = 0;
	/*获取游戏路径（绝对/相对）*/
	virtual QString getGamePath() = 0;
	/*获取Java路径*/
	virtual QString getJavaPath() = 0;
	/*获取Native文件夹路径*/
	virtual QString getNativePath() = 0;
	/*获取用户名*/
	virtual QString getPlayerName() = 0;
	/*获取用户类型*/
	virtual QString getUserType() = 0;
	/*获取额外参数*/
	virtual QString getExtraArgument() = 0;
	/*获取最小内存*/
	virtual int getXmn() = 0;
	/*获取最大内存*/
	virtual int getXmx() = 0;
};

