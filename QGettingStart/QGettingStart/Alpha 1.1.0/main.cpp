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

	printf("�����汾��");
	getline(cin, in);
	launchVersion = in;
	gameBuilder->setGameVersion(QString::fromLocal8Bit(in.c_str()));

	printf("��Ϸ·����.minecraft����");
	getline(cin, in);
	gameBuilder->setGamePath(QString::fromLocal8Bit(in.c_str()));
	
	printf("Java·����.exe����");
	getline(cin, in);
	gameBuilder->setJavaPath(QString::fromLocal8Bit(in.c_str()));

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
	gameBuilder->setExtraArgument("-XX:HeapDumpPath=MojangTricksIntelDriversForPerformance_javaw.exe_minecraft.exe.heapdump -XX:+UseG1GC -XX:-UseAdaptiveSizePolicy -XX:-OmitStackTraceInFastThrow");

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
	/*
	QVector<QString> ret = launcher->getStringVector(game, Option::JAVA_PATH);

	for (size_t i = 0; i < ret.size(); i++)
	{
		cout << ret[i].toLocal8Bit().toStdString() << endl;
	}
	*/
	return 0;
}
