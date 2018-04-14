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
## 正式版本已开始推送！

# 开发文档
![QGSDocument](https://qgsdocument.blueplum.studio/index.html)

# 开始
## 使用启动核心
1.下载源码自行编译或下载已编译好的静态库：
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

2.将静态库，如"QGettingStarted.lib，quazip.lib"，添加进工程，包含头文件"QGettingStarted.h"即可。
