#include "QSolution.h"


QSolution::QSolution()
{
	mUserName.clear();
	mPassword.clear();
	mUserType = 0;
	mJVMArgument.clear();
	mPreInstruction.clear();
	mServerAddress.clear();
	mGameVersion.clear();
	mGamePath.clear();
	mJavaPathVector.clear();
	mCustomJavaPath.clear();
	mJavaPathType = 0;
	mNativePath.clear();
	mNativePathType = 0;
	mXmx = 0;
	mXmn = 0;
}


QSolution::~QSolution()
{
}

/**/

void QSolution::apply()
{
	mJsonObject = QJsonObject();

	mJsonObject.insert("SolutionName", QJsonValue(mSolutionName));

	mJsonObject.insert("UserName", QJsonValue(mUserName));

	mJsonObject.insert("Password", QJsonValue(mPassword));

	mJsonObject.insert("UserType", QJsonValue(mUserType));

	mJsonObject.insert("JVMArgument", QJsonValue(mJVMArgument));

	mJsonObject.insert("PreInstruction", QJsonValue(mPreInstruction));

	mJsonObject.insert("ServerAddress", QJsonValue(mServerAddress));

	mJsonObject.insert("GameVersion", QJsonValue(mGameVersion));

	mJsonObject.insert("GamePath", QJsonValue(mGamePath));

	QJsonArray array;
	for (int i = 0; i < this->mJavaPathVector.size(); i++)
	{
		array.push_back(QJsonValue(this->mJavaPathVector[i]));
	}
	mJsonObject.insert("JavaPathVector", QJsonValue(array));

	mJsonObject.insert("CustomJavaPath", QJsonValue(mCustomJavaPath));

	mJsonObject.insert("JavaPathType", QJsonValue(mJavaPathType));

	mJsonObject.insert("NativePathType", QJsonValue(mNativePathType));
	mJsonObject.insert("NativePath", QJsonValue(mNativePath));

	mJsonObject.insert("Xmx", QJsonValue(mXmx));

	mJsonObject.insert("Xmn", QJsonValue(mXmn));
}

/*
USER_NAME,
PASSWORD,
USER_TYPE,
JVM_ARGUMENT,
PRE_INSTRUCTION,
SERVER_ADDRESS,
GAME_VERSION,
GAME_PATH,
JAVA_PATH_VECTOR,
CUSTOM_JAVA_PATH,
JAVA_PATH_TYPE,
NATIVE_PATH,
NATIVE_PATH_TYPE,
XMX,
XMN
*/

int QSolution::getInt(AttributeFlags attribute)const
{
	int ret = -1;
	switch (attribute)
	{
	case USER_TYPE:
		ret = getUserType();
		break;
	case JAVA_PATH_TYPE:
		ret = getJavaPathType();
		break;
	case NATIVE_PATH_TYPE:
		ret = getNativePathType();
		break;
	case XMX:
		ret = getXmx();
		break;
	case XMN:
		ret = getXmn();
		break;
	default:
		ret = -1;
		break;
	}

	return ret;
}

QString QSolution::getString(AttributeFlags attribute)const
{
	QString ret = "";

	switch (attribute)
	{
	case USER_NAME:
		ret = getUserName();
		break;
	case PASSWORD:
		ret = getPassword();
		break;
	case JVM_ARGUMENT:
		ret = getJVMArgument();
		break;
	case PRE_INSTRUCTION:
		ret = getPreInstruction();
		break;
	case SERVER_ADDRESS:
		ret = getServerAddress();
		break;
	case GAME_VERSION:
		ret = getGameVersion();
		break;
	case GAME_PATH:
		ret = getGamePath();
		break;
	case CUSTOM_JAVA_PATH:
		ret = getCustomJavaPath();
		break;
	case NATIVE_PATH:
		ret = getNativePath();
		break;
	default:
		ret.clear();
		break;
	}

	return ret;
}

QVector<QString> QSolution::getStringVector(AttributeFlags attribute)const
{
	QVector<QString> ret;

	switch (attribute)
	{
	case JAVA_PATH_VECTOR:
		ret = getJavaPathVector();
		break;
	default:
		ret.clear();
		break;
	}

	return ret;
}


void QSolution::setInt(AttributeFlags attribute, int arg)
{
	switch (attribute)
	{
	case USER_TYPE:
		setUserType(arg);
		break;
	case JAVA_PATH_TYPE:
		setJavaPathType(arg);
		break;
	case NATIVE_PATH_TYPE:
		setNativePathType(arg);
		break;
	case XMX:
		setXmx(arg);
		break;
	case XMN:
		setXmn(arg);
		break;
	default:
		break;
	}
}

