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
	QGSGame *		mFatherPtr;	//�̳���Ϸ�汾

	QString			mGameVersion;	//��Ϸ�汾
	QString			mGamePath;		//��Ϸ·��
	QString			mJavaPath;		//Java·��
	QString			mNativePath;	//native�ļ���·��
	QString			mPlayerName;	//�û���
	QString			mUserType;		//�û�����
	QString			mAccessToken;	//accessToken
	QString			mClientToken;	//clientToken
	QString			mJVMArgument;	//JVM����
	QString			mPreInstruction;//ǰ��ָ��
	QString			mServerAddress; //������ֱ����ַ
	QString			mGameArgument;  //��Ϸ����
	int				mXmn;			//��С�ڴ�
	int				mXmx;			//����ڴ�

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

/*��ȡ��Ϸ�汾*/
QString QGSGame::getGameVersion()
{
	//return QString::fromLocal8Bit(mGame.getVersion().c_str());
	return d->mGameVersion;
}

/*��ȡ��Ϸ·��������/��ԣ�*/
QString QGSGame::getGamePath()
{
	//return QString::fromLocal8Bit(mGame.getGamePath().c_str());
	return d->mGamePath;
}

/*��ȡJava·��*/
QString QGSGame::getJavaPath()
{
	//return QString::fromLocal8Bit(mGame.getJavaPath().c_str());
	return d->mJavaPath;
}

/*��ȡNative�ļ���·��*/
QString QGSGame::getNativePath()
{
	//return QString::fromLocal8Bit(mGame.getNativePath().c_str());
	return d->mNativePath;
}

/*��ȡ�û���*/
QString QGSGame::getPlayerName()
{
	//return QString::fromLocal8Bit(mGame.getPlayerName().c_str());
	return d->mPlayerName;
}

/*��ȡ�û�����*/
QString QGSGame::getUserType()
{
	//return QString::fromLocal8Bit(mGame.getUserType().c_str());
	return d->mUserType;
}

/*��ȡaccessToken*/
QString QGSGame::getAccessToken()
{
	return d->mAccessToken;
}

/*��ȡclientToken*/
QString QGSGame::getClientToken()
{
	return d->mClientToken;
}

/*��ȡJVM����*/
QString QGSGame::getJVMArgument()
{
	return d->mJVMArgument;
}

/*��ȡǰ��ָ��*/
QString QGSGame::getPreInstruction()
{
	return d->mPreInstruction;
}

/*��ȡֱ���������ַ*/
QString QGSGame::getServerAddress()
{
	return d->mServerAddress;
}

/*��ȡ��Ϸ����*/
QString QGSGame::getGameArgument()
{
	return d->mGameArgument;
}

/*��ȡ��С�ڴ�*/
int QGSGame::getXmn()
{
	//return mGame.getXmn();
	return d->mXmn;
}

/*��ȡ����ڴ�*/
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

/*������Ϸ�汾*/
void QGSGame::setGameVersion(const QString & gameVersion)
{
	d->mGameVersion = gameVersion;
}

/*������Ϸ·��������/��ԣ�*/
void QGSGame::setGamePath(const QString & gamePath)
{
	d->mGamePath = gamePath;
}

/*����Java·��*/
void QGSGame::setJavaPath(const QString & JavaPath)
{
	d->mJavaPath = JavaPath;
}

/*����Native�ļ���·��*/
void QGSGame::setNativePath(const QString & nativePath)
{
	d->mNativePath = nativePath;
}

/*�����û���*/
void QGSGame::setPlayerName(const QString & playerName)
{
	d->mPlayerName = playerName;
}

/*�����û�����*/
void QGSGame::setUserType(const QString & userType)
{
	d->mUserType = userType;
}

/*����accessToken*/
void QGSGame::setAccessToken(const QString & accessToken)
{
	d->mAccessToken = accessToken;
}

/*����clientToken*/
void QGSGame::setClientToken(const QString & clientToken)
{
	d->mClientToken = clientToken;
}

/*����JVM����*/
void QGSGame::setJVMArgument(const QString & JVMArgument)
{
	d->mJVMArgument = JVMArgument;
}

/*����ǰ��ָ��*/
void QGSGame::setPreInstruction(const QString & preInstruction)
{
	d->mPreInstruction = preInstruction;
}

/*����ֱ���������ַ*/
void QGSGame::setServerAddress(const QString & serverAddress)
{
	d->mServerAddress = serverAddress;
}

/*������Ϸ����*/
void QGSGame::setGameArgument(const QString & gameArgument)
{
	d->mGameArgument = gameArgument;
}

/*������С�ڴ�*/
void QGSGame::setXmn(const int Xmn)
{
	d->mXmn = Xmn;
}

/*��������ڴ�*/
void QGSGame::setXmx(const int Xmx)
{
	d->mXmx = Xmx;
}
