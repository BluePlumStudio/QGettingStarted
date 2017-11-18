#pragma once

#include "QGSAbstractGame.h"
#include "../QGettingStart_Util/Exception.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QString>

//#include "GettingStart/GSGame.h"

class QGSGame:public QGSAbstractGame
{
public:
	friend class QGSGameBuilder;
	friend class QGSLauncher;
	friend class QGSUtil;

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
	/*��ȡaccessToken*/
	virtual QString getAccessToken();
	/*��ȡclientToken*/
	virtual QString getClientToken();
	/*��ȡJVM����*/
	virtual QString getJVMArgument();
	/*��ȡǰ��ָ��*/
	virtual QString getPreInstruction();
	/*��ȡֱ���������ַ*/
	virtual QString getServerAddress();
	/*��ȡ��Ϸ����*/
	virtual QString getGameArgument();
	/*��ȡ��С�ڴ�*/
	virtual int getXmn();
	/*��ȡ����ڴ�*/
	virtual int getXmx();
private:
	void setInitState(const bool state);
	bool getInitState()const;
	void setJsonDocument(const QJsonDocument & jsonDocument);
	QJsonDocument getJsonDocument()const;
	void setFatherPtr(QGSGame * fatherPtr);
	QGSGame * getFatherPtr()const;

	/*������Ϸ�汾*/
	void setGameVersion(const QString & gameVersion);
	/*������Ϸ·��������/��ԣ�*/
	void setGamePath(const QString & gamePath);
	/*����Java·��*/
	void setJavaPath(const QString & JavaPath);
	/*����Native�ļ���·��*/
	void setNativePath(const QString & nativePath);
	/*�����û���*/
	void setPlayerName(const QString & playerName);
	/*�����û�����*/
	void setUserType(const QString & userType);
	/*����accessToken*/
	void setAccessToken(const QString & accessToken);
	/*����clientToken*/
	void setClientToken(const QString & clientToken);
	/*����JVM����*/
	void setJVMArgument(const QString & JVMArgument);
	/*����ǰ��ָ��*/
	void setPreInstruction(const QString & preInstruction);
	/*����ֱ���������ַ*/
	void setServerAddress(const QString & serverAddress);
	/*������Ϸ����*/
	void setGameArgument(const QString & gameArgument);
	/*������С�ڴ�*/
	void setXmn(const int Xmn);
	/*��������ڴ�*/
	void setXmx(const int Xmx);
private:

	class Private;
	friend class Private;
	Private * d;
};

