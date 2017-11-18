#include <QtCore/QCoreApplication>

#include "QConfig.h"

int main(int argc, char *argv[])
{
	//QCoreApplication a(argc, argv);

	QConfig config;
	QSolution solution;

	config.appendSolution(solution);
	config.writeFile("config.json");

	//return a.exec();
	return 0;
}
