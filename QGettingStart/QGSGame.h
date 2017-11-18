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
	/*获取游戏版本*/
	virtual QString getGameVersion();
	/*获取游戏路径（绝对/相对）*/
	virtual QString getGamePath();
	/*获取Java路径*/
	virtual QString getJavaPath();
	/*获取Native文件夹路径*/
	virtual QString getNativePath();
	/*获取用户名*/
	virtual QString getPlayerName();
	/*获取用户类型*/
	virtual QString getUserType();
	/*获取accessToken*/
	virtual QString getAccessToken();
	/*获取clientToken*/
	virtual QString getClientToken();
	/*获取JVM参数*/
	virtual QString getJVMArgument();
	/*获取前置指令*/
	virtual QString getPreInstruction();
	/*获取直入服务器地址*/
	virtual QString getServerAddress();
	/*获取游戏参数*/
	virtual QString getGameArgument();
	/*获取最小内存*/
	virtual int getXmn();
	/*获取最大内存*/
	virtual int getXmx();
private:
	void setInitState(const bool state);
	bool getInitState()const;
	void setJsonDocument(const QJsonDocument & jsonDocument);
	QJsonDocument getJsonDocument()const;
	void setFatherPtr(QGSGame * fatherPtr);
	QGSGame * getFatherPtr()const;

	/*设置游戏版本*/
	void setGameVersion(const QString & gameVersion);
	/*设置游戏路径（绝对/相对）*/
	void setGamePath(const QString & gamePath);
	/*设置Java路径*/
	void setJavaPath(const QString & JavaPath);
	/*设置Native文件夹路径*/
	void setNativePath(const QString & nativePath);
	/*设置用户名*/
	void setPlayerName(const QString & playerName);
	/*设置用户类型*/
	void setUserType(const QString & userType);
	/*设置accessToken*/
	void setAccessToken(const QString & accessToken);
	/*设置clientToken*/
	void setClientToken(const QString & clientToken);
	/*设置JVM参数*/
	void setJVMArgument(const QString & JVMArgument);
	/*设置前置指令*/
	void setPreInstruction(const QString & preInstruction);
	/*设置直入服务器地址*/
	void setServerAddress(const QString & serverAddress);
	/*设置游戏参数*/
	void setGameArgument(const QString & gameArgument);
	/*设置最小内存*/
	void setXmn(const int Xmn);
	/*设置最大内存*/
	void setXmx(const int Xmx);
private:

	class Private;
	friend class Private;
	Private * d;
};

