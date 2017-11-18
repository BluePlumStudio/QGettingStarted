#pragma once

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonValue>
#include <QString>
#include <QFile>
#include <QVector>
#include <QPair>

typedef int AttributeFlags;

enum Attribute
{
	USER_NAME = 0x0001,
	PASSWORD = 0x0002,
	USER_TYPE = 0x0004,
	JVM_ARGUMENT = 0x0008,
	PRE_INSTRUCTION = 0x0010,
	SERVER_ADDRESS = 0x0020,
	GAME_VERSION = 0x0040,
	GAME_PATH = 0x0080,
	JAVA_PATH_VECTOR = 0x0100,
	CUSTOM_JAVA_PATH = 0x0200,
	JAVA_PATH_TYPE = 0x0400,
	NATIVE_PATH = 0x0800,
	NATIVE_PATH_TYPE = 0x1000,
	XMX = 0x2000,
	XMN = 0x4000,
};

class Solution
{
public:
	Solution()
	{

	}

	virtual ~Solution()
	{

	}
public:
	virtual void				apply() = 0;

	QString						getSolutionName()
	{
		return mSolutionName;
	}
	void						setSolutionName(QString solutionName)
	{
		mSolutionName = solutionName;
	}

	virtual int					getInt(AttributeFlags)const = 0;
	virtual QString				getString(AttributeFlags)const = 0;
	virtual QVector<QString>	getStringVector(AttributeFlags)const = 0;

	virtual void					setInt(AttributeFlags, const int) = 0;
	virtual void				setString(AttributeFlags, const QString) = 0;
	virtual void	setStringVector(AttributeFlags, const QVector<QString>) = 0;
protected:
	QString mSolutionName;
};

