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
	QGSDownloaderFactory downloadManager{ downloadSource.data() };
	QGSDownloader * downloader;
	QGSGameDirectory gameDirectory{ QDir{QCoreApplication::applicationDirPath() + "/.minecraft"} };

	//forge download test
	downloader = downloadManager.generateForgeDownloader(new QFile{ QString{ QCoreApplication::applicationDirPath() + "/forge.zip" } }, "1.4.7", "6.6.1.530", "src", "zip");
	QObject::connect(downloader, &QGSDownloader::downloadProgress, [=](qint64 bytesReceived, qint64 bytesTotal)
	{
		cout << "Forge:" << bytesReceived << ";" << bytesTotal << endl;
	});
	QObject::connect(downloader, &QGSDownloader::finished, downloader, &QObject::deleteLater);
	QObject::connect(downloader, &QGSDownloader::error, [=](QGSDownloader::Error error)
	{
		qDebug() << "Forge:" << "Code:" << error.getCode() << "Message:" << error.getMessage();
	});
	QObject::connect(downloader, &QGSDownloader::timeout, [=]()
	{
		qDebug() << "Forge:" << "timeout";
	});
	if (!downloader->start())
	{
		qDebug() << "Forge:" << "start failed";
		return 1;
	}
	//liteloader download test
	downloader = downloadManager.generateLiteLoaderDownloader(new QFile{ QString{ QCoreApplication::applicationDirPath() + "/liteloader.jar" } }, "1.11.2", "1.11.2-SNAPSHOT", "installer");
	QObject::connect(downloader, &QGSDownloader::downloadProgress, [=](qint64 bytesReceived, qint64 bytesTotal)
	{
		cout << "LiteLoader:" << bytesReceived << ";" << bytesTotal << endl;
	});
	QObject::connect(downloader, &QGSDownloader::finished, downloader, &QObject::deleteLater);
	QObject::connect(downloader, &QGSDownloader::error, [=](QGSDownloader::Error error)
	{
		qDebug() << "LiteLoader:" << "Code:" << error.getCode() << "Message:" << error.getMessage();
	});
	QObject::connect(downloader, &QGSDownloader::timeout, [=]()
	{
		qDebug() << "LiteLoader:" << "timeout";
	});
	if (!downloader->start())
	{
		qDebug() << "LiteLoader:" << "start failed";
		return 1;
	}
	//optifine download test
	downloader = downloadManager.generateOptifineDownloader(new QFile{ QString{ QCoreApplication::applicationDirPath() + "/optifine.zip" } }, "1.9.2", "HD_U", "D7");
	QObject::connect(downloader, &QGSDownloader::downloadProgress, [=](qint64 bytesReceived, qint64 bytesTotal)
	{
		cout << "Optifine:" << bytesReceived << ";" << bytesTotal << endl;
	});
	QObject::connect(downloader, &QGSDownloader::finished, downloader, &QObject::deleteLater);
	QObject::connect(downloader, &QGSDownloader::error, [=](QGSDownloader::Error error)
	{
		qDebug() << "Optifine:" << "Code:" << error.getCode() << "Message:" << error.getMessage();
	});
	QObject::connect(downloader, &QGSDownloader::timeout, [=]()
	{
		qDebug() << "Optifine:" << "timeout";
	});
	if (!downloader->start())
	{
		qDebug() << "Optifine:" << "start failed";
		return 1;
	}
	//version download test
	GameVersion version;
	QMap<QString, Downloads::Download> downloads;
	downloads.insert("client",
		Downloads::Download{ 8736083,"4a61c873be90bb1196d68dac7b29870408c56969","",QUrl("https://launcher.mojang.com/mc/game/1.9.4/client/4a61c873be90bb1196d68dac7b29870408c56969/client.jar") });
	version.setDownloads(downloads);
	version.setId("1.9.4");
	downloader = downloadManager.generateGameVersionDownloader(version, gameDirectory, "client");
	QObject::connect(downloader, &QGSDownloader::downloadProgress, [=](qint64 bytesReceived, qint64 bytesTotal)
	{
		cout << "version:" << bytesReceived << ";" << bytesTotal << endl;
	});
	QObject::connect(downloader, &QGSDownloader::finished, downloader, &QObject::deleteLater);
	QObject::connect(downloader, &QGSDownloader::error, [=](QGSDownloader::Error error)
	{
		qDebug() << "version:" << "Code:" << error.getCode() << "Message:" << error.getMessage();
	});
	QObject::connect(downloader, &QGSDownloader::timeout, [=]()
	{
		qDebug() << "version:" << "timeout";
	});
	if (!downloader->start())
	{
		qDebug() << "version:" << "start failed";
		return 1;
	}
	//library download test
	Library library;
	library.setPackage("com.mojang");
	library.setName("netty");
	library.setVersion("1.6");
	downloader = downloadManager.generateLibraryDownloader(library, gameDirectory);
	QObject::connect(downloader, &QGSDownloader::downloadProgress, [=](qint64 bytesReceived, qint64 bytesTotal)
	{
		cout << "Library:" << bytesReceived << ";" << bytesTotal << endl;
	});
	QObject::connect(downloader, &QGSDownloader::finished, downloader, &QObject::deleteLater);
	QObject::connect(downloader, &QGSDownloader::error, [=](QGSDownloader::Error error)
	{
		qDebug() << "Library:" << "Code:" << error.getCode() << "Message:" << error.getMessage();
	});
	QObject::connect(downloader, &QGSDownloader::timeout, [=]()
	{
		qDebug() << "Library:" << "timeout";
	});
	if (!downloader->start())
	{
		qDebug() << "Library:" << "start failed";
		return 1;
	}
	//version manifest download test
	downloader = downloadManager.generateGameVersionInfoJsonDownloader(new QFile{ QString{ QCoreApplication::applicationDirPath() + "/version_manifest.json" } });
	QObject::connect(downloader, &QGSDownloader::downloadProgress, [=](qint64 bytesReceived, qint64 bytesTotal)
	{
		cout << "version manifest:" << bytesReceived << ";" << bytesTotal << endl;
	});
	QObject::connect(downloader, &QGSDownloader::finished, [=]()
	{
		//version manifest prase test
		qDebug() << "version manifest prase test";
		QGSGameVersionInfoListFactory versionInfoFactory;
		downloader->getTargetFile()->open(QIODevice::ReadOnly);
		GameVersionInfoList versionInfoList{ versionInfoFactory.createGameVersionInfoList(downloader->getTargetFile()->readAll()) };
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
		qDebug() << "version manifest:" << "Code:" << error.getCode() << "Message:" << error.getMessage();
	});
	if (!downloader->start())
	{
		qDebug() << "version manifest:" << "start failed";
		return 1;
	}
	//forge version download test
	downloader = downloadManager.generateForgeVersionInfoJsonDownloader(new QFile{ QString{ QCoreApplication::applicationDirPath() + "/forge_manifest.json" } }, 100, 50);
	QObject::connect(downloader, &QGSDownloader::downloadProgress, [=](qint64 bytesReceived, qint64 bytesTotal)
	{
		cout << "forge version:" << bytesReceived << ";" << bytesTotal << endl;
	});
	QObject::connect(downloader, &QGSDownloader::finished, [=]()
	{
		//forge version prase test
		qDebug() << "forge version prase test";
		QGSForgeVersionInfoListFactory versionInfoFactory;
		downloader->getTargetFile()->open(QIODevice::ReadOnly);
		ForgeVersionInfoList versionInfoList{ versionInfoFactory.createForgeVersionInfoList(downloader->getTargetFile()->readAll(),1,1000) };
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
		downloader->deleteLater();
	});
	QObject::connect(downloader, &QGSDownloader::error, [=](QGSDownloader::Error error)
	{
		qDebug() << "forge version:" << "Code:" << error.getCode() << "Message:" << error.getMessage();
	});
	if (!downloader->start())
	{
		qDebug() << "forge version:" << "start failed";
		return 1;
	}
	//liteloader version download test
	downloader = downloadManager.generateLiteLoaderVersionInfoJsonDownloader(new QFile{ QString{ QCoreApplication::applicationDirPath() + "/liteloader_manifest.json" } });
	QObject::connect(downloader, &QGSDownloader::downloadProgress, [=](qint64 bytesReceived, qint64 bytesTotal)
	{
		cout << "liteloader manifest:" << bytesReceived << ";" << bytesTotal << endl;
	});
	QObject::connect(downloader, &QGSDownloader::finished, [=]()
	{
		//liteloader manifest prase test
		qDebug() << "liteloader manifest prase test";
		QGSLiteLoaderVersionInfoListFactory versionInfoFactory;
		downloader->getTargetFile()->open(QIODevice::ReadOnly);
		LiteLoaderVersionInfoList versionInfoList{ versionInfoFactory.createLiteLoaderVersionInfoList(downloader->getTargetFile()->readAll()) };
		for (int i = 0; i < versionInfoList.size(); i++)
		{
			qDebug() << versionInfoList[i].getLiteLoaderVersionReposity().getUrl();
		}
		downloader->deleteLater();
	});
	QObject::connect(downloader, &QGSDownloader::error, [=](QGSDownloader::Error error)
	{
		qDebug() << "liteloader manifest:" << "Code:" << error.getCode() << "Message:" << error.getMessage();
	});
	if (!downloader->start())
	{
		qDebug() << "liteloader manifest:" << "start failed";
		return 1;
	}
	//optifine version download test
	downloader = downloadManager.generateOptifineVersionInfoJsonDownloader(new QFile{ QString{ QCoreApplication::applicationDirPath() + "/optifine_manifest.json" } });
	QObject::connect(downloader, &QGSDownloader::downloadProgress, [=](qint64 bytesReceived, qint64 bytesTotal)
	{
		cout << "optifine manifest:" << bytesReceived << ";" << bytesTotal << endl;
	});
	QObject::connect(downloader, &QGSDownloader::finished, [=]()
	{
		//optifine manifest prase test
		qDebug() << "optifine manifest prase test";
		QGSOptifineVersionInfoListFactory versionInfoFactory;
		downloader->getTargetFile()->open(QIODevice::ReadOnly);
		OptifineVersionInfoList versionInfoList{ versionInfoFactory.createOptifineVersionInfoList(downloader->getTargetFile()->readAll()) };
		for (int i = 0; i < versionInfoList.size(); i++)
		{
			qDebug() << versionInfoList[i].getFileName();
		}
		downloader->deleteLater();
	});
	QObject::connect(downloader, &QGSDownloader::error, [=](QGSDownloader::Error error)
	{
		qDebug() << "optifine manifest:" << "Code:" << error.getCode() << "Message:" << error.getMessage();
	});
	if (!downloader->start())
	{
		qDebug() << "optifine manifest:" << "start failed";
		return 1;
	}
	return 0;
}

