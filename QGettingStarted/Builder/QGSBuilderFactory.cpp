#include "QGSBuilderFactory.h"
#include "../Util/QGSExceptionInvalidValue.h"

QGSBuilderFactory::QGSBuilderFactory(QGSThreadPoolManager * threadPoolManagerPtr, QObject *parent)
	: QObject(parent), mThreadPoolManagerPtr(threadPoolManagerPtr)
{
	if (!mThreadPoolManagerPtr)
	{
		throw QGSExceptionInvalidValue();
	}
}

QGSBuilderFactory::~QGSBuilderFactory()
{
}

QGSGameVersionBuilder * QGSBuilderFactory::createGameVersionBuilder(QGSGameVersionInfo & versionInfo, QGSGameDirectory * gameDirectory, QGSDownloadTaskFactory * downloadTaskFactory)
{
	return new QGSGameVersionBuilder(mThreadPoolManagerPtr, versionInfo, gameDirectory, downloadTaskFactory);
}

QGSLibraryBuilder * QGSBuilderFactory::createLibraryBuilder(QGSGameVersionInfo & versionInfo, QGSGameDirectory * gameDirectory, QGSDownloadTaskFactory * downloadTaskFactory)
{
	return new QGSLibraryBuilder(mThreadPoolManagerPtr, versionInfo, gameDirectory, downloadTaskFactory);
}

QGSAssetBuilder * QGSBuilderFactory::createAssetBuilder(QGSGameVersionInfo & versionInfo, QGSGameDirectory * gameDirectory, QGSDownloadTaskFactory * downloadTaskFactory)
{
	return new QGSAssetBuilder(mThreadPoolManagerPtr, versionInfo, gameDirectory, downloadTaskFactory);
}

/*
QGSForgeBuilder * QGSBuilderFactory::createForgeBuilder(QGSForgeVersionInfo & versionInfo, QGSGameDirectory * gameDirectory, QGSDownloadTaskFactory * downloadTaskFactory)
{
	return new QGSForgeBuilder(versionInfo, gameDirectory, downloadTaskFactory);
}
*/