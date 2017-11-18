#include "QGSGame.h"

#include <QException>

class QGSGame::Private
{
public:
	Private()
	{
		mInited = false;
		mFatherPtr = nullptr;

		mGameVersion.clear();
		mGamePath.clear();
		mJavaPath.clear();
		mNativePath.clear();
		mPlayerName.clear();
		mUserType.clear();
		mAccessToken.clear();
		mClientToken.clear();
		mJVMArgument.clear();
		mPreInstruction.clear();
		mServerAddress.clear();
		mGameArgument.clear();
		mXmn = 0;
		mXmx = 0;
	}

	~Private()
	{

	}

public:
	bool			mInited;
	QGSGame *		mFatherPtr;	//继承游戏版本

	QString			mGameVersion;	//游戏版本
	QString			mGamePath;		//游戏路径
	QString			mJavaPath;		//Java路径
	QString			mNativePath;	//native文件夹路径
	QString			mPlayerName;	//用户名
	QString			mUserType;		//用户类型
	QString			mAccessToken;	//accessToken
	QString			mClientToken;	//clientToken
	QString			mJVMArgument;	//JVM参数
	QString			mPreInstruction;//前置指令
	QString			mServerAddress; //服务器直连地址
	QString			mGameArgument;  //游戏参数
	int				mXmn;			//最小内存
	int				mXmx;			//最大内存

	QJsonDocument	mJsonDocument;
};

QGSGame::QGSGame()
{
	d = new Private;

	if (!d)
	{
		throw ExceptionBadAlloc();
	}
}


QGSGame::~QGSGame()
{
	if (d)
	{
		delete d;
	}

	d = nullptr;
}

/*获取游戏版本*/
QString QGSGame::getGameVersion()
{
	//return QString::fromLocal8Bit(mGame.getVersion().c_str());
	return d->mGameVersion;
}

/*获取游戏路径（绝对/相对）*/
QString QGSGame::getGamePath()
{
	//return QString::fromLocal8Bit(mGame.getGamePath().c_str());
	return d->mGamePath;
}

/*获取Java路径*/
QString QGSGame::getJavaPath()
{
	//return QString::fromLocal8Bit(mGame.getJavaPath().c_str());
	return d->mJavaPath;
}

/*获取Native文件夹路径*/
QString QGSGame::getNativePath()
{
	//return QString::fromLocal8Bit(mGame.getNativePath().c_str());
	return d->mNativePath;
}

/*获取用户名*/
QString QGSGame::getPlayerName()
{
	//return QString::fromLocal8Bit(mGame.getPlayerName().c_str());
	return d->mPlayerName;
}

/*获取用户类型*/
QString QGSGame::getUserType()
{
	//return QString::fromLocal8Bit(mGame.getUserType().c_str());
	return d->mUserType;
}

/*获取accessToken*/
QString QGSGame::getAccessToken()
{
	return d->mAccessToken;
}

/*获取clientToken*/
QString QGSGame::getClientToken()
{
	return d->mClientToken;
}

/*获取JVM参数*/
QString QGSGame::getJVMArgument()
{
	return d->mJVMArgument;
}

/*获取前置指令*/
QString QGSGame::getPreInstruction()
{
	return d->mPreInstruction;
}

/*获取直入服务器地址*/
QString QGSGame::getServerAddress()
{
	return d->mServerAddress;
}

/*获取游戏参数*/
QString QGSGame::getGameArgument()
{
	return d->mGameArgument;
}

/*获取最小内存*/
int QGSGame::getXmn()
{
	//return mGame.getXmn();
	return d->mXmn;
}

/*获取最大内存*/
int QGSGame::getXmx()
{
	//return mGame.getXmx();
	return d->mXmx;
}

/**/

void QGSGame::setInitState(const bool state)
{
	d->mInited = state;
}

bool QGSGame::getInitState()const
{
	return d->mInited;
}

void QGSGame::setJsonDocument(const QJsonDocument & jsonDocument)
{
	d->mJsonDocument = jsonDocument;
}
QJsonDocument QGSGame::getJsonDocument()const
{
	return d->mJsonDocument;
}

void QGSGame::setFatherPtr(QGSGame * fatherPtr)
{
	d->mFatherPtr = fatherPtr;
}

QGSGame * QGSGame::getFatherPtr()const
{
	return d->mFatherPtr;
}

/*设置游戏版本*/
void QGSGame::setGameVersion(const QString & gameVersion)
{
	d->mGameVersion = gameVersion;
}

/*设置游戏路径（绝对/相对）*/
void QGSGame::setGamePath(const QString & gamePath)
{
	d->mGamePath = gamePath;
}

/*设置Java路径*/
void QGSGame::setJavaPath(const QString & JavaPath)
{
	d->mJavaPath = JavaPath;
}

/*设置Native文件夹路径*/
void QGSGame::setNativePath(const QString & nativePath)
{
	d->mNativePath = nativePath;
}

/*设置用户名*/
void QGSGame::setPlayerName(const QString & playerName)
{
	d->mPlayerName = playerName;
}

/*设置用户类型*/
void QGSGame::setUserType(const QString & userType)
{
	d->mUserType = userType;
}

/*设置accessToken*/
void QGSGame::setAccessToken(const QString & accessToken)
{
	d->mAccessToken = accessToken;
}

/*设置clientToken*/
void QGSGame::setClientToken(const QString & clientToken)
{
	d->mClientToken = clientToken;
}

/*设置JVM参数*/
void QGSGame::setJVMArgument(const QString & JVMArgument)
{
	d->mJVMArgument = JVMArgument;
}

/*设置前置指令*/
void QGSGame::setPreInstruction(const QString & preInstruction)
{
	d->mPreInstruction = preInstruction;
}

/*设置直入服务器地址*/
void QGSGame::setServerAddress(const QString & serverAddress)
{
	d->mServerAddress = serverAddress;
}

/*设置游戏参数*/
void QGSGame::setGameArgument(const QString & gameArgument)
{
	d->mGameArgument = gameArgument;
}

/*设置最小内存*/
void QGSGame::setXmn(const int Xmn)
{
	d->mXmn = Xmn;
}

/*设置最大内存*/
void QGSGame::setXmx(const int Xmx)
{
	d->mXmx = Xmx;
}
