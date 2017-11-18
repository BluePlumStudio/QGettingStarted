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

/*��ȡ��Ϸ�汾*/
QString QGSGame::getGameVersion()
{
	return QString::fromLocal8Bit(mGame.getVersion().c_str());
}

/*��ȡ��Ϸ·��������/��ԣ�*/
QString QGSGame::getGamePath()
{
	return QString::fromLocal8Bit(mGame.getGamePath().c_str());
}

/*��ȡJava·��*/
QString QGSGame::getJavaPath()
{
	return QString::fromLocal8Bit(mGame.getJavaPath().c_str());
}

/*��ȡNative�ļ���·��*/
QString QGSGame::getNativePath()
{
	return QString::fromLocal8Bit(mGame.getNativePath().c_str());
}

/*��ȡ�û���*/
QString QGSGame::getPlayerName()
{
	return QString::fromLocal8Bit(mGame.getPlayerName().c_str());
}

/*��ȡ�û�����*/
QString QGSGame::getUserType()
{
	return QString::fromLocal8Bit(mGame.getUserType().c_str());
}

/*��ȡ�������*/
QString QGSGame::getExtraArgument()
{
	return QString::fromLocal8Bit(mGame.getExtraArgument().c_str());
}

/*��ȡJVM����*/
QString QGSGame::getJVMArgument()
{
	return mJVMArgument;
}

/*��ȡǰ��ָ��*/
QString QGSGame::getPreInstruction()
{
	return mPreInstruction;
}

/*��ȡֱ���������ַ*/
QString QGSGame::getServerAddress()
{
	return mServerAddress;
}

/*��ȡ��Ϸ����*/
QString QGSGame::getGameArgument()
{
	return mGameArgument;
}

/*��ȡ��С�ڴ�*/
int QGSGame::getXmn()
{
	return mGame.getXmn();
}

/*��ȡ����ڴ�*/
int QGSGame::getXmx()
{
	return mGame.getXmx();
}
