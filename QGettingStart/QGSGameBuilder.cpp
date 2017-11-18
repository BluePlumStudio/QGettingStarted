#include "QGSGameBuilder.h"

#include <QFile>
#include <QDir>
#include <QDebug>

QGSGameBuilder::QGSGameBuilder()
{
	mGame = new QGSGame;
	if (!mGame)
	{
		throw ExceptionBadAlloc();
	}
}


QGSGameBuilder::~QGSGameBuilder()
{

}

/*������Ϸ�汾*/
bool QGSGameBuilder::setGameVersion(QString gameVersion)
{
	bool ret = false;

	if (!mGame->getInitState())
	{
		ret = true;
		mGame->setGameVersion(gameVersion);
	}

	return ret;
}

/*������Ϸ·��������/��ԣ�*/
bool QGSGameBuilder::setGamePath(QString gamePath)
{
	bool ret = false;

	if (!mGame->getInitState())
	{
		ret = true;
		mGame->setGamePath(gamePath);
	}

	return ret;
}

/*����Java·��*/
bool QGSGameBuilder::setJavaPath(QString JavaPath)
{
	bool ret = false;

	if (!mGame->getInitState())
	{
		ret = true;
		mGame->setJavaPath(JavaPath);
	}

	return ret;
}

/*����Native�ļ���·��*/
bool QGSGameBuilder::setNativePath(QString nativePath)
{
	bool ret = false;

	if (!mGame->getInitState())
	{
		ret = true;
		mGame->setNativePath(nativePath);
	}

	return ret;
}

/*�����û���*/
bool QGSGameBuilder::setPlayerName(QString playerName)
{
	bool ret = false;

	if (!mGame->getInitState())
	{
		ret = true;
		mGame->setPlayerName(playerName);
	}

	return ret;
}

/*�����û�����*/
bool QGSGameBuilder::setUserType(QString userType)
{
	bool ret = false;

	if (!mGame->getInitState())
	{
		ret = true;
		mGame->setUserType(userType);
	}

	return ret;
}

/*����accessToken*/
bool QGSGameBuilder::setAccessToken(const QString & accessToken)
{
	bool ret = false;

	if (!mGame->getInitState())
	{
		ret = true;
		mGame->setAccessToken(accessToken);
	}

	return ret;
}

/*����clientToken*/
bool QGSGameBuilder::setClientToken(const QString & clientToken)
{
	bool ret = false;

	if (!mGame->getInitState())
	{
		ret = true;
		mGame->setClientToken(clientToken);
	}

	return ret;
}

/*����JVM����*/
bool QGSGameBuilder::setJVMArgument(QString JVMArgument)
{
	bool ret = false;

	if (!mGame->getInitState())
	{
		ret = true;
		mGame->setJVMArgument(JVMArgument);
	}

	return ret;
}

/*����ǰ��ָ��*/
bool QGSGameBuilder::setPreInstruction(QString preInstruction)
{
	bool ret = false;

	if (!mGame->getInitState())
	{
		ret = true;
		mGame->setPreInstruction(preInstruction);
	}

	return ret;
}

/*����ֱ���������ַ*/
bool QGSGameBuilder::setServerAddress(QString serverAddress)
{
	bool ret = false;

	if (!mGame->getInitState())
	{
		ret = true;
		mGame->setServerAddress(serverAddress);
	}

	return ret;
}

/*������Ϸ����*/
bool QGSGameBuilder::setGameArgument(QString gameArgument)
{
	bool ret = false;

	if (!mGame->getInitState())
	{
		ret = true;
		mGame->setGameArgument(gameArgument);
	}

	return ret;
}

/*������С�ڴ�*/
bool QGSGameBuilder::setXmn(int Xmn)
{
	bool ret = true;

	mGame->setXmn(Xmn);

	return ret;
}

/*��������ڴ�*/
bool QGSGameBuilder::setXmx(int Xmx)
{
	bool ret = true;

	mGame->setXmx(Xmx);

	return ret;
}

/*��ȡ��Ϸ*/
QGSGame * QGSGameBuilder::getGame(QGSAbstractGameBuilder::GameBuilderError * gameError)
{
	if (!mGame->getInitState())
	{
		QGSAbstractGameBuilder::GameBuilderError retGameError = initGame();
		if (gameError)
		{
			*gameError = retGameError;
		}

	}
	else
	{
		if (gameError)
		{
			*gameError = QGSAbstractGameBuilder::GameBuilderError(QString::fromLocal8Bit("mGame�ѳ�ʼ����"), QGSAbstractGameBuilder::GameBuilderError::Error::INITED);
		}

	}

	return mGame;
}

