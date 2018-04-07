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
Visual Studio 2015/Qt 5.10.0 下编译通过。

# 警告
## Pre阶段的API已经基本定型，请留意最新开发文档。

# 开始
## 使用启动核心
1.下载源码自行编译或下载已编译好的静态库：
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

2.将静态库，如"QGettingStarted.lib，quazip.lib"，添加进工程，包含头文件"QGettingStarted.h"即可。

## 启动Minecraft（Beta）
```cpp
/*启动1.11.2原版为例*/

//Qt
#include <QtCore/QCoreApplication>
#include <QSharedPointer>
//QGettingStarted
#include "QGettingStarted.h"

using namespace std;
using namespace qgs;//核心的名称空间

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	QGSGameDirectory gameDirectory{ QDir(QCoreApplication::applicationDirPath() + "/" + ".minecraft") };

	QGSLauncher launcher{ gameDirectory.getVersion("1.11.2"),gameDirectory };
	
	QGSLaunchOptionsBuilder launchOptionsBuilder;//启动选项建造者
	launchOptionsBuilder.setJavaPath("C:/Program Files/Java/jre1.8.0_121/bin/javaw.exe");//Java路径
	launchOptionsBuilder.setMaxMemory(1024);//最大内存（MB）
	launchOptionsBuilder.setMinMemory(128);//最小内存（MB）
	launchOptionsBuilder.setAuthInfo(QGSOfflineAccountFactory().createAccount()->authenticate("gou"));//用户，这里是离线用户
	//launchOptionsBuilder.setJVMArguments("-XX:+UseG1GC -XX:-UseAdaptiveSizePolicy -XX:-OmitStackTraceInFastThrow");//可选的JVM虚拟机参数
  
	//生成启动命令，生成的命令可以直接用QProcess执行
	QString launchCommand;//启动命令
	launcher.generateLaunchCommand(launchOptionsBuilder.getLaunchOptions(), launchCommand);
  
	return 0;
}
```
## 正版登录
```cpp
	try
	{
		AuthInfo authInfo = QGSYggdrasilAccountFactory().createAccount()->authenticate("gouliguojiashengsiyi@ha.com",
			"+1s+1s+1s");
	}
	catch(const QGSExceptionAuthentication & exception)
	{
		/*异常处理
		QString error{ exception.getError() };
		QString errorMessage{ exception.getErrorMessage() };
		QString cause{ exception.getCause() };
		*/
	}

```
## 下载
* 获取Minecraft版本信息
```cpp
	/*version_manifest.json download test*/
	QSharedPointer<QGSDownloadSourceBMCLAPI> downloadSource{ new QGSDownloadSourceBMCLAPI };
	QGSDownloadManager downloadManager{ downloadSource.data() };
	downloader = downloadManager.generateVersionManifestDownloader();
	QObject::connect(downloader, &QGSDownloader::downloadProgress, [=](qint64 bytesReceived, qint64 bytesTotal)
	{
		/*下载进度*/
	});
	QObject::connect(downloader, &QGSDownloader::finished, [=]() 
	{
		//version_manifest.json prase test
		VersionInfoList versionInfoList{ downloader->getFile() };//Minecraft版本列表
		for (int i = 0; i < versionInfoList.size(); i++)
		{
			qDebug() << "id:" << versionInfoList[i].getId()
				<< "type:" << versionInfoList[i].getType()
				<< "time:" << versionInfoList[i].getTime()
				<< "releasetime:" << versionInfoList[i].getReleaseTime()
				<< "url:" << versionInfoList[i].getUrl().toString();
		}
		downloader->deleteLater();
	});
	QObject::connect(downloader, &QGSDownloader::error, [=](QGSDownloader::Error error)
	{
		/*下载错误*/
	});
	QObject::connect(downloader, &QGSDownloader::timeout, [=]()
	{
		/*下载超时*/
	});
	if (!downloader->start())
	{
		/*开始下载失败*/
	}
	/*...*/
```
* 下载Minecraft本体
```cpp
	/*下载1.9.2为例*/
	
	QSharedPointer<QGSDownloadSourceBMCLAPI> downloadSource{ new QGSDownloadSourceBMCLAPI };
	QGSDownloadManager downloadManager{ downloadSource.data() };
	QGSDownloader * downloader{ downloadManager.generateVersionDownloader("1.9.2", "client") };//服务端填"server"
	/*
	QGSDownloader * generateVersionDownloader(const QString & mcversion, const QString & category, DownloadInfo & downloadInfo = DownloadInfo());
	*/
	QObject::connect(downloader, &QGSDownloader::downloadProgress, [=](qint64 bytesReceived, qint64 bytesTotal)
	{
		/*下载进度*/
	});
	QObject::connect(downloader, &QGSDownloader::finished, downloader, &QObject::deleteLater);
	QObject::connect(downloader, &QGSDownloader::error, [=](QGSDownloader::Error error)
	{
		/*下载错误*/
	});
	if (!downloader->start())
	{
		/*开始下载失败*/
	}
	/*...*/
```
* 下载Forge
```cpp
	/*下载forge-1.12.2-14.23.2.2624-universal.jar为例*/
	
	QSharedPointer<QGSDownloadSourceBMCLAPI> downloadSource{ new QGSDownloadSourceBMCLAPI };
	QGSDownloadManager downloadManager{ downloadSource.data() };
	QGSDownloader * downloader{ downloadManager.generateForgeDownloader("1.12.2","14.23.2.2624","universal","jar") };
	/*
	QGSDownloader * generateForgeDownloader(const QString & mcversion, const QString & version, const QString & category, const QString & format, const QString & branch = "", DownloadInfo & downloadInfo = DownloadInfo());
	*/
	QObject::connect(downloader, &QGSDownloader::downloadProgress, [=](qint64 bytesReceived, qint64 bytesTotal)
	{
		/*下载进度*/
	});
	QObject::connect(downloader, &QGSDownloader::finished, downloader, &QObject::deleteLater);
	QObject::connect(downloader, &QGSDownloader::error, [=](QGSDownloader::Error error)
	{
		/*下载错误*/
	});
	if (!downloader->start())
	{
		/*开始下载失败*/
	}
	/*...*/
```

