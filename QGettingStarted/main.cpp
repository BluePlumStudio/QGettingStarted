#include <QtCore/QCoreApplication>
#include <QSharedPointer>
#include <QTextStream>
#include <QDebug>
#include <QTemporaryFile>
#include <iostream>
#include <string>

#include "QGettingStarted.h"

using namespace std;
using namespace qgs;

void generateLaunchCommandTest()
{
	while (true)
	{
		cout << "游戏路径：";
		string directory;
		getline(cin, directory);
		QGSGameDirectory gameDirectory{ QDir(QString::fromLocal8Bit(directory.c_str())) };

		cout << "游戏版本：";
		string version;
		getline(cin, version);
		QGSLauncher launcher{ gameDirectory.getVersion(QString::fromLocal8Bit(version.c_str())),gameDirectory };

		QGSLaunchOptionsBuilder launchOptionsBuilder;
		QString launchCommand;
		/*
		cout << "Java路径：";
		string JavaPath;
		getline(cin, JavaPath);
		*/
		launchOptionsBuilder.setJavaPath("C:/Program Files/Java/jre1.8.0_162/bin/javaw.exe");
		launchOptionsBuilder.setMaxMemory(1024);
		launchOptionsBuilder.setMinMemory(128);
		/*
		cout << "用户名：";
		string userName;
		getline(cin, userName);
		launchOptionsBuilder.setAuthInfo(QGSOfflineAccountFactory().createAccount()->authenticate(QString::fromLocal8Bit(userName.c_str())));
		*/
		launchOptionsBuilder.setAuthInfo(QGSOfflineAccountFactory().createAccount()->authenticate("uiufqr7386@yeah.net", ""));
		launchOptionsBuilder.setJVMArguments("-XX:+UseG1GC -XX:-UseAdaptiveSizePolicy -XX:-OmitStackTraceInFastThrow");
		/*
		launchOptionsBuilder.setWrapper("前置指令");
		launchOptionsBuilder.setServerInfo(QGSLaunchOptions::ServerInfo("serveraddress.com"));
		launchOptionsBuilder.setGameArguments("游戏参数");
		launchOptionsBuilder.setWindowSize({ 480,854 });
		launchOptionsBuilder.setFullScreen(true);
		launchOptionsBuilder.setMetaspaceSize(8888);
		launchOptionsBuilder.setProxy(QNetworkProxy("proxyaddress", "proxyport", "proxyuser", "proxypassword"));
		*/
		if (launcher.generateLaunchCommand(launchOptionsBuilder.getLaunchOptions(), launchCommand) != LauncherError::Ok)
		{
			qDebug() << "生成启动脚本失败";
			return;
		}

		QFile launchCommandFile;
		launchCommandFile.setFileName(QCoreApplication::applicationDirPath() + "/" + QString::fromStdString(version) + ".bat");
		launchCommandFile.open(QIODevice::Text | QIODevice::WriteOnly | QIODevice::Truncate);
		QTextStream testStream(&launchCommandFile);
		testStream << launchCommand.toUtf8();
		launchCommandFile.close();
	}
}

