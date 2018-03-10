# QGettingStarted
[![Build Status](https://travis-ci.org/BluePlumStudio/QGettingStarted.svg?branch=renew)](https://travis-ci.org/BluePlumStudio/QGettingStarted)
[![Gitter](https://badges.gitter.im/Join%20Chat.svg)](https://gitter.im/blueplumstudio?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge) 
## An open-source library for launching and downloading 'Minecraft'.

 * 启动全版本Minecraft
 * 可拓展登录系统
   * 支持Offline（离线）
   * 支持Yggdrasil（正版）
 * 下载Minecraft（开发中）
 * 下载Forge/Liteloader（开发中）
   * 支持Liteloader的快照版本
   * 支持自定义下载源
   * 支持多线程下载
   * 支持断点下载
 * Natives解压

# 编译
Visual Studio 2015/Qt 5.10.0 下编译通过。

# 警告
## Beta阶段的API可能与最终版本有所出入，请留意最新开发文档。

# 开始
## 使用启动核心
1.下载源码自行编译或下载已编译好的静态库（已更新到Beta 1.2.0）：
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

2.将静态库，如"QGettingStarted.lib"，添加进工程，包含头文件"QGettingStarted.h"即可。

## 启动Minecraft
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
