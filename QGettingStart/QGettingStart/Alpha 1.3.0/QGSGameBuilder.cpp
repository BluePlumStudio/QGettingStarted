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

/*������Ϸ�汾*/
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

/*������Ϸ·��������/��ԣ�*/
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

/*����Java·��*/
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

/*����Native�ļ���·��*/
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

/*�����û���*/
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

/*�����û�����*/
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

/*���ö������*/
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

/*����JVM����*/
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

/*����ǰ��ָ��*/
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

/*����ֱ���������ַ*/
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

/*������Ϸ����*/
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

/*������С�ڴ�*/
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

/*��������ڴ�*/
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

/*��ȡ��Ϸ*/
QGSGame * QGSGameBuilder::getGame()
{
	return mGame;
}