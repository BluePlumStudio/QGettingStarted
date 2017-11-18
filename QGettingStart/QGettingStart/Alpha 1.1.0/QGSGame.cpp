#include "QGSGame.h"

#include <QException>

QGSGame::QGSGame()
{

}


QGSGame::~QGSGame()
{
}

/*获取游戏版本*/
QString QGSGame::getGameVersion()
{
	return QString::fromLocal8Bit(game.getVersion().c_str());
}

/*获取游戏路径（绝对/相对）*/
QString QGSGame::getGamePath()
{
	return QString::fromLocal8Bit(game.getGamePath().c_str());
}

/*获取Java路径*/
QString QGSGame::getJavaPath()
{
	return QString::fromLocal8Bit(game.getJavaPath().c_str());
}

/*获取Native文件夹路径*/
QString QGSGame::getNativePath()
{
	return QString::fromLocal8Bit(game.getNativePath().c_str());
}

/*获取用户名*/
QString QGSGame::getPlayerName()
{
	return QString::fromLocal8Bit(game.getPlayerName().c_str());
}

/*获取用户类型*/
QString QGSGame::getUserType()
{
	return QString::fromLocal8Bit(game.getUserType().c_str());
}

/*获取额外参数*/
QString QGSGame::getExtraArgument()
{
	return QString::fromLocal8Bit(game.getExtraArgument().c_str());
}

/*获取最小内存*/
int QGSGame::getXmn()
{
	return game.getXmn();
}

/*获取最大内存*/
int QGSGame::getXmx()
{
	return game.getXmx();
}