* 下载LiteLoader
```cpp
	/*下载liteloader-1.7.10为例*/
	
	QSharedPointer<QGSDownloadSourceBMCLAPI> downloadSource{ new QGSDownloadSourceBMCLAPI };
	QGSDownloadManager downloadManager{ downloadSource.data() };
	QGSDownloader * downloader{ downloadManager.generateLiteLoaderDownloader("1.7.10", "1.7.10") };
	/*
	QGSDownloader * generateLiteLoaderDownloader(const QString & version, const QString & mcversion, DownloadInfo & downloadInfo = DownloadInfo());
	*/
	QObject::connect(downloader, &QGSDownloader::downloadProgress, [=](qint64 bytesReceived, qint64 bytesTotal)
	{
		/*下载进度*/
	});
	QObject::connect(downloader, &QGSDownloader::finished, downloader, &QObject::deleteLater);
	QObject::connect(downloader, &QGSDownloader::error, [=](QGSDownloader::Error error)
	{
		/*下载错误*/
	});
	if (!downloader->start())
	{
		/*开始下载失败*/
	}
	/*...*/
```

* 下载Optifine
```cpp
	/*下载optifine-1.9.2-HD_U-D7为例*/
	
	QSharedPointer<QGSDownloadSourceBMCLAPI> downloadSource{ new QGSDownloadSourceBMCLAPI };
	QGSDownloadManager downloadManager{ downloadSource.data() };
	QGSDownloader * downloader{ downloadManager.generateOptifineDownloader("1.9.2", "HD_U", "D7") };
	/*
	QGSDownloader * generateOptifineDownloader(const QString & mcversion, const QString & type, const QString & patch, DownloadInfo & downloadInfo = DownloadInfo());
	*/
	QObject::connect(downloader, &QGSDownloader::downloadProgress, [=](qint64 bytesReceived, qint64 bytesTotal)
	{
		/*下载进度*/
	});
	QObject::connect(downloader, &QGSDownloader::finished, downloader, &QObject::deleteLater);
	QObject::connect(downloader, &QGSDownloader::error, [=](QGSDownloader::Error error)
	{
		/*下载错误*/
	});
	if (!downloader->start())
	{
		/*开始下载失败*/
	}
	/*...*/
```
* 下载Library
```cpp
	/*下载Library*/
	
	QSharedPointer<QGSDownloadSourceBMCLAPI> downloadSource{ new QGSDownloadSourceBMCLAPI };
	QGSDownloadManager downloadManager{ downloadSource.data() };
	QGSDownloader * downloader{ downloadManager.generateLibraryDownloader(library,DownloadInfo{-1,"","D:/.minecraft/libraries/....."}) };
	/*
	QGSDownloader * generateLibraryDownloader(const Library & library, DownloadInfo & downloadInfo = DownloadInfo());

	library：你的library对象
	downloadInfo：参数3：保存路径（可以根据QGSGameDirectory的generateLibraryFile()获取
	*/
	QObject::connect(downloader, &QGSDownloader::downloadProgress, [=](qint64 bytesReceived, qint64 bytesTotal)
	{
		/*下载进度*/
	});
	QObject::connect(downloader, &QGSDownloader::finished, downloader, &QObject::deleteLater);
	QObject::connect(downloader, &QGSDownloader::error, [=](QGSDownloader::Error error)
	{
		/*下载错误*/
	});
	if (!downloader->start())
	{
		/*开始下载失败*/
	}
	/*...*/
```