int downloadTest()
{
	QSharedPointer<QGSIDownloadSource> downloadSource{ new QGSDownloadSourceBMCLAPI };
	QGSDownloadTaskFactory downloadManager{ downloadSource.data() };
	QGSDownloadTask * downloadTask;
	QGSGameDirectory gameDirectory{ QDir{QCoreApplication::applicationDirPath() + "/.minecraft"} };

	//forge download test
	downloadTask = downloadManager.generateForgeDownloadTask(new QFile{ QString{ QCoreApplication::applicationDirPath() + "/forge.zip" } }, "1.4.7", "6.6.1.530", "src", "zip");
	QObject::connect(downloadTask, &QGSDownloadTask::downloadProgress, [=](qint64 bytesReceived, qint64 bytesTotal, QGSTask * task)
	{
		cout << "Forge:" << bytesReceived << ";" << bytesTotal << endl;
	});
	QObject::connect(downloadTask, &QGSDownloadTask::finished, downloadTask, &QObject::deleteLater);
	QObject::connect(downloadTask, &QGSDownloadTask::downloadError, [=](QGSDownloadTask::QGSDownloadError error, QGSTask * task)
	{
		qDebug() << "Forge:" << "Code:" << error.getCode() << "Message:" << error.getMessage();
	});
	QObject::connect(downloadTask, &QGSDownloadTask::timeout, [=]()
	{
		qDebug() << "Forge:" << "timeout";
	});
	downloadTask->start();
	//liteloader download test
	downloadTask = downloadManager.generateLiteLoaderDownloadTask(new QFile{ QString{ QCoreApplication::applicationDirPath() + "/liteloader.jar" } }, "1.11.2", "1.11.2-SNAPSHOT", "installer");
	QObject::connect(downloadTask, &QGSDownloadTask::downloadProgress, [=](qint64 bytesReceived, qint64 bytesTotal, QGSTask * task)
	{
		cout << "LiteLoader:" << bytesReceived << ";" << bytesTotal << endl;
	});
	QObject::connect(downloadTask, &QGSDownloadTask::finished, downloadTask, &QObject::deleteLater);
	QObject::connect(downloadTask, &QGSDownloadTask::downloadError, [=](QGSDownloadTask::QGSDownloadError error, QGSTask * task)
	{
		qDebug() << "LiteLoader:" << "Code:" << error.getCode() << "Message:" << error.getMessage();
	});
	QObject::connect(downloadTask, &QGSDownloadTask::timeout, [=]()
	{
		qDebug() << "LiteLoader:" << "timeout";
	});
	downloadTask->start();
	//optifine download test
	downloadTask = downloadManager.generateOptifineDownloadTask(new QFile{ QString{ QCoreApplication::applicationDirPath() + "/optifine.zip" } }, "1.9.2", "HD_U", "D7");
	QObject::connect(downloadTask, &QGSDownloadTask::downloadProgress, [=](qint64 bytesReceived, qint64 bytesTotal, QGSTask * task)
	{
		cout << "Optifine:" << bytesReceived << ";" << bytesTotal << endl;
	});
	QObject::connect(downloadTask, &QGSDownloadTask::finished, downloadTask, &QObject::deleteLater);
	QObject::connect(downloadTask, &QGSDownloadTask::downloadError, [=](QGSDownloadTask::QGSDownloadError error, QGSTask * task)
	{
		qDebug() << "Optifine:" << "Code:" << error.getCode() << "Message:" << error.getMessage();
	});
	QObject::connect(downloadTask, &QGSDownloadTask::timeout, [=]()
	{
		qDebug() << "Optifine:" << "timeout";
	});
	downloadTask->start();
	//version download test
	QGSGameVersion version;
	QMap<QString, QGSDownloads::QGSIDownload> downloads;
	downloads.insert("client",
		QGSDownloads::QGSIDownload{ 8736083,"4a61c873be90bb1196d68dac7b29870408c56969","",QUrl("https://launcher.mojang.com/mc/game/1.9.4/client/4a61c873be90bb1196d68dac7b29870408c56969/client.jar") });
	version.setDownloads(downloads);
	version.setId("1.9.4");
	downloadTask = downloadManager.generateGameVersionDownloadTask(version, gameDirectory, "client");
	QObject::connect(downloadTask, &QGSDownloadTask::downloadProgress, [=](qint64 bytesReceived, qint64 bytesTotal, QGSTask * task)
	{
		cout << "version:" << bytesReceived << ";" << bytesTotal << endl;
	});
	QObject::connect(downloadTask, &QGSDownloadTask::finished, downloadTask, &QObject::deleteLater);
	QObject::connect(downloadTask, &QGSDownloadTask::downloadError, [=](QGSDownloadTask::QGSDownloadError error, QGSTask * task)
	{
		qDebug() << "version:" << "Code:" << error.getCode() << "Message:" << error.getMessage();
	});
	QObject::connect(downloadTask, &QGSDownloadTask::timeout, [=]()
	{
		qDebug() << "version:" << "timeout";
	});
	downloadTask->start();
	//library download test
	QGSLibrary library;
	library.setPackage("com.mojang");
	library.setName("netty");
	library.setVersion("1.6");
	downloadTask = downloadManager.generateLibraryDownloadTask(library, gameDirectory);
	QObject::connect(downloadTask, &QGSDownloadTask::downloadProgress, [=](qint64 bytesReceived, qint64 bytesTotal, QGSTask * task)
	{
		cout << "QGSLibrary:" << bytesReceived << ";" << bytesTotal << endl;
	});
	QObject::connect(downloadTask, &QGSDownloadTask::finished, downloadTask, &QObject::deleteLater);
	QObject::connect(downloadTask, &QGSDownloadTask::downloadError, [=](QGSDownloadTask::QGSDownloadError error, QGSTask * task)
	{
		qDebug() << "QGSLibrary:" << "Code:" << error.getCode() << "Message:" << error.getMessage();
	});
	QObject::connect(downloadTask, &QGSDownloadTask::timeout, [=]()
	{
		qDebug() << "QGSLibrary:" << "timeout";
	});
	downloadTask->start();
	//version manifest download test
	downloadTask = downloadManager.generateGameVersionInfoJsonDownloadTask(new QFile{ QString{ QCoreApplication::applicationDirPath() + "/version_manifest.json" } });
	QObject::connect(downloadTask, &QGSDownloadTask::downloadProgress, [=](qint64 bytesReceived, qint64 bytesTotal, QGSTask * task)
	{
		cout << "version manifest:" << bytesReceived << ";" << bytesTotal << endl;
	});
	QObject::connect(downloadTask, &QGSDownloadTask::finished, [=](QGSTask * task)
	{
		//version manifest prase test
		qDebug() << "version manifest prase test";
		QGSGameVersionInfoListFactory versionInfoFactory;
		downloadTask->getTargetFile()->open(QIODevice::ReadOnly);
		QGSGameVersionInfoList versionInfoList{ versionInfoFactory.createGameVersionInfoList(downloadTask->getTargetFile()->readAll()) };
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
	QObject::connect(downloadTask, &QGSDownloadTask::downloadError, [=](QGSDownloadTask::QGSDownloadError error, QGSTask * task)
	{
		qDebug() << "version manifest:" << "Code:" << error.getCode() << "Message:" << error.getMessage();
	});
	downloadTask->start();
	//forge version download test
	downloadTask = downloadManager.generateForgeVersionInfoJsonDownloadTask(new QFile{ QString{ QCoreApplication::applicationDirPath() + "/forge_manifest.json" } }, 100, 50);
	QObject::connect(downloadTask, &QGSDownloadTask::downloadProgress, [=](qint64 bytesReceived, qint64 bytesTotal, QGSTask * task)
	{
		cout << "forge version:" << bytesReceived << ";" << bytesTotal << endl;
	});
	QObject::connect(downloadTask, &QGSDownloadTask::finished, [=](QGSTask * task)
	{
		//forge version prase test
		qDebug() << "forge version prase test";
		QGSForgeVersionInfoListFactory versionInfoFactory;
		downloadTask->getTargetFile()->open(QIODevice::ReadOnly);
		QGSForgeVersionInfoList versionInfoList{ versionInfoFactory.createForgeVersionInfoList(downloadTask->getTargetFile()->readAll(),1,1000) };
		versionInfoList.merge(versionInfoList);
		for (int i = 0; i < versionInfoList.size(); i++)
		{
			qDebug() << "branch" << versionInfoList[i].getBranch()
				<< "build" << versionInfoList[i].getBuild()
				<< "mcversion" << versionInfoList[i].getMcversion()
				<< "modified" << versionInfoList[i].getModified()
				<< "version" << versionInfoList[i].getVersion()
				<< "_id" << versionInfoList[i].getId();

		}
		downloadTask->deleteLater();
	});
	QObject::connect(downloadTask, &QGSDownloadTask::downloadError, [=](QGSDownloadTask::QGSDownloadError error, QGSTask * task)
	{
		qDebug() << "forge version:" << "Code:" << error.getCode() << "Message:" << error.getMessage();
	});
	downloadTask->start();
	//liteloader version download test
	downloadTask = downloadManager.generateLiteLoaderVersionInfoJsonDownloadTask(new QFile{ QString{ QCoreApplication::applicationDirPath() + "/liteloader_manifest.json" } });
	QObject::connect(downloadTask, &QGSDownloadTask::downloadProgress, [=](qint64 bytesReceived, qint64 bytesTotal, QGSTask * task)
	{
		cout << "liteloader manifest:" << bytesReceived << ";" << bytesTotal << endl;
	});
	QObject::connect(downloadTask, &QGSDownloadTask::finished, [=](QGSTask * task)
	{
		//liteloader manifest prase test
		qDebug() << "liteloader manifest prase test";
		QGSLiteLoaderVersionInfoListFactory versionInfoFactory;
		downloadTask->getTargetFile()->open(QIODevice::ReadOnly);
		QGSLiteLoaderVersionInfoList versionInfoList{ versionInfoFactory.createLiteLoaderVersionInfoList(downloadTask->getTargetFile()->readAll()) };
		for (int i = 0; i < versionInfoList.size(); i++)
		{
			qDebug() << versionInfoList[i].getLiteLoaderVersionReposity().getUrl();
		}
		downloadTask->deleteLater();
	});
	QObject::connect(downloadTask, &QGSDownloadTask::downloadError, [=](QGSDownloadTask::QGSDownloadError error, QGSTask * task)
	{
		qDebug() << "liteloader manifest:" << "Code:" << error.getCode() << "Message:" << error.getMessage();
	});
	downloadTask->start();
	//optifine version download test
	downloadTask = downloadManager.generateOptifineVersionInfoJsonDownloadTask(new QFile{ QString{ QCoreApplication::applicationDirPath() + "/optifine_manifest.json" } });
	QObject::connect(downloadTask, &QGSDownloadTask::downloadProgress, [=](qint64 bytesReceived, qint64 bytesTotal, QGSTask * task)
	{
		cout << "optifine manifest:" << bytesReceived << ";" << bytesTotal << endl;
	});
	QObject::connect(downloadTask, &QGSDownloadTask::finished, [=](QGSTask * task)
	{
		//optifine manifest prase test
		qDebug() << "optifine manifest prase test";
		QGSOptifineVersionInfoListFactory versionInfoFactory;
		downloadTask->getTargetFile()->open(QIODevice::ReadOnly);
		QGSOptifineVersionInfoList versionInfoList{ versionInfoFactory.createOptifineVersionInfoList(downloadTask->getTargetFile()->readAll()) };
		for (int i = 0; i < versionInfoList.size(); i++)
		{
			qDebug() << versionInfoList[i].getFileName();
		}
		downloadTask->deleteLater();
	});
	QObject::connect(downloadTask, &QGSDownloadTask::downloadError, [=](QGSDownloadTask::QGSDownloadError error, QGSTask * task)
	{
		qDebug() << "optifine manifest:" << "Code:" << error.getCode() << "Message:" << error.getMessage();
	});
	downloadTask->start();
	return 0;
}

void gameBuildTest()
{
	QSharedPointer<QGSIDownloadSource> downloadSource{ new QGSDownloadSourceOfficial };
	QGSDownloadTaskFactory downloadManager{ downloadSource.data() };
	QGSDownloadTask * downloadTask;
	QGSGameDirectory gameDirectory{ QDir{ QCoreApplication::applicationDirPath() + "/.minecraft" } };

	static QGSGameVersionInfo versionInfo;

	downloadTask = downloadManager.generateGameVersionInfoJsonDownloadTask(new QFile{ QString{ QCoreApplication::applicationDirPath() + "/version_manifest.json" } });
	downloadTask->start();
	QEventLoop eventLoop;
	QObject::connect(downloadTask, &QGSDownloadTask::finished, [&](QGSTask * task)
	{
		QGSGameVersionInfoListFactory versionInfoFactory;
		downloadTask->getTargetFile()->open(QIODevice::ReadOnly);
		QGSGameVersionInfoList versionInfoList{ versionInfoFactory.createGameVersionInfoList(downloadTask->getTargetFile()->readAll()) };
		versionInfo = versionInfoList.getVersionInfo("1.11.2");
		downloadTask->deleteLater();
		eventLoop.quit();
		qDebug() << "version manifest:" << "finished!";
	});
	eventLoop.exec();

	downloadTask = downloadManager.generateGameVersionJsonDownloadTask(versionInfo, gameDirectory);
	downloadTask->start();
	QObject::connect(downloadTask, &QGSDownloadTask::finished, [&](QGSTask * task)
	{
		downloadTask->deleteLater();
		eventLoop.quit();
		qDebug() << "version json:" << "finished!";
	});
	eventLoop.exec();

	auto & version{ gameDirectory.getVersion("1.11.2") };
	downloadTask = downloadManager.generateGameVersionDownloadTask(version, gameDirectory, "client");
	downloadTask->start();
	QObject::connect(downloadTask, &QGSDownloadTask::finished, [&](QGSTask * task)
	{
		downloadTask->deleteLater();
		eventLoop.quit();
		qDebug() << "version:" << "finished!";
	});
	eventLoop.exec();

	auto & libraryList{ version.getLibraries() };
	qDebug() << "library count:" << libraryList.size();
	for (auto & i : libraryList)
	{
		downloadTask = downloadManager.generateLibraryDownloadTask(i, gameDirectory);
		downloadTask->start();
		QObject::connect(downloadTask, &QGSDownloadTask::finished, [=](QGSTask * task)
		{
			qDebug() << "library:" << "finished!";
			downloadTask->deleteLater();
		});
		QObject::connect(downloadTask, &QGSDownloadTask::timeout, [=](QGSTask * task)
		{
			qDebug() << "library:" << "timeout!";
		});
		QObject::connect(downloadTask, &QGSDownloadTask::error, [=](QGSTask * task)
		{
			qDebug() << "library:" << "error!";
		});
	}

	static QGSAssetIndexInfo assetIndexInfo;
	downloadTask = downloadManager.generateAssetIndexJsonDownloadTask(version.getAssetIndex(), gameDirectory);
	downloadTask->start();
	QObject::connect(downloadTask, &QGSDownloadTask::finished, [&](QGSTask * task)
	{
		
		QGSAssetIndexInfoFactory versionInfoFactory;
		downloadTask->getTargetFile()->open(QIODevice::ReadOnly);
		assetIndexInfo = versionInfoFactory.createAssetIndexInfo(downloadTask->getTargetFile()->readAll());
		downloadTask->deleteLater();
		eventLoop.quit();
		qDebug() << "asset index json:" << "finished!";
	});
	eventLoop.exec();

	auto && assetObjectMap{ assetIndexInfo.getAssetObjectMap() };
	for (auto & i : assetObjectMap)
	{
		downloadTask = downloadManager.generateAssetObjectDownloadTask(i, gameDirectory);
		downloadTask->start();
		QObject::connect(downloadTask, &QGSDownloadTask::finished, [=](QGSTask * task)
		{
			qDebug() << "asset object:" << "finished!";
			downloadTask->deleteLater();
		});
		QObject::connect(downloadTask, &QGSDownloadTask::timeout, [=](QGSTask * task)
		{
			qDebug() << "asset object:" << "timeout!";
		});
		QObject::connect(downloadTask, &QGSDownloadTask::error, [=](QGSTask * task)
		{
			qDebug() << "asset object:" << "error!";
		});
	}
}

void threadPoolTest()
{

}

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	qDebug() << "=QGettingStart Test=";

	//threadPoolTest();
	downloadTest();
	//gameBuildTest();
	//generateLaunchCommandTest();

	return a.exec();
}
