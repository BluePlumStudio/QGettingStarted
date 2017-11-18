#include "QGSGameBuilder.h"


QGSGameBuilder::QGSGameBuilder()
{
	mGame = new QGSGame;

	if (!mGame)
	{
		throw ExceptionBadAlloc();
	}

	
}


QGSGameBuilder::~QGSGameBuilder()
{
	if (mGame)
	{
		delete mGame;
	}
	mGame = nullptr;
}

/*设置游戏版本*/
bool QGSGameBuilder::setGameVersion(QString gameVersion)
{
	bool ret = true;

	if (!mGame->game.isInit())
	{
		mGameVersion = gameVersion;
		if (!mGamePath.isEmpty())
		{
			Status status = mGame->game.init(mGameVersion.toLocal8Bit().toStdString(), mGamePath.toLocal8Bit().toStdString());
			if (status != Status::NO_ERROR)
			{
				ret = false;
			}
		}
	}

	return ret;
}

/*设置游戏路径（绝对/相对）*/
bool QGSGameBuilder::setGamePath(QString gamePath)
{
	bool ret = true;

	if (!mGame->game.isInit())
	{
		mGamePath = gamePath;
		if (!mGameVersion.isEmpty())
		{
			Status status = mGame->game.init(mGameVersion.toLocal8Bit().toStdString(), mGamePath.toLocal8Bit().toStdString());
			if (status != Status::NO_ERROR)
			{
				ret = false;
			}
		}
	}

	return ret;
}

/*设置Java路径*/
bool QGSGameBuilder::setJavaPath(QString javaPath)
{
	bool ret = false;

	if (mGame->game.isInit())
	{
		mGame->game.setJavaPath(javaPath.toLocal8Bit().toStdString());
		ret = true;
	}

	return ret;
}

/*设置Native文件夹路径*/
bool QGSGameBuilder::setNativePath(QString nativePath)
{
	bool ret = false;

	if (mGame->game.isInit())
	{
		mGame->game.setNativePath(nativePath.toLocal8Bit().toStdString());
		ret = true;
	}

	return ret;
}

/*设置用户名*/
bool QGSGameBuilder::setPlayerName(QString playerName)
{
	bool ret = false;

	if (mGame->game.isInit())
	{
		mGame->game.setPlayerName(playerName.toLocal8Bit().toStdString());
		ret = true;
	}

	return ret;
}

/*设置用户类型*/
bool QGSGameBuilder::setUserType(QString userType)
{
	bool ret = false;

	if (mGame->game.isInit())
	{
		mGame->game.setUserType(userType.toLocal8Bit().toStdString());
		ret = true;
	}

	return ret;
}

/*设置额外参数*/
bool QGSGameBuilder::setExtraArgument(QString extraArgument)
{
	bool ret = false;

	if (mGame->game.isInit())
	{
		mGame->game.setExtraArgument(extraArgument.toLocal8Bit().toStdString());
		ret = true;
	}

	return ret;
}

/*设置最小内存*/
bool QGSGameBuilder::setXmn(int Xmn)
{
	bool ret = false;

	if (mGame->game.isInit())
	{
		mGame->game.setXmn(Xmn);
		ret = true;
	}

	return ret;
}

/*设置最大内存*/
bool QGSGameBuilder::setXmx(int Xmx)
{
	bool ret = false;

	if (mGame->game.isInit())
	{
		mGame->game.setXmx(Xmx);
		ret = true;
	}

	return ret;
}

/*获取游戏*/
QGSGame * QGSGameBuilder::getGame()
{
	return mGame;
}