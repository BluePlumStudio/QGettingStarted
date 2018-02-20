#pragma once

#include <QMap>
#include <QString>

class Asset
{
public:
	class Object
	{
	public:
		Object()
		{

		}
		~Object()
		{

		}

	private:
		QString mHash;
		qint64 mSize;
	};

public:
	Asset();
	~Asset();

private:
	bool mVirtual;
	QMap<QString, Object> mObjects;
};