void gameBuildTest()
{
	QSharedPointer<QGSIDownloadSource> downloadSource{ new QGSDownloadSourceOfficial };
	QGSDownloaderFactory downloadManager{ downloadSource.data() };
	QGSDownloader * downloader;
	QGSGameDirectory gameDirectory{ QDir{ QCoreApplication::applicationDirPath() + "/.minecraft" } };

	static GameVersionInfo versionInfo;

	downloader = downloadManager.generateGameVersionInfoJsonDownloader(new QFile{ QString{ QCoreApplication::applicationDirPath() + "/version_manifest.json" } });
	if (!downloader->start())
	{
		qDebug() << "version manifest:" << "start failed";
		return;
	}
	QEventLoop eventLoop;
	QObject::connect(downloader, &QGSDownloader::finished, [&]()
	{
		QGSGameVersionInfoListFactory versionInfoFactory;
		downloader->getTargetFile()->open(QIODevice::ReadOnly);
		GameVersionInfoList versionInfoList{ versionInfoFactory.createGameVersionInfoList(downloader->getTargetFile()->readAll()) };
		versionInfo = versionInfoList.getVersionInfo("1.11.2");
		downloader->deleteLater();
		eventLoop.quit();
		qDebug() << "version manifest:" << "finished!";
	});
	eventLoop.exec();

	downloader = downloadManager.generateGameVersionJsonDownloader(versionInfo, gameDirectory);
	downloader->start();
	QObject::connect(downloader, &QGSDownloader::finished, [&]()
	{
		downloader->deleteLater();
		eventLoop.quit();
		qDebug() << "version json:" << "finished!";
	});
	eventLoop.exec();

	auto & version{ gameDirectory.getVersion("1.11.2") };
	downloader = downloadManager.generateGameVersionDownloader(version, gameDirectory, "client");
	downloader->start();
	QObject::connect(downloader, &QGSDownloader::finished, [&]()
	{
		downloader->deleteLater();
		eventLoop.quit();
		qDebug() << "version:" << "finished!";
	});
	eventLoop.exec();

	auto & libraryList{ version.getLibraries() };
	qDebug() << "library count:" << libraryList.size();
	for (auto & i : libraryList)
	{
		downloader = downloadManager.generateLibraryDownloader(i, gameDirectory);
		downloader->start();
		QObject::connect(downloader, &QGSDownloader::finished, [=]()
		{
			qDebug() << "library:" << "finished!";
			downloader->deleteLater();
		});
		QObject::connect(downloader, &QGSDownloader::timeout, [=]()
		{
			qDebug() << "library:" << "timeout!";
		});
		QObject::connect(downloader, &QGSDownloader::error, [=]()
		{
			qDebug() << "library:" << "error!";
		});
	}

	static AssetIndexInfo assetIndexInfo;
	downloader = downloadManager.generateAssetIndexJsonDownloader(version.getAssetIndex(), gameDirectory);
	downloader->start();
	QObject::connect(downloader, &QGSDownloader::finished, [&]()
	{
		
		QGSAssetIndexInfoFactory versionInfoFactory;
		downloader->getTargetFile()->open(QIODevice::ReadOnly);
		assetIndexInfo = versionInfoFactory.createAssetIndexInfo(downloader->getTargetFile()->readAll());
		downloader->deleteLater();
		eventLoop.quit();
		qDebug() << "asset index json:" << "finished!";
	});
	eventLoop.exec();

	auto && assetObjectMap{ assetIndexInfo.getAssetObjectMap() };
	for (auto & i : assetObjectMap)
	{
		downloader = downloadManager.generateAssetObjectDownloader(i, gameDirectory);
		downloader->start();
		QObject::connect(downloader, &QGSDownloader::finished, [=]()
		{
			qDebug() << "asset object:" << "finished!";
			downloader->deleteLater();
		});
		QObject::connect(downloader, &QGSDownloader::timeout, [=]()
		{
			qDebug() << "asset object:" << "timeout!";
		});
		QObject::connect(downloader, &QGSDownloader::error, [=]()
		{
			qDebug() << "asset object:" << "error!";
		});
	}
}

void threadPoolTest()
{
	QGSDownloaderFactory downloaderFactory{ new QGSDownloadSourceOfficial };
	QGSGameDirectory gameDirectory{ QDir{ QCoreApplication::applicationDirPath() + "/.minecraft" } };
	static QGSGameBuilder gameBuilder{ new QGSDownloadSourceOfficial, &gameDirectory };
	QFile manifestFile{ QCoreApplication::applicationDirPath() + "/version_manifest.json" };
	manifestFile.open(QIODevice::ReadOnly);
	QGSGameVersionInfoListFactory infoListFactory;
	auto && infoList{ infoListFactory.createGameVersionInfoList(manifestFile.readAll()) };
	gameBuilder.start(infoList.getVersionInfo("1.11.2"));
	auto * downloader = downloaderFactory.generateGameVersionJsonDownloader(infoList.getVersionInfo("1.11.2"), gameDirectory);
	//downloader->start();
}

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	qDebug() << "=QGettingStart Test=";

	threadPoolTest();
	//downloadTest();
	//gameBuildTest();
	//generateLaunchCommandTest();

	return a.exec();
}
