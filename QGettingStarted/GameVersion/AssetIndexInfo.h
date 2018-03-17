#pragma once

#include <QMap>
#include <QString>

class AssetObject
{
public:
	AssetObject(const QString & hash = "", const qint64 & size = 0);

	AssetObject(const AssetObject & right) = default;

	AssetObject(AssetObject && right) = default;

	AssetObject & operator=(const AssetObject & right) = default;

	AssetObject & operator=(AssetObject && right) = default;

	~AssetObject();

	AssetObject & setHash(const QString & hash);
	AssetObject & setSize(const qint64 size);

	QString getHash()const;
	qint64 getSize()const;
private:
	QString mHash;
	qint64 mSize;
};

class AssetIndexInfo
{
public:
	AssetIndexInfo(const bool _virtual = false, const QMap<QString, AssetObject> & assetInfoMap = QMap<QString, AssetObject>());

	AssetIndexInfo(const AssetIndexInfo & right) = default;

	AssetIndexInfo(AssetIndexInfo && right) = default;

	AssetIndexInfo & operator=(const AssetIndexInfo & right) = default;

	AssetIndexInfo & operator=(AssetIndexInfo && right) = default;

	~AssetIndexInfo();

	AssetIndexInfo & setVirtual(const bool _virtual);

	AssetIndexInfo & setAssetObjects(const QMap<QString, AssetObject> & objects);

	bool getVirtual()const;

	QMap<QString, AssetObject> getAssetObjectMap()const;

	AssetObject & getAssetObject(const QString & key);

	bool addAssetObject(const QString & key, const AssetObject & assetObject);

	bool removeAssetObject(const QString & key);

	bool containsAssetObject(const QString & key)const;

	int size();
private:
	bool mVirtual;
	QMap<QString, AssetObject> mAssetObjectMap;
};
