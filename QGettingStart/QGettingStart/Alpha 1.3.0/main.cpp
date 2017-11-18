#include <QtCore/QCoreApplication>

#include "QGettingStart.h"

#ifdef WIN32
#include <Windows.h>
#endif

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

	printf("�����汾��");
	getline(cin, in);
	launchVersion = in;
	gameBuilder->setGameVersion(QString::fromLocal8Bit(in.c_str()));

	printf("��Ϸ·����.minecraft����");
	getline(cin, in);
	gameBuilder->setGamePath(QString::fromLocal8Bit(in.c_str()));
	
	printf("Java·����.exe����");
	//getline(cin, in);
	//gameBuilder->setJavaPath(QString::fromLocal8Bit(in.c_str()));
	gameBuilder->setJavaPath(launcher->getStringVector(nullptr, Option::JAVA_PATH | Option::SYSTEM_SETTINGS)[0] + "/javaw.exe");

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
	gameBuilder->setJVMArgument("-XX:+UseG1GC -XX:-UseAdaptiveSizePolicy -XX:-OmitStackTraceInFastThrow");
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
	game = gameBuilder->getGame();

	launchCommandFile.open(string(launchVersion + ".bat").c_str(), ios::out | ios::binary | ios::trunc);

	/*��ȡ��������*/
	launchCommand = launcher->getString(game, Option::LAUNCH);

	launchCommandFile << launchCommand.toLocal8Bit().toStdString();
	printf("�����ű������ɣ�\n");
	launchCommandFile.close();
	return 0;
}
