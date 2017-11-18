#include "QGSGame.h"

#include <QException>

QGSGame::QGSGame()
{

}


QGSGame::~QGSGame()
{
}

/*��ȡ��Ϸ�汾*/
QString QGSGame::getGameVersion()
{
	return QString::fromLocal8Bit(game.getVersion().c_str());
}

/*��ȡ��Ϸ·��������/��ԣ�*/
QString QGSGame::getGamePath()
{
	return QString::fromLocal8Bit(game.getGamePath().c_str());
}

/*��ȡJava·��*/
QString QGSGame::getJavaPath()
{
	return QString::fromLocal8Bit(game.getJavaPath().c_str());
}

/*��ȡNative�ļ���·��*/
QString QGSGame::getNativePath()
{
	return QString::fromLocal8Bit(game.getNativePath().c_str());
}

/*��ȡ�û���*/
QString QGSGame::getPlayerName()
{
	return QString::fromLocal8Bit(game.getPlayerName().c_str());
}

/*��ȡ�û�����*/
QString QGSGame::getUserType()
{
	return QString::fromLocal8Bit(game.getUserType().c_str());
}

/*��ȡ�������*/
QString QGSGame::getExtraArgument()
{
	return QString::fromLocal8Bit(game.getExtraArgument().c_str());
}

/*��ȡ��С�ڴ�*/
int QGSGame::getXmn()
{
	return game.getXmn();
}

/*��ȡ����ڴ�*/
int QGSGame::getXmx()
{
	return game.getXmx();
}
