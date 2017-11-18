#include <QtCore/QCoreApplication>

#include "QGettingStart.h"

#ifdef WIN32
#include <Windows.h>
#endif

#include <string>
#include <fstream>
#include <iostream>

#include <QTextStream>

using namespace std;

int main(int argc, char *argv[])
{
	//QCoreApplication a(argc, argv);

	string in, launchVersion;
	//fstream launchCommandFile;
	QFile launchCommandFile;
	int Xmn, Xmx;
	QGSAbstractGameBuilder * gameBuilder = new QGSGameBuilder;
	QGSAbstractLauncher * launcher = new QGSLauncher;
	QGSAbstractGame * game = nullptr;
	QString launchCommand;

	printf("�����汾��");
	getline(cin, in);
	launchVersion = in;
	gameBuilder->setGameVersion(QString::fromLocal8Bit(in.c_str()));

	printf("��Ϸ·����.minecraft����");
	getline(cin, in);
	gameBuilder->setGamePath(QString::fromLocal8Bit(in.c_str()));

	QVector<QString> JavaPaths;
	QGSUtil::getInstance()->getJavaPathVectorFromSystemSettings(JavaPaths);
	if (JavaPaths.size())
	{
		gameBuilder->setJavaPath(JavaPaths.first() + "/javaw.exe");
	}
	else
	{
		printf("Java·����.exe����");
		getline(cin, in);
		gameBuilder->setJavaPath(QString::fromLocal8Bit(in.c_str()));
	}

	printf("native�ļ���·��·����");
	getline(cin, in);
	gameBuilder->setNativePath(QString::fromLocal8Bit(in.c_str()));

	printf("�û�����");
	getline(cin, in);
	gameBuilder->setPlayerName(QString::fromLocal8Bit(in.c_str()));

	printf("�û����ͣ�Legacy/Mojang����");
	getline(cin, in);
	gameBuilder->setUserType(QString::fromLocal8Bit(in.c_str()));

	/*�������*/
	//gameBuilder->setJVMArgument("-XX:+UseG1GC -XX:-UseAdaptiveSizePolicy -XX:-OmitStackTraceInFastThrow");
	//gameBuilder->setPreInstruction("PreInstructionTEST");
	//gameBuilder->setServerAddress("127.0.0.1:6666");
	//gameBuilder->setGameArgument("GameArgumentTEST");

	printf("����ڴ棨MB����");
	cin >> Xmx;
	printf("��С�ڴ棨MB����");
	cin >> Xmn;
	gameBuilder->setXmx(Xmx);
	gameBuilder->setXmn(Xmn);

	/*��ȡ����õ�game*/
	QGSAbstractGameBuilder::GameBuilderError builderError;
	game = gameBuilder->getGame(&builderError);
	printf("QGSAbstractGameBuilder::GameBuilderError��\n");
	qDebug() << builderError.mBuildError;
	qDebug() << builderError.mErrorMessage;

	//���ܲ���
	launcher->getLaunchString(game, launchCommand);
	QVector<QGSUtil::Library> libraries;
	QGSAbstractLauncher::LauncherError launcherError = QGSUtil::getInstance()->getLibrariesVector(static_cast<QGSGame *>(game), libraries);
	printf("QGSAbstractLauncher::LauncherError��\n");
	qDebug() << launcherError.mLaunchError;
	qDebug() << launcherError.mErrorMessage;

	launchCommandFile.setFileName(game->getGameVersion() + ".bat");
	launchCommandFile.open(QIODevice::Text | QIODevice::WriteOnly | QIODevice::Truncate);

	QTextStream testStream(&launchCommandFile);
	QString headCmd(QString("@echo off\nset appdata=%1\ncd /%2 %appdata%\n").arg(game->getGamePath()).arg(game->getGamePath()[0]));
	testStream << headCmd.toUtf8() << launchCommand.toUtf8();
	printf("�����ű������ɣ�\n");
	launchCommandFile.close();
	return 0;
}
