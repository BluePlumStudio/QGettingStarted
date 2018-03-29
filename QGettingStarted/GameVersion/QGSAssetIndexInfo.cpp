#include "QGSAssetIndexInfo.h"

QGSAssetIndexInfo::QGSAssetIndexInfo(const bool _virtual, const QMap<QString, QGSAssetObject> & assetInfoMap)
	:mVirtual(_virtual), mAssetObjectMap(assetInfoMap)
{

}

QGSAssetIndexInfo::~QGSAssetIndexInfo()
{

}

QGSAssetIndexInfo & QGSAssetIndexInfo::setVirtual(const bool _virtual)
{
	mVirtual = _virtual;
	return *this;
}

QGSAssetIndexInfo & QGSAssetIndexInfo::setAssetObjects(const QMap<QString, QGSAssetObject> & objects)
{
	mAssetObjectMap = objects;
	return *this;
}

bool QGSAssetIndexInfo::getVirtual()const
{
	return mVirtual;
}

QMap<QString, QGSAssetObject> QGSAssetIndexInfo::getAssetObjectMap()const
{
	return mAssetObjectMap;
}

QGSAssetObject & QGSAssetIndexInfo::getAssetObject(const QString & key)
{
	return mAssetObjectMap[key];
}

bool QGSAssetIndexInfo::addAssetObject(const QString & key, const QGSAssetObject & assetObject)
{
	if (containsAssetObject(key))
	{
		return false;
	}

	mAssetObjectMap.insert(key, assetObject);
	return true;
}

bool QGSAssetIndexInfo::removeAssetObject(const QString & key)
{
	if (!containsAssetObject(key))
	{
		return false;
	}

	mAssetObjectMap.remove(key);
	return true;
}

bool QGSAssetIndexInfo::containsAssetObject(const QString & key) const
{
	return mAssetObjectMap.contains(key);
}

int QGSAssetIndexInfo::size()
{
	return mAssetObjectMap.size();
}
