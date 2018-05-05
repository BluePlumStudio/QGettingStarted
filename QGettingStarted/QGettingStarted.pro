#-------------------------------------------------
#
# Project created by QtCreator 2018-04-06T22:23:08
#
#-------------------------------------------------

QT       += network sql

QT       -= gui

TARGET = QGettingStarted
TEMPLATE = lib
CONFIG += staticlib

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0




HEADERS += \
    Builder/QGSAssetBuilder.h \
    Builder/QGSAssetIndexJsonDownloadTaskGenerationTask.h \
    Builder/QGSAssetObjectDownloadTaskGenerationTask.h \
    Builder/QGSBuilderFactory.h \
    Builder/QGSDownloadTaskGenerationTask.h \
    Builder/QGSGameVersionBuilder.h \
    Builder/QGSGameVersionDownloadTaskGenerationTask.h \
    Builder/QGSGameVersionJsonDownloadTaskGenerationTask.h \
    Builder/QGSIBuilder.h \
    Builder/QGSLibraryBuilder.h \
    Download/QGSAssetIndexJsonDownloadTask.h \
    Download/QGSAssetObjectDownloadTask.h \
    Download/QGSBMCLAPIDownloadSource.h \
    Download/QGSDownloader.h \
    Download/QGSDownloadInfo.h \
    Download/QGSDownloadTask.h \
    Download/QGSDownloadTaskFactory.h \
    Download/QGSForgeDownloadTask.h \
    Download/QGSGameVersionDownloadTask.h \
    Download/QGSGameVersionJsonDownloadTask.h \
    Download/QGSIDownloadSource.h \
    Download/QGSLibraryDownloadTask.h \
    Download/QGSLiteLoaderDownloadTask.h \
    Download/QGSOfficialDownloadSource.h \
    Download/QGSOptifineDownloadTask.h \
    GameVersion/QGSArguments.h \
    GameVersion/QGSAssetIndex.h \
    GameVersion/QGSAssetIndexInfo.h \
    GameVersion/QGSAssetIndexInfoFactory.h \
    GameVersion/QGSAssetObject.h \
    GameVersion/QGSDownloads.h \
    GameVersion/QGSExtract.h \
    GameVersion/QGSForgeVersionInfo.h \
    GameVersion/QGSForgeVersionInfoList.h \
    GameVersion/QGSForgeVersionInfoListFactory.h \
    GameVersion/QGSGameVersion.h \
    GameVersion/QGSGameVersionInfo.h \
    GameVersion/QGSGameVersionInfoList.h \
    GameVersion/QGSGameVersionInfoListFactory.h \
    GameVersion/QGSLibrary.h \
    GameVersion/QGSLiteLoaderVersionInfo.h \
    GameVersion/QGSLiteLoaderVersionInfoList.h \
    GameVersion/QGSLiteLoaderVersionInfoListFactory.h \
    GameVersion/QGSLiteLoaderVersionMeta.h \
    GameVersion/QGSLiteLoaderVersionReposity.h \
    GameVersion/QGSLogging.h \
    GameVersion/QGSOptifineVersionInfo.h \
    GameVersion/QGSOptifineVersionInfoList.h \
    GameVersion/QGSOptifineVersionInfoListFactory.h \
    GameVersion/QGSRules.h \
    Launcher/QGSGameDirectory.h \
    Launcher/QGSGameVersionPraser.h \
    Launcher/QGSGeneralGameVersionPraseStrategy.h \
    Launcher/QGSGeneralLauncherStrategy.h \
    Launcher/QGSIGameVersionPraseStrategy.h \
    Launcher/QGSILauncherStrategy.h \
    Launcher/QGSLauncher.h \
    LaunchOptions/QGSAuthInfo.h \
    LaunchOptions/QGSIAccount.h \
    LaunchOptions/QGSIAccountFactory.h \
    LaunchOptions/QGSILaunchOptionsBuilder.h \
    LaunchOptions/QGSLaunchOptions.h \
    LaunchOptions/QGSLaunchOptionsBuilder.h \
    LaunchOptions/QGSOfflineAccount.h \
    LaunchOptions/QGSOfflineAccountFactory.h \
    LaunchOptions/QGSYggdrasilAccount.h \
    LaunchOptions/QGSYggdrasilAccountFactory.h \
    Util/zlib/crypt.h \
    Util/zlib/inffast.h \
    Util/zlib/inflate.h \
    Util/zlib/inftrees.h \
    Util/zlib/ioapi.h \
    Util/zlib/iowin32.h \
    Util/zlib/mztools.h \
    Util/zlib/unzip.h \
    Util/zlib/zconf.h \
    Util/zlib/zip.h \
    Util/zlib/zlib.h \
    Util/zlib/zutil.h \
    Util/QGSException.h \
    Util/QGSExceptionAuthentication.h \
    Util/QGSExceptionCompress.h \
    Util/QGSExceptionInvalidValue.h \
    Util/QGSExceptionIO.h \
    Util/QGSExceptionJsonPraseError.h \
    Util/QGSExceptionVersionNotFound.h \
    Util/QGSFileTools.h \
    Util/QGSNetworkAccessManager.h \
    Util/QGSOperatingSystem.h \
    Util/QGSTask.h \
    Util/QGSTaskThread.h \
    Util/QGSThreadPool.h \
    Util/QGSUuidGenerator.h \
    QGettingStarted.h \
    Util/QGSThreadPoolManager.h