/**/

QGSAbstractGameBuilder::GameBuilderError QGSGameBuilder::initGame()
{
	QJsonObject jsonObject;

	QGSGame * gamePtr = mGame;

	do
	{
		QDir gameDir;
		gameDir.setPath(gamePtr->getGamePath());
		if (!gameDir.exists())
		{
			return QGSAbstractGameBuilder::GameBuilderError(QString::fromLocal8Bit("��Ϸ·�������ڣ�"), QGSAbstractGameBuilder::GameBuilderError::Error::DIR_NOT_EXISTING);
		}

		QFile jsonFile;
		jsonFile.setFileName(gameDir.path() +
			"/versions/" +
			gamePtr->getGameVersion() + "/" +
			gamePtr->getGameVersion() + ".json");
		if (!jsonFile.exists())
		{
			return QGSAbstractGameBuilder::GameBuilderError(QString::fromLocal8Bit("Json�ļ������ڣ�"), QGSAbstractGameBuilder::GameBuilderError::Error::FILE_NOT_EXISTING);
		}
		if (!jsonFile.open(QIODevice::ReadOnly))
		{
			return QGSAbstractGameBuilder::GameBuilderError(QString::fromLocal8Bit("Json�ļ���ʧ�ܣ�"), QGSAbstractGameBuilder::GameBuilderError::Error::OPEN_FILE_ERROR);
		}

		//qDebug() << jsonFile.readAll();
		QJsonParseError jsonParseError;
		gamePtr->setJsonDocument(QJsonDocument::fromJson(jsonFile.readAll(), &jsonParseError));
		jsonFile.close();
		if (jsonParseError.error != QJsonParseError::ParseError::NoError)
		{
			return QGSAbstractGameBuilder::GameBuilderError(QString::fromLocal8Bit("Json�ļ���������"), QGSAbstractGameBuilder::GameBuilderError::Error::JSON_PRASE_ERROR);
		}

		jsonObject = gamePtr->getJsonDocument().object();
		QString inheritsFrom;
		if (jsonObject.contains("inheritsFrom"))
		{
			QJsonValue jsonValueInheritsFrom = jsonObject.value("inheritsFrom");
			inheritsFrom = jsonValueInheritsFrom.toString();

			gamePtr->setFatherPtr(new QGSGame);
			if (!gamePtr->getFatherPtr())
			{
				throw ExceptionBadAlloc();
			}

			gameInherit(gamePtr, gamePtr->getFatherPtr());
			gamePtr->getFatherPtr()->setGameVersion(inheritsFrom);
		}

		gamePtr->setInitState(true);
		if (mGameVersionList.contains(gamePtr->getGameVersion()))
		{
			QGSAbstractGameBuilder::GameBuilderError(QString::fromLocal8Bit("��Ϸ�汾ѭ�����ã�"), QGSAbstractGameBuilder::GameBuilderError::Error::GAME_VERSION_CIRCULAR_REFERENCE);
		}
		mGameVersionList.push_back(gamePtr->getGameVersion());
		gamePtr = gamePtr->getFatherPtr();
	} while (gamePtr);

	return QGSAbstractGameBuilder::GameBuilderError(QString::fromLocal8Bit("��ʼ��mGame�ɹ���"), QGSAbstractGameBuilder::GameBuilderError::Error::NO_ERROR);
}

void QGSGameBuilder::gameInherit(QGSGame * childGame, QGSGame * fatherGame)
{
	if (!childGame || !fatherGame)
	{
		return;
	}
	
	fatherGame->setGamePath(childGame->getGamePath());

	fatherGame->setJavaPath(childGame->getJavaPath());

	fatherGame->setPlayerName(childGame->getPlayerName());

	fatherGame->setUserType(childGame->getUserType());

	fatherGame->setAccessToken(childGame->getAccessToken());

	fatherGame->setClientToken(childGame->getClientToken());

	fatherGame->setJVMArgument(childGame->getJVMArgument());

	fatherGame->setPreInstruction(childGame->getPreInstruction());

	fatherGame->setServerAddress(childGame->getServerAddress());

	fatherGame->setGameArgument(childGame->getGameArgument());

	fatherGame->setXmn(childGame->getXmn());

	fatherGame->setXmx(childGame->getXmx());

}