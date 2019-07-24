#include "QGSAssetObject.h"

QGSAssetObject::QGSAssetObject(const QString & path, const QString & hash, const qint64 & size)
	:mPath(path), mHash(hash), mSize(size)
{
	if (!QMetaType::isRegistered(QMetaType::type("QGSAssetObject")))
	{
		qRegisterMetaType<QGSAssetObject>("QGSAssetObject");
	}
}

QGSAssetObject::~QGSAssetObject()
{

}

QGSAssetObject & QGSAssetObject::setPath(const QString & path)
{
	mPath = path;
	return *this;
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

QString QGSAssetObject::getPath() const
{
	return mPath;
}

QString QGSAssetObject::getHash() const
{
	return mHash;
}

qint64 QGSAssetObject::getSize() const
{
	return mSize;
}
