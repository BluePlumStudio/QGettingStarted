#pragma once

#include "Game.h"
#include "Exception.h"

#include "GettingStart/GSGame.h"

class QGSGame:public Game
{
public:
	friend class QGSGameBuilder;
	friend class QGSLauncher;

	QGSGame();
	virtual ~QGSGame();
public:
	/*��ȡ��Ϸ�汾*/
	virtual QString getGameVersion();
	/*��ȡ��Ϸ·��������/��ԣ�*/
	virtual QString getGamePath();
	/*��ȡJava·��*/
	virtual QString getJavaPath();
	/*��ȡNative�ļ���·��*/
	virtual QString getNativePath();
	/*��ȡ�û���*/
	virtual QString getPlayerName();
	/*��ȡ�û�����*/
	virtual QString getUserType();
	/*��ȡ�������*/
	virtual QString getExtraArgument();
	/*��ȡ��С�ڴ�*/
	virtual int getXmn();
	/*��ȡ����ڴ�*/
	virtual int getXmx();
private:
	gs::GSGame game;
};

