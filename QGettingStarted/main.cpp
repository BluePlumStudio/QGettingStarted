#include <QtCore/QCoreApplication>
#include <QSharedPointer>
#include <QTextStream>
#include <QDebug>
#include <iostream>
#include <string>

#include "QGettingStarted.h"

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	using namespace std;
	using namespace qgs;
	while (1)
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
		launchOptionsBuilder.setAuthInfo(QGSOfflineAccountFactory().createAccount()->authenticate("uiufqr7386@yeah.net", "f2fdf55555555"));
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
			return 1;
		}

		QFile launchCommandFile;
		launchCommandFile.setFileName(QCoreApplication::applicationDirPath() + "/" + QString::fromStdString(version) + ".bat");
		launchCommandFile.open(QIODevice::Text | QIODevice::WriteOnly | QIODevice::Truncate);
		QTextStream testStream(&launchCommandFile);
		testStream << launchCommand.toUtf8();
		launchCommandFile.close();
	}
	//return a.exec();
}
