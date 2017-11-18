#pragma once

#include <QString>

#include "../QGettingStart_Util/Exception.h"

class QGSAbstractGame
{
public:
	QGSAbstractGame()
	{

	}
	virtual ~QGSAbstractGame()
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
	/*��ȡaccessToken*/
	virtual QString getAccessToken() = 0;
	/*��ȡclientToken*/
	virtual QString getClientToken() = 0;
	/*��ȡJVM����*/
	virtual QString getJVMArgument() = 0;
	/*��ȡǰ��ָ��*/
	virtual QString getPreInstruction() = 0;
	/*��ȡֱ���������ַ*/
	virtual QString getServerAddress() = 0;
	/*��ȡ��Ϸ����*/
	virtual QString getGameArgument() = 0;
	/*��ȡ��С�ڴ�*/
	virtual int getXmn() = 0;
	/*��ȡ����ڴ�*/
	virtual int getXmx() = 0;
};

