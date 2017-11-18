#include <QtCore/QCoreApplication>

#include "QGettingStart.h"

#include <string>
#include <fstream>

using namespace std;

int main(int argc, char *argv[])
{
	//QCoreApplication a(argc, argv);

	string in, launchVersion;
	fstream launchCommandFile;
	int Xmn, Xmx;
	GameBuilder * gameBuilder = new QGSGameBuilder;
	Launcher * launcher = new QGSLauncher;
	Game * game = nullptr;
	QString launchCommand;

	printf("启动版本：");
	getline(cin, in);
	launchVersion = in;
	gameBuilder->setGameVersion(QString::fromLocal8Bit(in.c_str()));

	printf("游戏路径（.minecraft）：");
	getline(cin, in);
	gameBuilder->setGamePath(QString::fromLocal8Bit(in.c_str()));
	
	printf("Java路径（.exe）：");
	getline(cin, in);
	gameBuilder->setJavaPath(QString::fromLocal8Bit(in.c_str()));

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
	gameBuilder->setExtraArgument("-XX:HeapDumpPath=MojangTricksIntelDriversForPerformance_javaw.exe_minecraft.exe.heapdump -XX:+UseG1GC -XX:-UseAdaptiveSizePolicy -XX:-OmitStackTraceInFastThrow");

	printf("最大内存（MB）：");
	cin >> Xmx;
	printf("最小内存（MB）：");
	cin >> Xmn;
	gameBuilder->setXmx(Xmx);
	gameBuilder->setXmn(Xmn);

	/*获取构造好的game*/
	game = gameBuilder->getGame();

	launchCommandFile.open(string(launchVersion + ".bat").c_str(), ios::out | ios::binary | ios::trunc);

	/*获取启动命令*/
	launchCommand = launcher->getString(game, Option::LAUNCH);

	launchCommandFile << launchCommand.toLocal8Bit().toStdString();
	printf("启动脚本已生成！\n");
	launchCommandFile.close();
	/*
	QVector<QString> ret = launcher->getStringVector(game, Option::JAVA_PATH);

	for (size_t i = 0; i < ret.size(); i++)
	{
		cout << ret[i].toLocal8Bit().toStdString() << endl;
	}
	*/
	return 0;
}
