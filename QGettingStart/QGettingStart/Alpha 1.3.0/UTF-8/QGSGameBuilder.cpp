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

	if (!mGame->mGame.isInit())
	{
		mGameVersion = gameVersion;
		if (!mGamePath.isEmpty())
		{
			Status status = mGame->mGame.init(mGameVersion.toLocal8Bit().toStdString(), mGamePath.toLocal8Bit().toStdString());
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

	if (!mGame->mGame.isInit())
	{
		mGamePath = gamePath;
		if (!mGameVersion.isEmpty())
		{
			Status status = mGame->mGame.init(mGameVersion.toLocal8Bit().toStdString(), mGamePath.toLocal8Bit().toStdString());
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

	if (mGame->mGame.isInit())
	{
		mGame->mGame.setJavaPath(javaPath.toLocal8Bit().toStdString());
		ret = true;
	}

	return ret;
}

/*设置Native文件夹路径*/
bool QGSGameBuilder::setNativePath(QString nativePath)
{
	bool ret = false;

	if (mGame->mGame.isInit())
	{
		mGame->mGame.setNativePath(nativePath.toLocal8Bit().toStdString());
		ret = true;
	}

	return ret;
}

/*设置用户名*/
bool QGSGameBuilder::setPlayerName(QString playerName)
{
	bool ret = false;

	if (mGame->mGame.isInit())
	{
		mGame->mGame.setPlayerName(playerName.toLocal8Bit().toStdString());
		ret = true;
	}

	return ret;
}

/*设置用户类型*/
bool QGSGameBuilder::setUserType(QString userType)
{
	bool ret = false;

	if (mGame->mGame.isInit())
	{
		mGame->mGame.setUserType(userType.toLocal8Bit().toStdString());
		ret = true;
	}

	return ret;
}

/*设置额外参数*/
bool QGSGameBuilder::setExtraArgument(QString extraArgument)
{
	bool ret = false;

	if (mGame->mGame.isInit())
	{
		mGame->mGame.setExtraArgument(extraArgument.toLocal8Bit().toStdString());
		ret = true;
	}

	return ret;
}

/*设置JVM参数*/
bool QGSGameBuilder::setJVMArgument(QString JVMArgument)
{
	bool ret = false;

	if (mGame->mGame.isInit())
	{
		mGame->mJVMArgument = JVMArgument;
		ret = true;
	}

	return ret;
}

/*设置前置指令*/
bool QGSGameBuilder::setPreInstruction(QString preInstruction)
{
	bool ret = false;

	if (mGame->mGame.isInit())
	{
		mGame->mPreInstruction = preInstruction;
		ret = true;
	}

	return ret;
}

/*设置直入服务器地址*/
bool QGSGameBuilder::setServerAddress(QString serverAddress)
{
	bool ret = false;

	if (mGame->mGame.isInit())
	{
		mGame->mServerAddress = serverAddress;
		ret = true;
	}

	return ret;
}

/*设置游戏参数*/
bool QGSGameBuilder::setGameArgument(QString gameArgument)
{
	bool ret = false;

	if (mGame->mGame.isInit())
	{
		mGame->mGameArgument = gameArgument;
		ret = true;
	}

	return ret;
}

/*设置最小内存*/
bool QGSGameBuilder::setXmn(int Xmn)
{
	bool ret = false;

	if (mGame->mGame.isInit())
	{
		mGame->mGame.setXmn(Xmn);
		ret = true;
	}

	return ret;
}

/*设置最大内存*/
bool QGSGameBuilder::setXmx(int Xmx)
{
	bool ret = false;

	if (mGame->mGame.isInit())
	{
		mGame->mGame.setXmx(Xmx);
		ret = true;
	}

	return ret;
}

/*获取游戏*/
QGSGame * QGSGameBuilder::getGame()
{
	return mGame;
}