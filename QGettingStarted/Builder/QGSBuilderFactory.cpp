#include "QGSBuilderFactory.h"

QGSBuilderFactory::QGSBuilderFactory(QObject *parent)
	: QObject(parent)
{
}

QGSBuilderFactory::~QGSBuilderFactory()
{
}

QGSGameVersionBuilder * QGSBuilderFactory::createGameVersionBuilder(QGSGameVersionInfo & versionInfo, QGSGameDirectory * gameDirectory, QGSDownloadTaskFactory * downloadTaskFactory)
{
	return new QGSGameVersionBuilder(versionInfo, gameDirectory, downloadTaskFactory);
}

QGSLibraryBuilder * QGSBuilderFactory::createLibraryBuilder(QGSGameVersionInfo & versionInfo, QGSGameDirectory * gameDirectory, QGSDownloadTaskFactory * downloadTaskFactory)
{
	return new QGSLibraryBuilder(versionInfo, gameDirectory, downloadTaskFactory);
}

QGSAssetBuilder * QGSBuilderFactory::createAssetBuilder(QGSGameVersionInfo & versionInfo, QGSGameDirectory * gameDirectory, QGSDownloadTaskFactory * downloadTaskFactory)
{
	return new QGSAssetBuilder(versionInfo, gameDirectory, downloadTaskFactory);
}

/*
QGSForgeBuilder * QGSBuilderFactory::createForgeBuilder(QGSForgeVersionInfo & versionInfo, QGSGameDirectory * gameDirectory, QGSDownloadTaskFactory * downloadTaskFactory)
{
	return new QGSForgeBuilder(versionInfo, gameDirectory, downloadTaskFactory);
}
*/