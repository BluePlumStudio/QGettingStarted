#pragma once

#include <QString>

#include "QGSAbstractGame.h"

class QGSAbstractGameBuilder
{
public:
	class GameBuilderError
	{
	public:
		typedef uint ErrorFlags;
	public:
		enum Error
		{
			NO_ERROR = 0x01,
			JSON_PRASE_ERROR = 0x02,
			OPEN_FILE_ERROR = 0x04,
			FILE_NOT_EXISTING = 0x08,
			DIR_NOT_EXISTING = 0x10,
			INITED = 0x20,
			GAME_VERSION_CIRCULAR_REFERENCE = 0x40
		};
	public:
		GameBuilderError(QString errorMessage = "", ErrorFlags buildError = Error::NO_ERROR)
		{
			mErrorMessage = errorMessage;
			mBuildError = buildError;
		}

		~GameBuilderError()
		{
		}

	public:
		QString mErrorMessage;
		ErrorFlags mBuildError;
	};

public:
	QGSAbstractGameBuilder()
	{

	}
	virtual ~QGSAbstractGameBuilder()
	{

	}

public:
	/*设置游戏版本*/
	virtual bool setGameVersion(QString gameVersion) = 0;
	/*设置游戏路径（绝对/相对）*/
	virtual bool setGamePath(QString gamePath) = 0;
	/*设置Java路径*/
	virtual bool setJavaPath(QString javaPath) = 0;
	/*设置Native文件夹路径*/
	virtual bool setNativePath(QString nativePath) = 0;
	/*设置用户名*/
	virtual bool setPlayerName(QString playerName) = 0;
	/*设置用户类型*/
	virtual bool setUserType(QString userType) = 0;
	/*设置accessToken*/
	virtual bool setAccessToken(const QString & accessToken) = 0;
	/*设置clientToken*/
	virtual bool setClientToken(const QString & clientToken) = 0;
	/*设置JVM参数*/
	virtual bool setJVMArgument(QString JVMArgument) = 0;
	/*设置前置指令*/
	virtual bool setPreInstruction(QString preInstruction) = 0;
	/*设置直入服务器地址*/
	virtual bool setServerAddress(QString serverAddress) = 0;
	/*设置游戏参数*/
	virtual bool setGameArgument(QString gameArgument) = 0;
	/*设置最小内存*/
	virtual bool setXmn(int Xmn) = 0;
	/*设置最大内存*/
	virtual bool setXmx(int Xmx) = 0;
	/*获取游戏*/
	virtual QGSAbstractGame * getGame(QGSAbstractGameBuilder::GameBuilderError * gameError = nullptr) = 0;
};

