#include "QGSGame.h"

#include <QException>

QGSGame::QGSGame()
{
	mJVMArgument = "";
	mPreInstruction = "";
	mServerAddress = "";
}


QGSGame::~QGSGame()
{
}

/*获取游戏版本*/
QString QGSGame::getGameVersion()
{
	return QString::fromLocal8Bit(mGame.getVersion().c_str());
}

/*获取游戏路径（绝对/相对）*/
QString QGSGame::getGamePath()
{
	return QString::fromLocal8Bit(mGame.getGamePath().c_str());
}

/*获取Java路径*/
QString QGSGame::getJavaPath()
{
	return QString::fromLocal8Bit(mGame.getJavaPath().c_str());
}

/*获取Native文件夹路径*/
QString QGSGame::getNativePath()
{
	return QString::fromLocal8Bit(mGame.getNativePath().c_str());
}

/*获取用户名*/
QString QGSGame::getPlayerName()
{
	return QString::fromLocal8Bit(mGame.getPlayerName().c_str());
}

/*获取用户类型*/
QString QGSGame::getUserType()
{
	return QString::fromLocal8Bit(mGame.getUserType().c_str());
}

/*获取额外参数*/
QString QGSGame::getExtraArgument()
{
	return QString::fromLocal8Bit(mGame.getExtraArgument().c_str());
}

/*获取JVM参数*/
QString QGSGame::getJVMArgument()
{
	return mJVMArgument;
}

/*获取前置指令*/
QString QGSGame::getPreInstruction()
{
	return mPreInstruction;
}

/*获取直入服务器地址*/
QString QGSGame::getServerAddress()
{
	return mServerAddress;
}

/*获取游戏参数*/
QString QGSGame::getGameArgument()
{
	return mGameArgument;
}

/*获取最小内存*/
int QGSGame::getXmn()
{
	return mGame.getXmn();
}

/*获取最大内存*/
int QGSGame::getXmx()
{
	return mGame.getXmx();
}
