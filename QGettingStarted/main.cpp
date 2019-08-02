
#include <QtCore/QCoreApplication>
#include <QSharedPointer>
#include <QTextStream>
#include <QDebug>
#include <QTemporaryFile>
#include <iostream>
#include <string>
#include <QUuid>

#include "QGettingStarted.h"

using namespace std;

void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
	QByteArray localMsg = msg.toLocal8Bit();
	switch (type) {
	case QtDebugMsg:
		//fprintf(stderr, "Debug: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
		fprintf(stderr, "%s\n", localMsg.constData());
		break;
	case QtInfoMsg:
		fprintf(stderr, "Info: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
		break;
	case QtWarningMsg:
		fprintf(stderr, "Warning: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
		break;
	case QtCriticalMsg:
		fprintf(stderr, "Critical: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
		break;
	case QtFatalMsg:
		fprintf(stderr, "Fatal: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
		abort();
	}
}

int downloadTest()
{
	QSharedPointer<QGSIDownloadSource> downloadSource(new QGSBMCLAPIDownloadSource);
	QGSDownloadTaskFactory downloadManager(downloadSource.data());
	QGSDownloadTask * downloadTask;
	QGSGameDirectory gameDirectory(QDir{ QCoreApplication::applicationDirPath() + "/.minecraft" });

	//forge download test
	downloadTask = downloadManager.generateForgeDownloadTask(new QFile(QString(QCoreApplication::applicationDirPath() + "/forge.zip")), "1.4.7", "6.6.1.530", "src", "zip");
	QObject::connect(downloadTask, &QGSDownloadTask::downloadProgress, [=](qint64 bytesReceived, qint64 bytesTotal, QGSTask * task)
	{
		cout << "Forge:" << bytesReceived << ";" << bytesTotal << endl;
	});
	QObject::connect(downloadTask, &QGSDownloadTask::finished, downloadTask, &QObject::deleteLater);
	QObject::connect(downloadTask, &QGSDownloadTask::downloadError, [=](QGSNetworkError error, QGSTask * task)
	{
		qDebug() << "Forge:" << "Code:" << error.getCode();
	});
	downloadTask->start();
	//liteloader download test
	downloadTask = downloadManager.generateLiteLoaderDownloadTask(new QFile(QString(QCoreApplication::applicationDirPath() + "/liteloader.jar")), "1.11.2", "1.11.2-SNAPSHOT", "installer");
	QObject::connect(downloadTask, &QGSDownloadTask::downloadProgress, [=](qint64 bytesReceived, qint64 bytesTotal, QGSTask * task)
	{
		cout << "LiteLoader:" << bytesReceived << ";" << bytesTotal << endl;
	});
	QObject::connect(downloadTask, &QGSDownloadTask::finished, downloadTask, &QObject::deleteLater);
	QObject::connect(downloadTask, &QGSDownloadTask::downloadError, [=](QGSNetworkError error, QGSTask * task)
	{
		qDebug() << "LiteLoader:" << "Code:" << error.getCode();
	});
	downloadTask->start();
	//optifine download test
	downloadTask = downloadManager.generateOptifineDownloadTask(new QFile(QString(QCoreApplication::applicationDirPath() + "/optifine.zip")), "1.9.2", "HD_U", "D7");
	QObject::connect(downloadTask, &QGSDownloadTask::downloadProgress, [=](qint64 bytesReceived, qint64 bytesTotal, QGSTask * task)
	{
		cout << "Optifine:" << bytesReceived << ";" << bytesTotal << endl;
	});
	QObject::connect(downloadTask, &QGSDownloadTask::finished, downloadTask, &QObject::deleteLater);
	QObject::connect(downloadTask, &QGSDownloadTask::downloadError, [=](QGSNetworkError error, QGSTask * task)
	{
		qDebug() << "Optifine:" << "Code:" << error.getCode() << "Message:" << error.getErrorString();
	});
	downloadTask->start();
	//version download test
	QGSGameVersion version;
	QMap<QString, QGSDownloadBase> downloads;
	downloads.insert("client",
		QGSDownloadBase(8736083, "4a61c873be90bb1196d68dac7b29870408c56969", "", QUrl("https://launcher.mojang.com/mc/game/1.9.4/client/4a61c873be90bb1196d68dac7b29870408c56969/client.jar")));
	version.setDownloads(downloads);
	version.setId("1.9.4");
	downloadTask = downloadManager.generateGameVersionDownloadTask(version, gameDirectory, "client");
	QObject::connect(downloadTask, &QGSDownloadTask::downloadProgress, [=](qint64 bytesReceived, qint64 bytesTotal, QGSTask * task)
	{
		cout << "version:" << bytesReceived << ";" << bytesTotal << endl;
	});
	QObject::connect(downloadTask, &QGSDownloadTask::finished, downloadTask, &QObject::deleteLater);
	QObject::connect(downloadTask, &QGSDownloadTask::downloadError, [=](QGSNetworkError error, QGSTask * task)
	{
		qDebug() << "version:" << "Code:" << error.getCode() << "Message:" << error.getErrorString();
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
	QObject::connect(downloadTask, &QGSDownloadTask::downloadError, [=](QGSNetworkError error, QGSTask * task)
	{
		qDebug() << "QGSLibrary:" << "Code:" << error.getCode() << "Message:" << error.getErrorString();
	});
	downloadTask->start();
	//version manifest download test
	downloadTask = downloadManager.generateGameVersionInfoJsonDownloadTask(new QFile(QString(QCoreApplication::applicationDirPath() + "/version_manifest.json")));
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
	QObject::connect(downloadTask, &QGSDownloadTask::downloadError, [=](QGSNetworkError error, QGSTask * task)
	{
		qDebug() << "version manifest:" << "Code:" << error.getCode() << "Message:" << error.getErrorString();
	});
	downloadTask->start();
	//forge version download test
	downloadTask = downloadManager.generateForgeVersionInfoJsonDownloadTask(new QFile(QString(QCoreApplication::applicationDirPath() + "/forge_manifest.json")), 100, 50);
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
		QGSForgeVersionInfoList versionInfoList(versionInfoFactory.createForgeVersionInfoList(downloadTask->getTargetFile()->readAll(), 1, 1000));
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
	QObject::connect(downloadTask, &QGSDownloadTask::downloadError, [=](QGSNetworkError error, QGSTask * task)
	{
		qDebug() << "forge version:" << "Code:" << error.getCode() << "Message:" << error.getErrorString();
	});
	downloadTask->start();
	//liteloader version download test
	downloadTask = downloadManager.generateLiteLoaderVersionInfoJsonDownloadTask(new QFile(QString(QCoreApplication::applicationDirPath() + "/liteloader_manifest.json")));
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
		QGSLiteLoaderVersionInfoList versionInfoList(versionInfoFactory.createLiteLoaderVersionInfoList(downloadTask->getTargetFile()->readAll()));
		for (int i = 0; i < versionInfoList.size(); i++)
		{
			qDebug() << versionInfoList[i].getLiteLoaderVersionReposity().getUrl();
		}
		downloadTask->deleteLater();
	});
	QObject::connect(downloadTask, &QGSDownloadTask::downloadError, [=](QGSNetworkError error, QGSTask * task)
	{
		qDebug() << "liteloader manifest:" << "Code:" << error.getCode() << "Message:" << error.getErrorString();
	});
	downloadTask->start();
	//optifine version download test
	downloadTask = downloadManager.generateOptifineVersionInfoJsonDownloadTask(new QFile(QString(QCoreApplication::applicationDirPath() + "/optifine_manifest.json")));
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
		QGSOptifineVersionInfoList versionInfoList(versionInfoFactory.createOptifineVersionInfoList(downloadTask->getTargetFile()->readAll()));
		for (int i = 0; i < versionInfoList.size(); i++)
		{
			qDebug() << versionInfoList[i].getFileName();
		}
		downloadTask->deleteLater();
	});
	QObject::connect(downloadTask, &QGSDownloadTask::downloadError, [=](QGSNetworkError error, QGSTask * task)
	{
		qDebug() << "optifine manifest:" << "Code:" << error.getCode() << "Message:" << error.getErrorString();
	});
	downloadTask->start();
	return 0;
}

void generateLaunchCommandTest()
{
	while (true)
	{
		cout << "游戏路径：";
		string directory;
		getline(cin, directory);
		QGSGameDirectory gameDirectory(QDir(QString::fromLocal8Bit(directory.c_str())));

		cout << "游戏版本：";
		string version;
		getline(cin, version);
		QGSLauncher launcher;

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
		QGSAuthInfo authInfo;
		QEventLoop eventLoop;
		auto * account(QGSOfflineAccountFactory().createAccount());
		QObject::connect(account, &QGSIAccount::finished, &eventLoop, &QEventLoop::quit);
		QObject::connect(account, &QGSIAccount::finished, [&authInfo](QGSAuthInfo _authInfo)
		{
			authInfo = _authInfo;
		});
		QObject::connect(account, &QGSIAccount::error, [](QGSNetworkError networkError)
		{
			qDebug() << "QGSNetworkError:" << networkError.getCode() << networkError.getErrorString();
		});
		account->authenticate("uiufqr7386@yeah.net", "");
		eventLoop.exec();

		launchOptionsBuilder.setAuthInfo(authInfo);
		launchOptionsBuilder.setJVMArguments("-XX:+UseG1GC -XX:-UseAdaptiveSizePolicy -XX:-OmitStackTraceInFastThrow");
		/*
		launchOptionsBuilder.setWrapper("前置指令");
		launchOptionsBuilder.setServerInfo(QGSServerInfo("serveraddress.com"));
		launchOptionsBuilder.setGameArguments("游戏参数");
		launchOptionsBuilder.setWindowSize((480,854));
		launchOptionsBuilder.setFullScreen(true);
		launchOptionsBuilder.setMetaspaceSize(8888);
		launchOptionsBuilder.setProxy(QNetworkProxy("proxyaddress", "proxyport", "proxyuser", "proxypassword"));
		*/
		if (launcher.generateLaunchCommand(gameDirectory.getVersion(QString::fromLocal8Bit(version.c_str())), gameDirectory, launchOptionsBuilder.getLaunchOptions(), launchCommand) & QGSLauncherError::Ok)
		{

		}

		QFile launchCommandFile;
		launchCommandFile.setFileName(QCoreApplication::applicationDirPath() + "/" + QString::fromStdString(version) + ".bat");
		launchCommandFile.open(QIODevice::Text | QIODevice::WriteOnly | QIODevice::Truncate);
		QTextStream testStream(&launchCommandFile);
		testStream << launchCommand.toUtf8();
		launchCommandFile.close();
	}
}

void gameVersionBuilderTest()
{
	QFile manifestFile(QCoreApplication::applicationDirPath() + "/version_manifest.json");
	manifestFile.open(QIODevice::ReadOnly);
	QGSGameVersionInfoListFactory versionInfoFactory;
	QGSGameVersionInfoList versionInfoList(versionInfoFactory.createGameVersionInfoList(manifestFile.readAll()));
	int downloadSourceId;
	int count = 0;
	qDebug() << "Count:";
	std::cin >> count;
	qDebug() << "DownloadSource: 1.Official 2.BMCL";
	std::cin >> downloadSourceId;
	std::getchar();

	QGSIDownloadSource * downloadSource = nullptr;
	if (downloadSourceId == 2)
	{
		downloadSource = new QGSBMCLAPIDownloadSource;
	}
	else
	{
		downloadSource = new QGSOfficialDownloadSource;
	}

	QGSDownloadTaskFactory * downloadTaskFactory(new QGSDownloadTaskFactory(downloadSource));
	auto * threadPoolManager(new QGSThreadPoolManager(8, 256));
	QGSBuilderFactory * builderFactory(new QGSBuilderFactory(threadPoolManager));

	for (int i = 0; i < count; i++)
	{
		qDebug() << "Version:";
		std::string versionId;
		std::getline(cin, versionId);
		QGSGameVersionInfo * versionInfo = new QGSGameVersionInfo(versionInfoList.getVersionInfo(QString::fromStdString(versionId)));

		QGSGameDirectory * gameDirectory(new QGSGameDirectory(QDir(QCoreApplication::applicationDirPath() +"/Minecraft/" + QString::fromStdString(versionId) + "/.minecraft")));
		QGSGameVersionBuilder * gameVersionBuilder = builderFactory->createGameVersionBuilder(*versionInfo, gameDirectory, downloadTaskFactory);
		QGSLibraryBuilder * libraryBuilder = builderFactory->createLibraryBuilder(*versionInfo, gameDirectory, downloadTaskFactory);
		QGSAssetBuilder * assetBuilder = builderFactory->createAssetBuilder(*versionInfo, gameDirectory, downloadTaskFactory);
		gameVersionBuilder->setNextTask(libraryBuilder).setNextTask(assetBuilder);
		QObject::connect(gameVersionBuilder, &QGSGameVersionBuilder::started, [=]()
		{
			qDebug() << "Version:" << (*versionInfo).getId() << "gameVersionBuilder started!";
		});
		QObject::connect(gameVersionBuilder, &QGSGameVersionBuilder::downloadTaskStarted, [=](QGSDownloadTask * task)
		{
			qDebug() << "Version:" << (*versionInfo).getId() << "download:" << task->getDownloadInfo().getUrl() << " started!";
		});
		QObject::connect(gameVersionBuilder, &QGSGameVersionBuilder::downloadTaskFinished, [=](QGSDownloadTask * task)
		{
			qDebug() << "Version:" << (*versionInfo).getId() << "download:" << task->getDownloadInfo().getUrl() << " finished!" << gameVersionBuilder->getTaskListSize() << "left!";
		});
		QObject::connect(gameVersionBuilder, &QGSGameVersionBuilder::downloadTaskStoped, [=](QGSDownloadTask * task)
		{
			qDebug() << "Version:" << (*versionInfo).getId() << "download:" << task->getDownloadInfo().getUrl() << " stoped!";
		});
		QObject::connect(gameVersionBuilder, &QGSGameVersionBuilder::downloadTaskCanceled, [=](QGSDownloadTask * task)
		{
			qDebug() << "Version:" << (*versionInfo).getId() << "download:" << task->getDownloadInfo().getUrl() << " canceled!";
		});
		QObject::connect(gameVersionBuilder, &QGSGameVersionBuilder::downloadTaskDownloadProgress, [=](qint64 bytesReceived, qint64 bytesTotal, QGSDownloadTask * task)
		{
			qDebug() << "Version:" << (*versionInfo).getId() << "download:" << task->getDownloadInfo().getUrl() << " download progress:" << "bytes received:" << bytesReceived << "bytes total:" << bytesTotal;
		});
		QObject::connect(gameVersionBuilder, &QGSGameVersionBuilder::downloadTaskDownloadError, [=](QGSNetworkError error, QGSDownloadTask * task)
		{
			qDebug() << "Version:" << (*versionInfo).getId() << "download:" << task->getDownloadInfo().getUrl() << " download error!" << gameVersionBuilder->getTaskListSize() << "left!" << "Error code:" << error.getCode();
		});
		QObject::connect(gameVersionBuilder, &QGSGameVersionBuilder::downloadTaskError, [=](QGSDownloadTask * task)
		{
			qDebug() << "Version:" << (*versionInfo).getId() << "download:" << task->getDownloadInfo().getUrl() << " error!" << gameVersionBuilder->getTaskListSize() << "left!";
		});
		QObject::connect(gameVersionBuilder, &QGSGameVersionBuilder::error, [=]()
		{
			qDebug() << "Version:" << (*versionInfo).getId() << "gameVersionBuilder error!";
			qDebug() << "Version:" << (*versionInfo).getId() << "gameVersionBuilder error!";
			qDebug() << "Version:" << (*versionInfo).getId() << "gameVersionBuilder error!";

			gameVersionBuilder->deleteLater();
		});
		QObject::connect(gameVersionBuilder, &QGSGameVersionBuilder::finished, [=]()
		{
			qDebug() << "Version:" << (*versionInfo).getId() << "gameVersionBuilder finished!";
			qDebug() << "Version:" << (*versionInfo).getId() << "gameVersionBuilder finished!";
			qDebug() << "Version:" << (*versionInfo).getId() << "gameVersionBuilder finished!";

			gameVersionBuilder->deleteLater();
		});
		//
		QObject::connect(libraryBuilder, &QGSLibraryBuilder::started, [=]()
		{
			qDebug() << "Version:" << (*versionInfo).getId() << "libraryBuilder started!";
		});
		QObject::connect(libraryBuilder, &QGSLibraryBuilder::downloadTaskStarted, [=](QGSDownloadTask * task)
		{
			qDebug() << "Version:" << (*versionInfo).getId() << "download:" << task->getDownloadInfo().getUrl() << " started!";
		});
		QObject::connect(libraryBuilder, &QGSLibraryBuilder::downloadTaskFinished, [=](QGSDownloadTask * task)
		{
			qDebug() << "Version:" << (*versionInfo).getId() << "download:" << task->getDownloadInfo().getUrl() << " finished!" << libraryBuilder->getTaskListSize() << "left!";
		});
		QObject::connect(libraryBuilder, &QGSLibraryBuilder::downloadTaskStoped, [=](QGSDownloadTask * task)
		{
			qDebug() << "Version:" << (*versionInfo).getId() << "download:" << task->getDownloadInfo().getUrl() << " stoped!";
		});
		QObject::connect(libraryBuilder, &QGSLibraryBuilder::downloadTaskCanceled, [=](QGSDownloadTask * task)
		{
			qDebug() << "Version:" << (*versionInfo).getId() << "download:" << task->getDownloadInfo().getUrl() << " canceled!";
		});
		QObject::connect(libraryBuilder, &QGSLibraryBuilder::downloadTaskDownloadProgress, [=](qint64 bytesReceived, qint64 bytesTotal, QGSDownloadTask * task)
		{
			qDebug() << "Version:" << (*versionInfo).getId() << "download:" << task->getDownloadInfo().getUrl() << " download progress:" << "bytes received:" << bytesReceived << "bytes total:" << bytesTotal;
		});
		QObject::connect(libraryBuilder, &QGSLibraryBuilder::downloadTaskDownloadError, [=](QGSNetworkError error, QGSDownloadTask * task)
		{
			qDebug() << "Version:" << (*versionInfo).getId() << "download:" << task->getDownloadInfo().getUrl() << " download error!" << libraryBuilder->getTaskListSize() << "left!" << "Error code:" << error.getCode();
		});
		QObject::connect(libraryBuilder, &QGSLibraryBuilder::downloadTaskError, [=](QGSDownloadTask * task)
		{
			qDebug() << "Version:" << (*versionInfo).getId() << "download:" << task->getDownloadInfo().getUrl() << " error!" << libraryBuilder->getTaskListSize() << "left!";
		});
		QObject::connect(libraryBuilder, &QGSLibraryBuilder::error, [=]()
		{
			qDebug() << "Version:" << (*versionInfo).getId() << "libraryBuilder error!";
			qDebug() << "Version:" << (*versionInfo).getId() << "libraryBuilder error!";
			qDebug() << "Version:" << (*versionInfo).getId() << "libraryBuilder error!";

			libraryBuilder->deleteLater();
		});
		QObject::connect(libraryBuilder, &QGSLibraryBuilder::finished, [=]()
		{
			qDebug() << "Version:" << (*versionInfo).getId() << "libraryBuilder finished!";
			qDebug() << "Version:" << (*versionInfo).getId() << "libraryBuilder finished!";
			qDebug() << "Version:" << (*versionInfo).getId() << "libraryBuilder finished!";

			libraryBuilder->deleteLater();
		});
		//
		QObject::connect(assetBuilder, &QGSLibraryBuilder::started, [=]()
		{
			qDebug() << "Version:" << (*versionInfo).getId() << "assetBuilder started!";
		});
		QObject::connect(assetBuilder, &QGSLibraryBuilder::downloadTaskStarted, [=](QGSDownloadTask * task)
		{
			qDebug() << "Version:" << (*versionInfo).getId() << "download:" << task->getDownloadInfo().getUrl() << " started!";
		});
		QObject::connect(assetBuilder, &QGSLibraryBuilder::downloadTaskFinished, [=](QGSDownloadTask * task)
		{
			qDebug() << "Version:" << (*versionInfo).getId() << "download:" << task->getDownloadInfo().getUrl() << " finished!" << assetBuilder->getTaskListSize() << "left!";
		});
		QObject::connect(assetBuilder, &QGSLibraryBuilder::downloadTaskStoped, [=](QGSDownloadTask * task)
		{
			qDebug() << "Version:" << (*versionInfo).getId() << "download:" << task->getDownloadInfo().getUrl() << " stoped!";
		});
		QObject::connect(assetBuilder, &QGSLibraryBuilder::downloadTaskCanceled, [=](QGSDownloadTask * task)
		{
			qDebug() << "Version:" << (*versionInfo).getId() << "download:" << task->getDownloadInfo().getUrl() << " canceled!";
		});
		QObject::connect(assetBuilder, &QGSLibraryBuilder::downloadTaskDownloadProgress, [=](qint64 bytesReceived, qint64 bytesTotal, QGSDownloadTask * task)
		{
			qDebug() << "Version:" << (*versionInfo).getId() << "download:" << task->getDownloadInfo().getUrl() << " download progress:" << "bytes received:" << bytesReceived << "bytes total:" << bytesTotal;
		});
		QObject::connect(assetBuilder, &QGSLibraryBuilder::downloadTaskDownloadError, [=](QGSNetworkError error, QGSDownloadTask * task)
		{
			qDebug() << "Version:" << (*versionInfo).getId() << "download:" << task->getDownloadInfo().getUrl() << " download error!" << assetBuilder->getTaskListSize() << "left!" << "Error code:" << error.getCode();
		});
		QObject::connect(assetBuilder, &QGSLibraryBuilder::downloadTaskError, [=](QGSDownloadTask * task)
		{
			qDebug() << "Version:" << (*versionInfo).getId() << "download:" << task->getDownloadInfo().getUrl() << " error!" << assetBuilder->getTaskListSize() << "left!";
		});
		QObject::connect(assetBuilder, &QGSLibraryBuilder::error, [=]()
		{
			qDebug() << "Version:" << (*versionInfo).getId() << "assetBuilder error!";
			qDebug() << "Version:" << (*versionInfo).getId() << "assetBuilder error!";
			qDebug() << "Version:" << (*versionInfo).getId() << "assetBuilder error!";

			assetBuilder->deleteLater();
		});
		QObject::connect(assetBuilder, &QGSLibraryBuilder::finished, [=]()
		{
			qDebug() << "Version:" << (*versionInfo).getId() << "assetBuilder finished!";
			qDebug() << "Version:" << (*versionInfo).getId() << "assetBuilder finished!";
			qDebug() << "Version:" << (*versionInfo).getId() << "assetBuilder finished!";

			assetBuilder->deleteLater();
		});

		threadPoolManager->addTaskBack(gameVersionBuilder);
	}

	/*
	QTimer::singleShot(10000, [=]()
	{
		gameVersionBuilder->stop();
		qDebug() << "gameVersionBuilder stoped!";

	});
	QTimer::singleShot(12000, [=]()
	{
		gameVersionBuilder->start();
		qDebug() << "gameVersionBuilder started!";

	});
	*/
}

void getJavaPathListTest()
{
	qDebug() << QGSFileTools::getJavaPathListFromSystemSettings();
}

void YggdrasilTest()
{
	QEventLoop eventLoop;
	auto * account(QGSYggdrasilAccountFactory().createAccount());
	QObject::connect(account, &QGSIAccount::finished, [](QGSAuthInfo authInfo)
	{
		qDebug() << "Name:" << authInfo.getSelectedProfile().getName();
		qDebug() << "Id:" << authInfo.getSelectedProfile().getId();
		qDebug() << "AccessToken:" << authInfo.getAccessToken();
		qDebug() << "UserType:" << authInfo.getUserType();
	});
	QObject::connect(account, &QGSIAccount::finished, &eventLoop, &QEventLoop::quit);
	QObject::connect(account, &QGSIAccount::error, [](QGSNetworkError networkError)
	{
		qDebug() << "QGSNetworkError:" << networkError.getCode() << networkError.getErrorString();
	});

	cout << "账户名：";
	string userName;
	getline(cin, userName);
	cout << "密码：";
	string passwords;
	getline(cin, passwords);

	account->authenticate(QString::fromStdString(userName), QString::fromStdString(passwords));
	eventLoop.exec();
}

int main(int argc, char *argv[])
{
	//qInstallMessageHandler(myMessageOutput);
	QCoreApplication a(argc, argv);
	//downloadTest();
	
	qDebug() << "=QGettingStart Test=";
	qDebug() << QString::fromLocal8Bit("1.生成启动命令 | 2.下载游戏 | 3.获取Java路径 | 4.Yggdrasil账号（正版）登录测试");
	int ans = 0;
	std::cin >> ans;
	cin.get();
	if (ans == 1)
	{
		generateLaunchCommandTest();
	}
	else if (ans == 2)
	{
		gameVersionBuilderTest();
	}
	else if (ans == 3)
	{
		getJavaPathListTest();
	}
	else if (ans == 4)
	{
		YggdrasilTest();
	}
	
	return a.exec();
}