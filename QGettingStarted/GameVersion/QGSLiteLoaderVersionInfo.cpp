#include "QGSLiteLoaderVersionInfo.h"

QGSLiteLoaderVersionInfo::QGSLiteLoaderVersionInfo()
{

}

QGSLiteLoaderVersionInfo::~QGSLiteLoaderVersionInfo()
{

}

QGSLiteLoaderVersionReposity QGSLiteLoaderVersionInfo::getLiteLoaderVersionReposity() const
{
	return mLiteLoaderVersionReposity;
}

QMap<QString, QGSLiteLoaderVersionMeta> QGSLiteLoaderVersionInfo::getLiteLoaderVersionSnapshotMetaMap()const
{
	return mLiteLoaderVersionSnapshotMetaMap;
}

QMap<QString, QGSLiteLoaderVersionMeta> QGSLiteLoaderVersionInfo::getLiteLoaderVersionArtefactMetaMap() const
{
	return mLiteLoaderVersionArtefactMetaMap;
}

QGSLiteLoaderVersionInfo & QGSLiteLoaderVersionInfo::setLiteLoaderVersionReposity(const QGSLiteLoaderVersionReposity & liteLoaderVersionReposity)
{
	mLiteLoaderVersionReposity = liteLoaderVersionReposity;
	return *this;
}

QGSLiteLoaderVersionInfo & QGSLiteLoaderVersionInfo::setLiteLoaderVersionSnapshotMetaMap(const QMap<QString, QGSLiteLoaderVersionMeta> & liteLoaderVersionSnapshotMetaMap)
{
	mLiteLoaderVersionSnapshotMetaMap = liteLoaderVersionSnapshotMetaMap;
	return *this;
}

QGSLiteLoaderVersionInfo & QGSLiteLoaderVersionInfo::setLiteLoaderVersionArtefactMetaMap(const QMap<QString, QGSLiteLoaderVersionMeta>& liteLoaderVersionArtefactMetaMap)
{
	mLiteLoaderVersionArtefactMetaMap = liteLoaderVersionArtefactMetaMap;
	return *this;
}
