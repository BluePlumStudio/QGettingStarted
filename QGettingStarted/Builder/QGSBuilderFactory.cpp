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

/*
QGSForgeBuilder * QGSBuilderFactory::createForgeBuilder(QGSForgeVersionInfo & versionInfo, QGSGameDirectory * gameDirectory, QGSDownloadTaskFactory * downloadTaskFactory)
{
	return new QGSForgeBuilder(versionInfo, gameDirectory, downloadTaskFactory);
}
*/