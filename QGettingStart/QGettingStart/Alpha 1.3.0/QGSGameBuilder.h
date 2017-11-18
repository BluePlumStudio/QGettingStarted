#pragma once

#include "GameBuilder.h"
#include "Game.h"
#include "Exception.h"

#include "QGSGame.h"

#include "GettingStart/GSGame.h"

class QGSGameBuilder:public GameBuilder
{
public:
	QGSGameBuilder();
	virtual ~QGSGameBuilder();
public:
	/*������Ϸ�汾*/
	virtual bool setGameVersion(QString gameVersion);
	/*������Ϸ·��������/��ԣ�*/
	virtual bool setGamePath(QString gamePath);
	/*����Java·��*/
	virtual bool setJavaPath(QString javaPath);
	/*����Native�ļ���·��*/
	virtual bool setNativePath(QString nativePath);
	/*�����û���*/
	virtual bool setPlayerName(QString playerName);
	/*�����û�����*/
	virtual bool setUserType(QString userType);
	/*���ö������*/
	virtual bool setExtraArgument(QString extraArgument);
	/*����JVM����*/
	virtual bool setJVMArgument(QString JVMArgument);
	/*����ǰ��ָ��*/
	virtual bool setPreInstruction(QString preInstruction);
	/*����ֱ���������ַ*/
	virtual bool setServerAddress(QString serverAddress);
	/*������Ϸ����*/
	virtual bool setGameArgument(QString gameArgument);
	/*������С�ڴ�*/
	virtual bool setXmn(int Xmn);
	/*��������ڴ�*/
	virtual bool setXmx(int Xmx);
	/*��ȡ��Ϸ*/
	virtual QGSGame * getGame();
private:
	QGSGame * mGame;
	QString mGameVersion;
	QString mGamePath;

};

