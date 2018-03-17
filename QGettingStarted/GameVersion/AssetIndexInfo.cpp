#include "AssetIndexInfo.h"

AssetObject::AssetObject(const QString & hash, const qint64 & size)
	:mHash(hash), mSize(size)
{

}

AssetObject::~AssetObject()
{

}

AssetObject & AssetObject::setHash(const QString & hash)
{
	mHash = hash;
	return *this;
}

AssetObject & AssetObject::setSize(const qint64 size)
{
	mSize = size;
	return *this;
}

QString AssetObject::getHash() const
{
	return mHash;
}

qint64 AssetObject::getSize() const
{
	return mSize;
}

/**/

AssetIndexInfo::AssetIndexInfo(const bool _virtual, const QMap<QString, AssetObject> & assetInfoMap)
	:mVirtual(_virtual), mAssetObjectMap(assetInfoMap)
{

}

AssetIndexInfo::~AssetIndexInfo()
{

}

AssetIndexInfo & AssetIndexInfo::setVirtual(const bool _virtual)
{
	mVirtual = _virtual;
	return *this;
}

AssetIndexInfo & AssetIndexInfo::setAssetObjects(const QMap<QString, AssetObject> & objects)
{
	mAssetObjectMap = objects;
	return *this;
}

bool AssetIndexInfo::getVirtual()const
{
	return mVirtual;
}

QMap<QString, AssetObject> AssetIndexInfo::getAssetObjectMap()const
{
	return mAssetObjectMap;
}

AssetObject & AssetIndexInfo::getAssetObject(const QString & key)
{
	return mAssetObjectMap[key];
}

bool AssetIndexInfo::addAssetObject(const QString & key, const AssetObject & assetObject)
{
	if (containsAssetObject(key))
	{
		return false;
	}

	mAssetObjectMap.insert(key, assetObject);
	return true;
}

bool AssetIndexInfo::removeAssetObject(const QString & key)
{
	if (!containsAssetObject(key))
	{
		return false;
	}

	mAssetObjectMap.remove(key);
	return true;
}

bool AssetIndexInfo::containsAssetObject(const QString & key) const
{
	return mAssetObjectMap.contains(key);
}

int AssetIndexInfo::size()
{
	return mAssetObjectMap.size();
}
