#pragma once

#include "QGSAbstractGameBuilder.h"
#include "QGSAbstractGame.h"
#include "../QGettingStart_Util/Exception.h"

#include "QGSGame.h"

//#include "GettingStart/GSGame.h"

class QGSGameBuilder:public QGSAbstractGameBuilder
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
	virtual bool setJavaPath(QString JavaPath);
	/*����Native�ļ���·��*/
	virtual bool setNativePath(QString nativePath);
	/*�����û���*/
	virtual bool setPlayerName(QString playerName);
	/*�����û�����*/
	virtual bool setUserType(QString userType);
	/*����accessToken*/
	virtual bool setAccessToken(const QString & accessToken);
	/*����clientToken*/
	virtual bool setClientToken(const QString & clientToken);
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
	virtual QGSGame * getGame(QGSAbstractGameBuilder::GameBuilderError * gameError = nullptr);
private:
	QGSAbstractGameBuilder::GameBuilderError initGame();
	void gameInherit(QGSGame * childGame, QGSGame * fatherGame);
private:
	QGSGame * mGame;
	QStringList mGameVersionList;
};

