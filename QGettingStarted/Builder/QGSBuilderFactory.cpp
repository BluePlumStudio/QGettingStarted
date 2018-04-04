#include "QGSBuilderFactory.h"

QGSBuilderFactory::QGSBuilderFactory(QObject *parent)
	: QObject(parent)
{
}

QGSBuilderFactory::~QGSBuilderFactory()
{
}

QGSGameBuilder * QGSBuilderFactory::createGameBuilder(QGSGameVersionInfo & versionInfo, QGSGameDirectory * gameDirectory, QGSDownloadTaskFactory * downloadTaskFactory)
{
	return new QGSGameBuilder(versionInfo, gameDirectory, downloadTaskFactory);
}

QGSForgeBuilder * QGSBuilderFactory::createForgeBuilder(QGSForgeVersionInfo & versionInfo, QGSGameDirectory * gameDirectory, QGSDownloadTaskFactory * downloadTaskFactory)
{
	return new QGSForgeBuilder(versionInfo, gameDirectory, downloadTaskFactory);
}
