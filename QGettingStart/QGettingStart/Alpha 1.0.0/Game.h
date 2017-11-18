#pragma once

#include <QString>

class Game
{
public:
	Game()
	{

	}
	virtual ~Game()
	{

	}
public:
	/*��ȡ��Ϸ�汾*/
	virtual QString getGameVersion() = 0;
	/*��ȡ��Ϸ·��������/��ԣ�*/
	virtual QString getGamePath() = 0;
	/*��ȡJava·��*/
	virtual QString getJavaPath() = 0;
	/*��ȡNative�ļ���·��*/
	virtual QString getNativePath() = 0;
	/*��ȡ�û���*/
	virtual QString getPlayerName() = 0;
	/*��ȡ�û�����*/
	virtual QString getUserType() = 0;
	/*��ȡ�������*/
	virtual QString getExtraArgument() = 0;
	/*��ȡ��С�ڴ�*/
	virtual int getXmn() = 0;
	/*��ȡ����ڴ�*/
	virtual int getXmx() = 0;
};

