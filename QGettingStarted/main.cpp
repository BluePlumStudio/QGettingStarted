#include <QtCore/QCoreApplication>
#include <iostream>
#include <string>

#include "Launcher/QGSGameDirectory.h"

int main(int argc, char *argv[])
{
	//QCoreApplication a(argc, argv);
	using namespace std;

	string directory;
	getline(cin, directory);
	IGameDirectory * gameDirectory = new QGSGameDirectory(QDir(QString::fromLocal8Bit(directory.c_str())));

	string version;
	getline(cin, version);
	gameDirectory->getVersion(QString::fromLocal8Bit(version.c_str()));

	//return a.exec();
}
