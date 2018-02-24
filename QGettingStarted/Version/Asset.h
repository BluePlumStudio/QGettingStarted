#pragma once

#include <QMap>
#include <QString>

class Asset
{
public:
	class Object
	{
	public:
		Object(const QString & hash = "", const qint64 & size = 0) :mHash(hash), mSize(size)
		{

		}

		Object(const Object & right) = default;

		Object(Object && right) = default;

		Object & operator=(const Object & right) = default;

		Object & operator=(Object && right) = default;

		~Object()
		{

		}

	private:
		QString mHash;
		qint64 mSize;
	};

public:
	Asset(const QMap<QString, Object> & objects = QMap<QString, Object>(), const bool _virtual = true);

	Asset(const Asset & right) = default;

	Asset(Asset && right) = default;

	Asset & operator=(const Asset & right) = default;

	Asset & operator=(Asset && right) = default;

	~Asset();

	Asset & setVirtual(const bool _virtual);

	Asset & setObjects(const QMap<QString, Object> & objects);

	bool getVirtual()const;

	QMap<QString, Object> getObjects()const;

private:
	bool mVirtual;
	QMap<QString, Object> mObjects;
};