SOURCES += \
    Builder/QGSAssetBuilder.cpp \
    Builder/QGSAssetIndexJsonDownloadTaskGenerationTask.cpp \
    Builder/QGSAssetObjectDownloadTaskGenerationTask.cpp \
    Builder/QGSBuilderFactory.cpp \
    Builder/QGSDownloadTaskGenerationTask.cpp \
    Builder/QGSGameVersionBuilder.cpp \
    Builder/QGSGameVersionDownloadTaskGenerationTask.cpp \
    Builder/QGSGameVersionJsonDownloadTaskGenerationTask.cpp \
    Builder/QGSIBuilder.cpp \
    Builder/QGSLibraryBuilder.cpp \
    Download/QGSAssetIndexJsonDownloadTask.cpp \
    Download/QGSAssetObjectDownloadTask.cpp \
    Download/QGSBMCLAPIDownloadSource.cpp \
    Download/QGSDownloader.cpp \
    Download/QGSDownloadInfo.cpp \
    Download/QGSDownloadTask.cpp \
    Download/QGSDownloadTaskFactory.cpp \
    Download/QGSForgeDownloadTask.cpp \
    Download/QGSGameVersionDownloadTask.cpp \
    Download/QGSGameVersionJsonDownloadTask.cpp \
    Download/QGSIDownloadSource.cpp \
    Download/QGSLibraryDownloadTask.cpp \
    Download/QGSLiteLoaderDownloadTask.cpp \
    Download/QGSOfficialDownloadSource.cpp \
    Download/QGSOptifineDownloadTask.cpp \
    GameVersion/QGSArguments.cpp \
    GameVersion/QGSAssetIndex.cpp \
    GameVersion/QGSAssetIndexInfo.cpp \
    GameVersion/QGSAssetIndexInfoFactory.cpp \
    GameVersion/QGSAssetObject.cpp \
    GameVersion/QGSDownloads.cpp \
    GameVersion/QGSExtract.cpp \
    GameVersion/QGSForgeVersionInfo.cpp \
    GameVersion/QGSForgeVersionInfoList.cpp \
    GameVersion/QGSForgeVersionInfoListFactory.cpp \
    GameVersion/QGSGameVersion.cpp \
    GameVersion/QGSGameVersionInfo.cpp \
    GameVersion/QGSGameVersionInfoList.cpp \
    GameVersion/QGSGameVersionInfoListFactory.cpp \
    GameVersion/QGSLibrary.cpp \
    GameVersion/QGSLiteLoaderVersionInfo.cpp \
    GameVersion/QGSLiteLoaderVersionInfoList.cpp \
    GameVersion/QGSLiteLoaderVersionInfoListFactory.cpp \
    GameVersion/QGSLiteLoaderVersionMeta.cpp \
    GameVersion/QGSLiteLoaderVersionReposity.cpp \
    GameVersion/QGSLogging.cpp \
    GameVersion/QGSOptifineVersionInfo.cpp \
    GameVersion/QGSOptifineVersionInfoList.cpp \
    GameVersion/QGSOptifineVersionInfoListFactory.cpp \
    GameVersion/QGSRules.cpp \
    Launcher/QGSGameDirectory.cpp \
    Launcher/QGSGameVersionPraser.cpp \
    Launcher/QGSGeneralGameVersionPraseStrategy.cpp \
    Launcher/QGSGeneralLauncherStrategy.cpp \
    Launcher/QGSIGameVersionPraseStrategy.cpp \
    Launcher/QGSILauncherStrategy.cpp \
    Launcher/QGSLauncher.cpp \
    LaunchOptions/QGSAuthInfo.cpp \
    LaunchOptions/QGSIAccount.cpp \
    LaunchOptions/QGSIAccountFactory.cpp \
    LaunchOptions/QGSILaunchOptionsBuilder.cpp \
    LaunchOptions/QGSLaunchOptions.cpp \
    LaunchOptions/QGSLaunchOptionsBuilder.cpp \
    LaunchOptions/QGSOfflineAccount.cpp \
    LaunchOptions/QGSOfflineAccountFactory.cpp \
    LaunchOptions/QGSYggdrasilAccount.cpp \
    LaunchOptions/QGSYggdrasilAccountFactory.cpp \
    Util/QGSException.cpp \
    Util/QGSExceptionAuthentication.cpp \
    Util/QGSExceptionCompress.cpp \
    Util/QGSExceptionInvalidValue.cpp \
    Util/QGSExceptionIO.cpp \
    Util/QGSExceptionJsonPraseError.cpp \
    Util/QGSExceptionVersionNotFound.cpp \
    Util/QGSFileTools.cpp \
    Util/QGSNetworkAccessManager.cpp \
    Util/QGSOperatingSystem.cpp \
    Util/QGSTask.cpp \
    Util/QGSTaskThread.cpp \
    Util/QGSThreadPool.cpp \
    Util/QGSUuidGenerator.cpp \
    main.cpp \
    Util/zlib/inffas86.c \
    Util/zlib/ioapi.c \
    Util/zlib/iowin32.c \
    Util/zlib/mztools.c \
    Util/zlib/unzip.c \
    Util/zlib/zip.c \
    Util/QGSThreadPoolManager.cpp


unix|win32: LIBS += -L$$PWD/Util/zlib/lib/ -lz

INCLUDEPATH += $$PWD/Util/zlib
DEPENDPATH += $$PWD/Util/zlib

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/Util/zlib/lib/z.lib
else:unix|win32-g++: PRE_TARGETDEPS += $$PWD/Util/zlib/lib/libz.a
