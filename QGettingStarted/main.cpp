#include <QtCore/QCoreApplication>
#include <QSharedPointer>
#include <QTextStream>
#include <iostream>
#include <string>

#include "QGettingStarted.h"

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	using namespace std;
	using namespace qgs;

	string directory;
	getline(cin, directory);
	QGSGameDirectory gameDirectory{ QDir(QString::fromLocal8Bit(directory.c_str())) };

	string version;
	getline(cin, version);
	//gameDirectory->getVersion(QString::fromLocal8Bit(version.c_str()));

	QSharedPointer<QGSLauncherFactory> launcherFactory{ new QGSLauncherFactory };
	QSharedPointer<QGSILauncher>launcher{ launcherFactory ->createLauncher(QString::fromLocal8Bit(version.c_str()),gameDirectory)};

	QGSLaunchOptionsBuilder launchOptionsBuilder;
	QString launchCommand;
	launchOptionsBuilder.setJavaPath("C:/Program Files/Java/jre1.8.0_121/bin/javaw.exe");
	launchOptionsBuilder.setMaxMemory(1024);
	launchOptionsBuilder.setMinMemory(128);
	launchOptionsBuilder.setAuthInfo(QGSOfflineAccountFactory().createAccount()->authenticate("23333"));
	launchOptionsBuilder.setJVMArguments("-XX:+UseG1GC -XX:-UseAdaptiveSizePolicy -XX:-OmitStackTraceInFastThrow");
	/*
	launchOptionsBuilder.setWrapper("前置指令");
	launchOptionsBuilder.setServerInfo(QGSLaunchOptions::ServerInfo("serveraddress.com"));
	launchOptionsBuilder.setGameArguments("游戏参数");
	launchOptionsBuilder.setWindowSize({ 480,854 });
	launchOptionsBuilder.setFullScreen(true);
	launchOptionsBuilder.setMetaspaceSize(8888);
	launchOptionsBuilder.setProxyInfo(QGSLaunchOptions::ProxyInfo("proxyaddress", "proxyport", "proxyuser", "proxypassword"));
	*/
	launcher->generateLaunchCommand(launchOptionsBuilder.getLaunchOptions(), launchCommand);

	QFile launchCommandFile;
	launchCommandFile.setFileName(QCoreApplication::applicationDirPath() + "/" + QString::fromStdString(version) + ".bat");
	launchCommandFile.open(QIODevice::Text | QIODevice::WriteOnly | QIODevice::Truncate);
	QTextStream testStream(&launchCommandFile);
	testStream << launchCommand.toUtf8();
	launchCommandFile.close();

	//return a.exec();
}
