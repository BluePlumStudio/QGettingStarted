#include "QGSAssetIndex.h"

QGSAssetIndex::QGSAssetIndex(const int size, const QString & SHA1, const QString & path, const QUrl & url, const qint64 totalSize, const QString & id)
	:QGSDownloadBase(size, SHA1, path, url), mTotalSize(totalSize), mId(id)
{

}

QGSAssetIndex::~QGSAssetIndex()
{

}

QGSAssetIndex & QGSAssetIndex::setTotalSize(const qint64 totalSize)
{
	mTotalSize = totalSize;
	return *this;
}

QGSAssetIndex & QGSAssetIndex::setId(const QString & id)
{
	mId = id;
	return *this;
}

qint64 QGSAssetIndex::getTotalSize()const
{
	return mTotalSize;
}

QString QGSAssetIndex::getId()const
{
	return mId;
}

void QGSAssetIndex::clear()
{
	mTotalSize = 0;
	mId.clear();
	QGSDownloadBase::clear();
}