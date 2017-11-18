#pragma once

#include "Solution.h"

class QSolution :
	public Solution
{
public:
	friend class QConfig;

	QSolution();
	virtual ~QSolution();
public:
	virtual void				apply();

	virtual int					getInt(AttributeFlags attribute)const;
	virtual QString				getString(AttributeFlags attribute)const;
	virtual QVector<QString>	getStringVector(AttributeFlags attribute)const;

	virtual void				setInt(AttributeFlags attribute, const int arg);
	virtual void				setString(AttributeFlags attribute, const QString arg);
	virtual void				setStringVector(AttributeFlags attribute, const QVector<QString> arg);
private:
	void loadFromJsonObject(QJsonObject & jsonObject);

	QString getUserName()const;
	QString getPassword()const;
	int     getUserType()const;
	QString getJVMArgument()const;
	QString getPreInstruction()const;
	QString getServerAddress()const;
	QString getGameVersion()const;
	QString getGamePath()const;
	QVector<QString> getJavaPathVector()const;
	QString getCustomJavaPath()const;
	int     getJavaPathType()const;
	QString getNativePath()const;
	int     getNativePathType()const;
	int     getXmx()const;
	int     getXmn()const;

	void setUserName(QString userName);
	void setPassword(QString password);
	void setUserType(int     userType);
	void setJVMArgument(QString JVMArgument);
	void setPreInstruction(QString preInstruction);
	void setServerAddress(QString serverAddress);
	void setGameVersion(QString gameVersion);
	void setGamePath(QString gamePath);
	void setJavaPathVector(QVector<QString> & JavaPathVector);
	void setCustomJavaPath(QString customJavaPath);
	void setJavaPathType(int JavaPathType);
	void setNativePath(QString nativePath);
	void setNativePathType(int     nativePathType);
	void setXmx(int     Xmx);
	void setXmn(int     Xmn);
private:
	QJsonObject mJsonObject;

	QString mUserName;
	QString mPassword;
	int     mUserType;
	QString mJVMArgument;
	QString mPreInstruction;
	QString mServerAddress;
	QString mGameVersion;
	QString mGamePath;
	QVector<QString> mJavaPathVector;
	QString mCustomJavaPath;
	int     mJavaPathType;
	QString mNativePath;
	int     mNativePathType;
	int     mXmx;
	int     mXmn;

};

