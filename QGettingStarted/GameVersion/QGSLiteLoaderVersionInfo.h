#pragma once

#include <QString>
#include <QMap>

#include "QGSLiteLoaderVersionReposity.h"
#include "QGSLiteLoaderVersionMeta.h"

class QGSLiteLoaderVersionInfo
{
public:
	QGSLiteLoaderVersionInfo();

	QGSLiteLoaderVersionInfo(const QGSLiteLoaderVersionInfo & right) = default;

	QGSLiteLoaderVersionInfo(QGSLiteLoaderVersionInfo && right) = default;

	QGSLiteLoaderVersionInfo & operator=(const QGSLiteLoaderVersionInfo & right) = default;

	QGSLiteLoaderVersionInfo & operator=(QGSLiteLoaderVersionInfo && right) = default;

	~QGSLiteLoaderVersionInfo();

	QGSLiteLoaderVersionReposity getLiteLoaderVersionReposity()const;
	QMap<QString, QGSLiteLoaderVersionMeta> getLiteLoaderVersionSnapshotMetaMap()const;
	QMap<QString, QGSLiteLoaderVersionMeta> getLiteLoaderVersionArtefactMetaMap()const;

	QGSLiteLoaderVersionInfo & setLiteLoaderVersionReposity(const QGSLiteLoaderVersionReposity & liteLoaderVersionReposity);
	QGSLiteLoaderVersionInfo & setLiteLoaderVersionSnapshotMetaMap(const QMap<QString, QGSLiteLoaderVersionMeta> & liteLoaderVersionSnapshotMetaMap);
	QGSLiteLoaderVersionInfo & setLiteLoaderVersionArtefactMetaMap(const QMap<QString, QGSLiteLoaderVersionMeta> & liteLoaderVersionArtefactMetaMap);
private:
	QGSLiteLoaderVersionReposity mLiteLoaderVersionReposity;
	QMap<QString, QGSLiteLoaderVersionMeta> mLiteLoaderVersionSnapshotMetaMap;
	QMap<QString, QGSLiteLoaderVersionMeta> mLiteLoaderVersionArtefactMetaMap;
};
