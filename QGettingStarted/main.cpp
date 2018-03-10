#include <QtCore/QCoreApplication>
#include <QSharedPointer>
#include <QTextStream>
#include <QDebug>
#include <iostream>
#include <string>

#include "QGettingStarted.h"

using namespace std;
using namespace qgs;

void generateLaunchCommandTest()
{
	cout << "��Ϸ·����";
	string directory;
	getline(cin, directory);
	QGSGameDirectory gameDirectory{ QDir(QString::fromLocal8Bit(directory.c_str())) };

	cout << "��Ϸ�汾��";
	string version;
	getline(cin, version);
	QGSLauncher launcher{ gameDirectory.getVersion(QString::fromLocal8Bit(version.c_str())),gameDirectory };

	QGSLaunchOptionsBuilder launchOptionsBuilder;
	QString launchCommand;
	/*
	cout << "Java·����";
	string JavaPath;
	getline(cin, JavaPath);
	*/
	launchOptionsBuilder.setJavaPath("C:/Program Files/Java/jre1.8.0_162/bin/javaw.exe");
	launchOptionsBuilder.setMaxMemory(1024);
	launchOptionsBuilder.setMinMemory(128);
	/*
	cout << "�û�����";
	string userName;
	getline(cin, userName);
	launchOptionsBuilder.setAuthInfo(QGSOfflineAccountFactory().createAccount()->authenticate(QString::fromLocal8Bit(userName.c_str())));
	*/
	launchOptionsBuilder.setAuthInfo(QGSOfflineAccountFactory().createAccount()->authenticate("uiufqr7386@yeah.net", ""));
	launchOptionsBuilder.setJVMArguments("-XX:+UseG1GC -XX:-UseAdaptiveSizePolicy -XX:-OmitStackTraceInFastThrow");
	/*
	launchOptionsBuilder.setWrapper("ǰ��ָ��");
	launchOptionsBuilder.setServerInfo(QGSLaunchOptions::ServerInfo("serveraddress.com"));
	launchOptionsBuilder.setGameArguments("��Ϸ����");
	launchOptionsBuilder.setWindowSize({ 480,854 });
	launchOptionsBuilder.setFullScreen(true);
	launchOptionsBuilder.setMetaspaceSize(8888);
	launchOptionsBuilder.setProxyInfo(QGSLaunchOptions::ProxyInfo("proxyaddress", "proxyport", "proxyuser", "proxypassword"));
	*/
	if (launcher.generateLaunchCommand(launchOptionsBuilder.getLaunchOptions(), launchCommand) != QGSILauncherStrategy::Error::OK)
	{
		qDebug() << "���������ű�ʧ��";
		return;
	}

	QFile launchCommandFile;
	launchCommandFile.setFileName(QCoreApplication::applicationDirPath() + "/" + QString::fromStdString(version) + ".bat");
	launchCommandFile.open(QIODevice::Text | QIODevice::WriteOnly | QIODevice::Truncate);
	QTextStream testStream(&launchCommandFile);
	testStream << launchCommand.toUtf8();
	launchCommandFile.close();
}

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	qDebug() << "=QGettingStart Test=";

	QGSDownloadManager<QGSDownloadSourceBMCLAPI> downloadManager;
	
	//forge download test
	auto * downloader{ downloadManager.generateForgeDownloader("1.4.7","6.6.1.530","src","zip") };
	QObject::connect(downloader, &QGSDownloader::downloadProgress, [=](qint64 bytesReceived, qint64 bytesTotal)
	{
		cout << "Forge:" << bytesReceived << ";" << bytesTotal << endl;
	});
	QObject::connect(downloader, &QGSDownloader::finished, downloader, &QObject::deleteLater);
	QObject::connect(downloader, &QGSDownloader::error, [=](QGSDownloader::Error error)
	{
		qDebug() << "Forge:" << "Code:" << error.getCode() << "Message:" << error.getMessage();
	});
	if (!downloader->start())
	{
		return 1;
	}
	//liteloader download test
	downloader = downloadManager.generateLiteLoaderDownloader("1.7.10", "1.7.10");
	QObject::connect(downloader, &QGSDownloader::downloadProgress, [=](qint64 bytesReceived, qint64 bytesTotal)
	{
		cout << "LiteLoader:" << bytesReceived << ";" << bytesTotal << endl;
	});
	QObject::connect(downloader, &QGSDownloader::finished, downloader, &QObject::deleteLater);
	QObject::connect(downloader, &QGSDownloader::error, [=](QGSDownloader::Error error)
	{
		qDebug() << "LiteLoader:" << "Code:" << error.getCode() << "Message:" << error.getMessage();
	});
	if (!downloader->start())
	{
		return 1;
	}
	//optifine download test
	downloader = downloadManager.generateOptifineDownloader("1.9.2", "HD_U", "D7");
	QObject::connect(downloader, &QGSDownloader::downloadProgress, [=](qint64 bytesReceived, qint64 bytesTotal)
	{
		cout << "Optifine:" << bytesReceived << ";" << bytesTotal << endl;
	});
	QObject::connect(downloader, &QGSDownloader::finished, downloader, &QObject::deleteLater);
	QObject::connect(downloader, &QGSDownloader::error, [=](QGSDownloader::Error error)
	{
		qDebug() << "Optifine:" << "Code:" << error.getCode() << "Message:" << error.getMessage();
	});
	if (!downloader->start())
	{
		return 1;
	}
	//version download test
	downloader = downloadManager.generateVersionDownloader("1.9.2", "client");
	QObject::connect(downloader, &QGSDownloader::downloadProgress, [=](qint64 bytesReceived, qint64 bytesTotal)
	{
		cout << "version:" << bytesReceived << ";" << bytesTotal << endl;
	});
	QObject::connect(downloader, &QGSDownloader::finished, downloader, &QObject::deleteLater);
	QObject::connect(downloader, &QGSDownloader::error, [=](QGSDownloader::Error error)
	{
		qDebug() << "version:" << "Code:" << error.getCode() << "Message:" << error.getMessage();
	});
	if (!downloader->start())
	{
		return 1;
	}
	//library download test
	Library library;
	library.setPackage("com.mojang");
	library.setName("netty");
	library.setVersion("1.6");
	downloader = downloadManager.generateLibraryDownloader(library);
	QObject::connect(downloader, &QGSDownloader::downloadProgress, [=](qint64 bytesReceived, qint64 bytesTotal)
	{
		cout << "Library:" << bytesReceived << ";" << bytesTotal << endl;
	});
	QObject::connect(downloader, &QGSDownloader::finished, downloader, &QObject::deleteLater);
	QObject::connect(downloader, &QGSDownloader::error, [=](QGSDownloader::Error error)
	{
		qDebug() << "Library:" << "Code:" << error.getCode() << "Message:" << error.getMessage();
	});
	if (!downloader->start())
	{
		return 1;
	}
	return a.exec();
}
