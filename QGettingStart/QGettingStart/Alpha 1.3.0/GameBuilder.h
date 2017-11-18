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
	/*������Ϸ�汾*/
	virtual bool setGameVersion(QString gameVersion) = 0;
	/*������Ϸ·��������/��ԣ�*/
	virtual bool setGamePath(QString gamePath) = 0;
	/*����Java·��*/
	virtual bool setJavaPath(QString javaPath) = 0;
	/*����Native�ļ���·��*/
	virtual bool setNativePath(QString nativePath) = 0;
	/*�����û���*/
	virtual bool setPlayerName(QString playerName) = 0;
	/*�����û�����*/
	virtual bool setUserType(QString userType) = 0;
	/*���ö������*/
	//virtual bool setExtraArgument(QString extraArgument) = 0;
	/*����JVM����*/
	virtual bool setJVMArgument(QString JVMArgument) = 0;
	/*����ǰ��ָ��*/
	virtual bool setPreInstruction(QString preInstruction) = 0;
	/*����ֱ���������ַ*/
	virtual bool setServerAddress(QString serverAddress) = 0;
	/*������Ϸ����*/
	virtual bool setGameArgument(QString gameArgument) = 0;
	/*������С�ڴ�*/
	virtual bool setXmn(int Xmn) = 0;
	/*��������ڴ�*/
	virtual bool setXmx(int Xmx) = 0;
	/*��ȡ��Ϸ*/
	virtual Game * getGame() = 0;
};

