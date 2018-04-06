#pragma once

#include <QObject>

//#include "QGSForgeBuilder.h"
#include "QGSGameVersionBuilder.h"
#include "QGSLibraryBuilder.h"
#include "QGSAssetBuilder.h"

class QGSBuilderFactory : public QObject
{
	Q_OBJECT

public:
	QGSBuilderFactory(QObject *parent = nullptr);

	QGSBuilderFactory(const QGSBuilderFactory & right) = delete;

	QGSBuilderFactory(QGSBuilderFactory && right) = delete;

	QGSBuilderFactory & operator=(const QGSBuilderFactory & right) = delete;

	QGSBuilderFactory & operator=(QGSBuilderFactory && right) = delete;

	virtual ~QGSBuilderFactory();

	QGSGameVersionBuilder * createGameVersionBuilder(QGSGameVersionInfo & versionInfo, QGSGameDirectory * gameDirectory, QGSDownloadTaskFactory * downloadTaskFactory);

	QGSLibraryBuilder * createLibraryBuilder(QGSGameVersionInfo & versionInfo, QGSGameDirectory * gameDirectory, QGSDownloadTaskFactory * downloadTaskFactory);

	QGSAssetBuilder * createAssetBuilder(QGSGameVersionInfo & versionInfo, QGSGameDirectory * gameDirectory, QGSDownloadTaskFactory * downloadTaskFactory);

	//QGSForgeBuilder * createForgeBuilder(QGSForgeVersionInfo & versionInfo, QGSGameDirectory * gameDirectory, QGSDownloadTaskFactory * downloadTaskFactory);
};
