# QGettingStarted
[![Build Status](https://travis-ci.org/BluePlumStudio/QGettingStarted.svg?branch=renew)](https://travis-ci.org/BluePlumStudio/QGettingStarted)
[![Gitter](https://badges.gitter.im/Join%20Chat.svg)](https://gitter.im/blueplumstudio?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge) 
## An open-source library for launching and downloading 'Minecraft'.
![logo](https://github.com/BluePlumStudio/QGettingStarted/blob/renew/Logo.png)

 * 启动全版本Minecraft
 * 可拓展登录系统
   * 支持Offline（离线）
   * 支持Yggdrasil（正版）
 * 下载Minecraft
 * 下载Forge/Liteloader/Optifine
   * 支持Liteloader的快照版本
   * 支持自定义下载源（已内置BMCLAPI）
   * 支持多线程下载
   * 支持断点下载
 * Natives解压
 * 网络代理
 * 启动报告（开发中）
 * Java信息查找（Windows Only）

# 编译
Visual Studio 2015/Qt Creator 4.5.0|Qt 5.10.0 下编译通过。

# 警告
## 正式版本已开始推送！

# 开发文档
[QGSDocument](https://qgsdocument.blueplum.studio/index.html)
使用完整功能请查阅开发文档

# 快速开始
## 使用启动核心
1.下载源码自行编译或下载已编译好的静态库：
 * 0.2.0：
- Windows：
[地址1](https://BluePlum.pipipan.com/fs/15016760-289581327)
[地址2](https://BluePlum.ctfile.com/fs/15016760-289581327)

 * 0.1.1：
- Windows：
[地址1](https://BluePlum.pipipan.com/fs/15016760-244159325)
[地址2](https://BluePlum.ctfile.com/fs/15016760-244159325)

 * Pre 2.0.0：
- Windows：
[地址1](https://u15016760.pipipan.com/fs/15016760-242677462)
[地址2](https://u15016760.ctfile.com/fs/15016760-242677462)

 * Beta 1.4.0：
- Windows：
[地址1](https://u15016760.pipipan.com/fs/15016760-241286287)
[地址2](https://u15016760.ctfile.com/fs/15016760-241286287)

 * Beta 1.3.0：
- Windows：
[城通网盘1](https://u15016760.pipipan.com/fs/15016760-241091666)
[城通网盘2](https://u15016760.ctfile.com/fs/15016760-241091666)

 * Beta 1.2.0：
- Windows：
[城通网盘1](https://u15016760.pipipan.com/fs/15016760-241072639)
[城通网盘2](https://u15016760.ctfile.com/fs/15016760-241072639)

 * Beta 1.1.0：
- Windows：
[城通网盘1](https://u15016760.pipipan.com/fs/15016760-239989968)
[城通网盘2](https://u15016760.ctfile.com/fs/15016760-239989968)

 * Beta 1.0.0：
- Windows：
[城通网盘1](https://u15016760.pipipan.com/fs/15016760-239566462)
[城通网盘2](https://u15016760.ctfile.com/fs/15016760-239566462)

2.将静态库，如"QGettingStarted.lib，zlib.lib"，添加进工程，包含头文件"QGettingStarted.h"即可。

# 启动游戏

```cpp
	QString launchCommand;
	QGSLauncher launcher;
	QGSGameDirectory gameDirectory(QDir("./minecraft"));
	QGSLaunchOptionsBuilder launchOptionsBuilder;

	launchOptionsBuilder.setJavaPath("C:/Program Files/Java/jre1.8.0_162/bin/javaw.exe");
	launchOptionsBuilder.setMaxMemory(1024);
	launchOptionsBuilder.setMinMemory(128);

	QGSAuthInfo authInfo;
	QEventLoop eventLoop;
	//正版登录替换为QGSYggdrasilAccountFactory
	QGSIAccount * account(QGSOfflineAccountFactory().createAccount());
	QObject::connect(account, &QGSIAccount::finished, &eventLoop, &QEventLoop::quit);
	QObject::connect(account, &QGSIAccount::finished, [&authInfo](QGSAuthInfo _authInfo)
	{
		authInfo = _authInfo;
	});
	/*正版登录的错误检查
	QObject::connect(account, &QGSIAccount::error, [](QGSNetworkError networkError)
	{
		qDebug() << "QGSNetworkError:" << networkError.getCode() << networkError.getErrorString();
	});
	*/
	account->authenticate("player");
	//account->authenticate("123@xxx.com","123456"); 正版登录
	eventLoop.exec();

	launchOptionsBuilder.setAuthInfo(authInfo);
	launchOptionsBuilder.setJVMArguments("-XX:+UseG1GC -XX:-UseAdaptiveSizePolicy -XX:-OmitStackTraceInFastThrow");

	launcher.generateLaunchCommand(gameDirectory.getVersion("1.11.2"), gameDirectory, launchOptionsBuilder.getLaunchOptions(), launchCommand);
```

# 获取游戏版本列表

```cpp
	//下载任务工厂
	QGSDownloadTaskFactory downloadTaskFactory(new QGSBMCLAPIDownloadSource);
	//下载到当前目录
	QGSDownloadTask * downloadTask = downloadTaskFactory.generateGameVersionInfoJsonDownloadTask(new QFile("./version_manifest.json"));
	//下载进程
	QObject::connect(downloadTask, &QGSDownloadTask::downloadProgress, [=](qint64 bytesReceived, qint64 bytesTotal, QGSTask * task)
	{
		qDebug() << "version manifest:" << bytesReceived << ";" << bytesTotal;
	});
	//下载完成
	QObject::connect(downloadTask, &QGSDownloadTask::finished, [=](QGSTask * task)
	{
		qDebug() << "version manifest prase test";
		QGSGameVersionInfoListFactory versionInfoFactory;
		downloadTask->getTargetFile()->open(QIODevice::ReadOnly);
		QGSGameVersionInfoList versionInfoList(versionInfoFactory.createGameVersionInfoList(downloadTask->getTargetFile()->readAll()));
		for (int i = 0; i < versionInfoList.size(); i++)
		{
			qDebug() << "id:" << versionInfoList[i].getId()
				<< "type:" << versionInfoList[i].getType()
				<< "time:" << versionInfoList[i].getTime()
				<< "releasetime:" << versionInfoList[i].getReleaseTime()
				<< "url:" << versionInfoList[i].getUrl().toString();
		}
		downloadTask->deleteLater();
	});
	//下载错误
	QObject::connect(downloadTask, &QGSDownloadTask::downloadError, [=](QGSNetworkError error, QGSTask * task)
	{
		qDebug() << "version manifest:" << "Code:" << error.getCode() << "Message:" << error.getErrorString();
	});
	downloadTask->start();
```

# 下载游戏（含库、资源补全）

```cpp
	//"version_manifest.json"文件需要自行下载，详见"获取版本列表"
	QFile manifestFile("./version_manifest.json");
	manifestFile.open(QIODevice::ReadOnly);
	QGSGameVersionInfoListFactory versionInfoFactory;
	QGSGameVersionInfoList versionInfoList(versionInfoFactory.createGameVersionInfoList(manifestFile.readAll()));
	QGSIDownloadSource * downloadSource = new QGSBMCLAPIDownloadSource;

	QGSGameVersionInfo versionInfo = versionInfoList.getVersionInfo("1.11.2");
	QGSDownloadTaskFactory downloadTaskFactory(downloadSource);
	//游戏目录
	QGSGameDirectory gameDirectory(QDir("/.minecraft"));
	//线程池。线程池数最小为8，最大为512。
	QGSThreadPoolManager * threadPoolManager(new QGSThreadPoolManager(8, 512));
	//建造者工厂，用于创建游戏各部分的建造者。
	QGSBuilderFactory * builderFactory(new QGSBuilderFactory(threadPoolManager));
	//游戏本体建造者。
	QGSGameVersionBuilder * gameVersionBuilder = builderFactory->createGameVersionBuilder(versionInfo, &gameDirectory, &downloadTaskFactory);
	//库建造者
	QGSLibraryBuilder * libraryBuilder = builderFactory->createLibraryBuilder(versionInfo, &gameDirectory, &downloadTaskFactory);
	//资源建造者
	QGSAssetBuilder * assetBuilder = builderFactory->createAssetBuilder(versionInfo, &gameDirectory, &downloadTaskFactory);
	//前一个任务发出finished(）（完成）信号后即刻执行下一个任务。
	gameVersionBuilder->setNextTask(libraryBuilder).setNextTask(assetBuilder);
	QObject::connect(gameVersionBuilder, &QGSGameVersionBuilder::started, [=]()//建造者开始
	{
		qDebug() << "gameVersionBuilder started!";
	});
	QObject::connect(gameVersionBuilder, &QGSGameVersionBuilder::downloadTaskStarted, [=](QGSDownloadTask * task)//任务开始
	{
		qDebug() << "download:" << task->getDownloadInfo().getUrl() << " started!";
	});
	QObject::connect(gameVersionBuilder, &QGSGameVersionBuilder::downloadTaskFinished, [=](QGSDownloadTask * task)//任务完成
	{
		qDebug() << "download:" << task->getDownloadInfo().getUrl() << " finished!" << gameVersionBuilder->getTaskListSize() << "left!";
		task->deleteLater();
	});
	QObject::connect(gameVersionBuilder, &QGSGameVersionBuilder::downloadTaskStoped, [=](QGSDownloadTask * task)//任务暂停
	{
		qDebug() << "download:" << task->getDownloadInfo().getUrl() << " stoped!";
	});
	QObject::connect(gameVersionBuilder, &QGSGameVersionBuilder::downloadTaskCanceled, [=](QGSDownloadTask * task)//任务取消
	{
		qDebug() << "download:" << task->getDownloadInfo().getUrl() << " canceled!";
		task->deleteLater();
	});
	QObject::connect(gameVersionBuilder, &QGSGameVersionBuilder::downloadTaskDownloadProgress, [](qint64 bytesReceived, qint64 bytesTotal, QGSDownloadTask * task)//任务进程
	{
		qDebug() << "download:" << task->getDownloadInfo().getUrl() << " download progress:" << "bytes received:" << bytesReceived << "bytes total:" << bytesTotal;
	});
	QObject::connect(gameVersionBuilder, &QGSGameVersionBuilder::downloadTaskDownloadError, [=](QGSNetworkError error, QGSDownloadTask * task)//任务错误（同时发出downloadTaskError()）
	{
		qDebug() << "download:" << task->getDownloadInfo().getUrl() << " download error!" << gameVersionBuilder->getTaskListSize() << "left!" << "Error code:" << error.getCode();
	});
	QObject::connect(gameVersionBuilder, &QGSGameVersionBuilder::downloadTaskError, [=](QGSDownloadTask * task)//任务错误
	{
		qDebug() << "download:" << task->getDownloadInfo().getUrl() << " error!" << gameVersionBuilder->getTaskListSize() << "left!";
		task->deleteLater();
	});
	QObject::connect(gameVersionBuilder, &QGSGameVersionBuilder::error, [=]()//建造者错误
	{
		qDebug() << "gameVersionBuilder error!";
	});
	QObject::connect(gameVersionBuilder, &QGSGameVersionBuilder::finished, [=]()//建造者完成
	{
		qDebug() << "gameVersionBuilder finished!";
	});
	//
	QObject::connect(libraryBuilder, &QGSLibraryBuilder::started, [=]()
	{
		qDebug() << "libraryBuilder started!";
	});
	QObject::connect(libraryBuilder, &QGSLibraryBuilder::downloadTaskStarted, [=](QGSDownloadTask * task)
	{
		qDebug() << "download:" << task->getDownloadInfo().getUrl() << " started!";
	});
	QObject::connect(libraryBuilder, &QGSLibraryBuilder::downloadTaskFinished, [=](QGSDownloadTask * task)
	{
		qDebug() << "download:" << task->getDownloadInfo().getUrl() << " finished!" << libraryBuilder->getTaskListSize() << "left!";
		task->deleteLater();
	});
	QObject::connect(libraryBuilder, &QGSLibraryBuilder::downloadTaskStoped, [=](QGSDownloadTask * task)
	{
		qDebug() << "download:" << task->getDownloadInfo().getUrl() << " stoped!";
	});
	QObject::connect(libraryBuilder, &QGSLibraryBuilder::downloadTaskCanceled, [=](QGSDownloadTask * task)
	{
		qDebug() << "download:" << task->getDownloadInfo().getUrl() << " canceled!";
		task->deleteLater();
	});
	QObject::connect(libraryBuilder, &QGSLibraryBuilder::downloadTaskDownloadProgress, [](qint64 bytesReceived, qint64 bytesTotal, QGSDownloadTask * task)
	{
		qDebug() << "download:" << task->getDownloadInfo().getUrl() << " download progress:" << "bytes received:" << bytesReceived << "bytes total:" << bytesTotal;
	});
	QObject::connect(libraryBuilder, &QGSLibraryBuilder::downloadTaskDownloadError, [=](QGSNetworkError error, QGSDownloadTask * task)
	{
		qDebug() << "download:" << task->getDownloadInfo().getUrl() << " download error!" << libraryBuilder->getTaskListSize() << "left!" << "Error code:" << error.getCode();
	});
	QObject::connect(libraryBuilder, &QGSLibraryBuilder::downloadTaskError, [=](QGSDownloadTask * task)
	{
		qDebug() << "download:" << task->getDownloadInfo().getUrl() << " error!" << libraryBuilder->getTaskListSize() << "left!";
		task->deleteLater();
	});
	QObject::connect(libraryBuilder, &QGSLibraryBuilder::error, [=]()
	{
		qDebug() << "libraryBuilder error!";
	});
	QObject::connect(libraryBuilder, &QGSLibraryBuilder::finished, [=]()
	{
		qDebug() << "libraryBuilder finished!";
	});
	//
	QObject::connect(assetBuilder, &QGSLibraryBuilder::started, [=]()
	{
		qDebug() << "assetBuilder started!";
	});
	QObject::connect(assetBuilder, &QGSLibraryBuilder::downloadTaskStarted, [=](QGSDownloadTask * task)
	{
		qDebug() << "download:" << task->getDownloadInfo().getUrl() << " started!";
	});
	QObject::connect(assetBuilder, &QGSLibraryBuilder::downloadTaskFinished, [=](QGSDownloadTask * task)
	{
		qDebug() << "download:" << task->getDownloadInfo().getUrl() << " finished!" << assetBuilder->getTaskListSize() << "left!";
		task->deleteLater();
	});
	QObject::connect(assetBuilder, &QGSLibraryBuilder::downloadTaskStoped, [=](QGSDownloadTask * task)
	{
		qDebug() << "download:" << task->getDownloadInfo().getUrl() << " stoped!";
	});
	QObject::connect(assetBuilder, &QGSLibraryBuilder::downloadTaskCanceled, [=](QGSDownloadTask * task)
	{
		qDebug() << "download:" << task->getDownloadInfo().getUrl() << " canceled!";
		task->deleteLater();
	});
	QObject::connect(assetBuilder, &QGSLibraryBuilder::downloadTaskDownloadProgress, [](qint64 bytesReceived, qint64 bytesTotal, QGSDownloadTask * task)
	{
		qDebug() << "download:" << task->getDownloadInfo().getUrl() << " download progress:" << "bytes received:" << bytesReceived << "bytes total:" << bytesTotal;
	});
	QObject::connect(assetBuilder, &QGSLibraryBuilder::downloadTaskDownloadError, [=](QGSNetworkError error, QGSDownloadTask * task)
	{
		qDebug() << "download:" << task->getDownloadInfo().getUrl() << " download error!" << assetBuilder->getTaskListSize() << "left!" << "Error code:" << error.getCode();
	});
	QObject::connect(assetBuilder, &QGSLibraryBuilder::downloadTaskError, [=](QGSDownloadTask * task)
	{
		qDebug() << "download:" << task->getDownloadInfo().getUrl() << " error!" << assetBuilder->getTaskListSize() << "left!";
		task->deleteLater();
	});
	QObject::connect(assetBuilder, &QGSLibraryBuilder::error, [=]()
	{
		qDebug() << "assetBuilder error!";
	});
	QObject::connect(assetBuilder, &QGSLibraryBuilder::finished, [=]()
	{
		qDebug() << "assetBuilder finished!";
	});
	//将建造者加入线程池
	threadPoolManager->addTaskBack(gameVersionBuilder);
```