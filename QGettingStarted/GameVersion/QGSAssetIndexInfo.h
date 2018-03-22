#pragma once

#include <QMap>
#include <QString>

class QGSAssetObject
{
public:
	QGSAssetObject(const QString & hash = "", const qint64 & size = 0);

	QGSAssetObject(const QGSAssetObject & right) = default;

	QGSAssetObject(QGSAssetObject && right) = default;

	QGSAssetObject & operator=(const QGSAssetObject & right) = default;

	QGSAssetObject & operator=(QGSAssetObject && right) = default;

	~QGSAssetObject();

	QGSAssetObject & setHash(const QString & hash);
	QGSAssetObject & setSize(const qint64 size);

	QString getHash()const;
	qint64 getSize()const;
private:
	QString mHash;
	qint64 mSize;
};

class QGSAssetIndexInfo
{
public:
	QGSAssetIndexInfo(const bool _virtual = false, const QMap<QString, QGSAssetObject> & assetInfoMap = QMap<QString, QGSAssetObject>());

	QGSAssetIndexInfo(const QGSAssetIndexInfo & right) = default;

	QGSAssetIndexInfo(QGSAssetIndexInfo && right) = default;

	QGSAssetIndexInfo & operator=(const QGSAssetIndexInfo & right) = default;

	QGSAssetIndexInfo & operator=(QGSAssetIndexInfo && right) = default;

	~QGSAssetIndexInfo();

	QGSAssetIndexInfo & setVirtual(const bool _virtual);

	QGSAssetIndexInfo & setAssetObjects(const QMap<QString, QGSAssetObject> & objects);

	bool getVirtual()const;

	QMap<QString, QGSAssetObject> getAssetObjectMap()const;

	QGSAssetObject & getAssetObject(const QString & key);

	bool addAssetObject(const QString & key, const QGSAssetObject & assetObject);

	bool removeAssetObject(const QString & key);

	bool containsAssetObject(const QString & key)const;

	int size();
private:
	bool mVirtual;
	QMap<QString, QGSAssetObject> mAssetObjectMap;
};
