#include "AssetIndex.h"

AssetIndex::AssetIndex(
	const int size, const QString & SHA1, const QString & path, const QUrl & url, const qint64 totalSize, const QString & id)
	:Downloads::Download(size, SHA1, path, url), mTotalSize(totalSize), mId(id)
{

}

AssetIndex::~AssetIndex()
{

}

AssetIndex & AssetIndex::setTotalSize(const qint64 totalSize)
{
	mTotalSize = totalSize;
	return *this;
}

AssetIndex & AssetIndex::setId(const QString & id)
{
	mId = id;
	return *this;
}

qint64 AssetIndex::getTotalSize()const
{
	return mTotalSize;
}

QString AssetIndex::getId()const
{
	return mId;
}