void QSolution::setString(AttributeFlags attribute, QString arg)
{
	switch (attribute)
	{
	case USER_NAME:
		setUserName(arg);
		break;
	case PASSWORD:
		setPassword(arg);
		break;
	case JVM_ARGUMENT:
		setJVMArgument(arg);
		break;
	case PRE_INSTRUCTION:
		setPreInstruction(arg);
		break;
	case SERVER_ADDRESS:
		setServerAddress(arg);
		break;
	case GAME_VERSION:
		setGameVersion(arg);
		break;
	case GAME_PATH:
		setGamePath(arg);
		break;
	case CUSTOM_JAVA_PATH:
		setCustomJavaPath(arg);
		break;
	case NATIVE_PATH:
		setNativePath(arg);
		break;
	default:
		break;
	}
}

void QSolution::setStringVector(AttributeFlags attribute, QVector<QString> arg)
{
	switch (attribute)
	{
	case JAVA_PATH_VECTOR:
		setJavaPathVector(arg);
		break;
	default:
		break;
	}
}

/**/

void QSolution::loadFromJsonObject(QJsonObject & mJsonObject)
{
	this->mJsonObject = mJsonObject;

	setSolutionName(this->mJsonObject.value("SolutionName").toString());

	setUserName(this->mJsonObject.value("UserName").toString());

	setPassword(this->mJsonObject.value("Password").toString());

	setUserType(this->mJsonObject.value("UserType").toInt());

	setJVMArgument(this->mJsonObject.value("JVMArgument").toString());

	setPassword(this->mJsonObject.value("PreInstruction").toString());

	setServerAddress(this->mJsonObject.value("ServerAddress").toString());

	setGameVersion(this->mJsonObject.value("GameVersion").toString());

	setGamePath(this->mJsonObject.value("GamePath").toString());

	QJsonArray JavaArray = this->mJsonObject.value("JavaPathVector").toArray();
	this->mJavaPathVector.clear();
	for (int i = 0; i < JavaArray.size(); i++)
	{
		this->mJavaPathVector.push_back(JavaArray.at(i).toString());
	}

	setCustomJavaPath(this->mJsonObject.value("CustomJavaPath").toString());

	setJavaPathType(this->mJsonObject.value("JavaPathType").toInt());

	setNativePath(this->mJsonObject.value("NativePath").toString());
	setNativePathType(this->mJsonObject.value("NativePathType").toInt());

	setXmx(this->mJsonObject.value("Xmx").toInt());
	setXmn(this->mJsonObject.value("Xmn").toInt());
}

QString QSolution::getUserName()const
{
	return mUserName;
}

QString QSolution::getPassword()const
{
	return mPassword;
}

int     QSolution::getUserType()const
{
	return mUserType;
}

QString QSolution::getJVMArgument()const
{
	return mJVMArgument;
}

QString QSolution::getPreInstruction()const
{
	return mPreInstruction;
}

QString QSolution::getServerAddress()const
{
	return mServerAddress;
}

QString QSolution::getGameVersion()const
{
	return mGameVersion;
}

QString QSolution::getGamePath()const
{
	return mGamePath;
}

QVector<QString> QSolution::getJavaPathVector()const
{
	return mJavaPathVector;
}

QString QSolution::getCustomJavaPath()const
{
	return mCustomJavaPath;
}

int QSolution::getJavaPathType()const
{
	return mJavaPathType;
}

QString QSolution::getNativePath()const
{
	return mNativePath;
}

int     QSolution::getNativePathType()const
{
	return mNativePathType;
}

int     QSolution::getXmx()const
{
	return mXmx;
}

int     QSolution::getXmn()const
{
	return mXmn;
}

/**/

void QSolution::setUserName(QString userName)
{
	this->mUserName = userName;
}

void QSolution::setPassword(QString password)
{
	this->mPassword = password;
}

void QSolution::setUserType(int     userType)
{
	this->mUserType = userType;
}

void QSolution::setJVMArgument(QString JVMArgument)
{
	this->mJVMArgument = JVMArgument;
}

void QSolution::setPreInstruction(QString preInstruction)
{
	this->mPreInstruction = preInstruction;
}

void QSolution::setServerAddress(QString serverAddress)
{
	this->mServerAddress = serverAddress;
}

void QSolution::setGameVersion(QString gameVersion)
{
	this->mGameVersion = gameVersion;
}

void QSolution::setGamePath(QString gamePath)
{
	this->mGamePath = gamePath;
}

void QSolution::setJavaPathVector(QVector<QString> & mJavaPathVector)
{
	this->mJavaPathVector = mJavaPathVector;
}

void QSolution::setCustomJavaPath(QString customJavaPath)
{
	this->mCustomJavaPath = customJavaPath;
}

void QSolution::setJavaPathType(int JavaPathType)
{
	this->mJavaPathType = JavaPathType;
}

void QSolution::setNativePath(QString nativePath)
{
	this->mNativePath = nativePath;
}

void QSolution::setNativePathType(int     nativePathType)
{
	this->mNativePathType = nativePathType;
}

void QSolution::setXmx(int     Xmx)
{
	this->mXmx = Xmx;
}

void QSolution::setXmn(int     Xmn)
{
	this->mXmn = Xmn;
}

