#include "QGSAssetObject.h"

QGSAssetObject::QGSAssetObject(const QString & hash, const qint64 & size)
	:mHash(hash), mSize(size)
{

}

QGSAssetObject::~QGSAssetObject()
{

}

QGSAssetObject & QGSAssetObject::setHash(const QString & hash)
{
	mHash = hash;
	return *this;
}

QGSAssetObject & QGSAssetObject::setSize(const qint64 size)
{
	mSize = size;
	return *this;
}

QString QGSAssetObject::getHash() const
{
	return mHash;
}

qint64 QGSAssetObject::getSize() const
{
	return mSize;
}
