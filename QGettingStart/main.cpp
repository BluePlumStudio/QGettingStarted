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

	printf("启动版本：");
	getline(cin, in);
	launchVersion = in;
	gameBuilder->setGameVersion(QString::fromLocal8Bit(in.c_str()));

	printf("游戏路径（.minecraft）：");
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
		printf("Java路径（.exe）：");
		getline(cin, in);
		gameBuilder->setJavaPath(QString::fromLocal8Bit(in.c_str()));
	}

	printf("native文件夹路径路径：");
	getline(cin, in);
	gameBuilder->setNativePath(QString::fromLocal8Bit(in.c_str()));

	printf("用户名：");
	getline(cin, in);
	gameBuilder->setPlayerName(QString::fromLocal8Bit(in.c_str()));

	printf("用户类型（Legacy/Mojang）：");
	getline(cin, in);
	gameBuilder->setUserType(QString::fromLocal8Bit(in.c_str()));

	/*额外参数*/
	//gameBuilder->setJVMArgument("-XX:+UseG1GC -XX:-UseAdaptiveSizePolicy -XX:-OmitStackTraceInFastThrow");
	//gameBuilder->setPreInstruction("PreInstructionTEST");
	//gameBuilder->setServerAddress("127.0.0.1:6666");
	//gameBuilder->setGameArgument("GameArgumentTEST");

	printf("最大内存（MB）：");
	cin >> Xmx;
	printf("最小内存（MB）：");
	cin >> Xmn;
	gameBuilder->setXmx(Xmx);
	gameBuilder->setXmn(Xmn);

	/*获取构造好的game*/
	QGSAbstractGameBuilder::GameBuilderError builderError;
	game = gameBuilder->getGame(&builderError);
	printf("QGSAbstractGameBuilder::GameBuilderError：\n");
	qDebug() << builderError.mBuildError;
	qDebug() << builderError.mErrorMessage;

	//功能测试
	launcher->getLaunchString(game, launchCommand);
	QVector<QGSUtil::Library> libraries;
	QGSAbstractLauncher::LauncherError launcherError = QGSUtil::getInstance()->getLibrariesVector(static_cast<QGSGame *>(game), libraries);
	printf("QGSAbstractLauncher::LauncherError：\n");
	qDebug() << launcherError.mLaunchError;
	qDebug() << launcherError.mErrorMessage;

	launchCommandFile.setFileName(game->getGameVersion() + ".bat");
	launchCommandFile.open(QIODevice::Text | QIODevice::WriteOnly | QIODevice::Truncate);

	QTextStream testStream(&launchCommandFile);
	QString headCmd(QString("@echo off\nset appdata=%1\ncd /%2 %appdata%\n").arg(game->getGamePath()).arg(game->getGamePath()[0]));
	testStream << headCmd.toUtf8() << launchCommand.toUtf8();
	printf("启动脚本已生成！\n");
	launchCommandFile.close();
	return 0;
}
