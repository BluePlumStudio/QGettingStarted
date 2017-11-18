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
	/*����accessToken*/
	virtual bool setAccessToken(const QString & accessToken) = 0;
	/*����clientToken*/
	virtual bool setClientToken(const QString & clientToken) = 0;
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
	virtual QGSAbstractGame * getGame(QGSAbstractGameBuilder::GameBuilderError * gameError = nullptr) = 0;
};

