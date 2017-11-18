#include "QGSLauncher.h"

#include <iostream>

using namespace std;

QGSLauncher::QGSLauncher()
{
}


QGSLauncher::~QGSLauncher()
{
}

QVector<QString> QGSLauncher::getStringVector(Game * game, Option option, QString arg)
{
	QGSGame * tmpGame = dynamic_cast<QGSGame *>(game);
	vector<string> strVector;
	QVector<QString> ret;
	QFileInfoList fileInfoList = QDir::drives();

	if (tmpGame)
	{
		switch (option)
		{
		case Option::LIBRARIES:
			strVector = mLauncher.getStyledLibrariesStringVector(tmpGame->game, true);
			break;
		case Option::LIBRARIES_MISSING:
			strVector = mLauncher.getMissingLibrariesStringVector(tmpGame->game, true);
			break;
		case Option::JAVA_PATH:
			if (arg.isEmpty())
			{
				for (int i = 0; i < fileInfoList.size(); i++)
				{
					cout << fileInfoList[i].filePath().toLocal8Bit().toStdString() << endl;
					getJavaPathVector(ret, fileInfoList[i].filePath());
				}
			}
			else
			{
				getJavaPathVector(ret, arg);
			}
			//
			break;
		default:
			strVector.clear();
			ret.clear();
			break;
		}

		for (vector<string>::iterator it = strVector.begin(); it != strVector.end(); ++it)
		{
			ret.push_back(QString::fromLocal8Bit((*it).c_str()));
		}
	}

	return ret;
}

QString QGSLauncher::getString(Game * game, Option option, QString arg)
{
	QGSGame * tmpGame = (QGSGame *)game;
	string str;
	QString ret;

	if (tmpGame)
	{
		switch (option)
		{
		case Option::LAUNCH:
			mLauncher.getLaunchString(tmpGame->game, str);
			break;
		case Option::MINECRAFT_ARGUMENTS:
			str = mLauncher.getStyledMinecraftArgumentsString(tmpGame->game);
			break;
		default:
			str = "";
			ret = "";
			break;
		}

		ret = QString::fromLocal8Bit(str.c_str());
	}

	return ret;
}

bool QGSLauncher::getJavaPathVector(QVector<QString> & vector, QString baseDirectory)
{
	QDir dir;
	int i = 0;
	QFileInfoList fileInfoList;

	dir.setPath(baseDirectory);
	if (!dir.exists())
	{
		return false;
	}

	fileInfoList = dir.entryInfoList();
	while (i < fileInfoList.size())
	{
		QFileInfo fileInfo = fileInfoList.at(i);
		if (fileInfo.fileName() == "." ||
			fileInfo.fileName() == "..")
		{
			i++;
			continue;
		}

		//cout << fileInfo.filePath().toLocal8Bit().toStdString() << endl;

		if (fileInfo.isDir())
		{
			getJavaPathVector(vector, fileInfo.filePath());
		}
		else
		{
			if (fileInfo.fileName() == "javaw.exe")
			{
				vector.push_back(fileInfo.filePath());
				//cout << fileInfo.filePath().toLocal8Bit().toStdString() << endl;
			}
		}

		i++;
	}

	return true;
}

/*
bool FindFile(const QString & path)
{
	QDir dir(path);
	if (!dir.exists())
		return false;
	dir.setFilter(QDir::Dirs | QDir::Files);
	dir.setSorting(QDir::DirsFirst);
	QFileInfoList list = dir.entryInfoList();
	int i = 0;
	do{

		QFileInfo fileInfo = list.at(i);
		if (fileInfo.fileName() == "." | fileInfo.fileName() == "..")
		{
			i++;
			continue;
		}
		bool bisDir = fileInfo.isDir();
		if (bisDir)
		{
			nFiles++;
			std::cout << qPrintable(QString("%1 %2 %3").arg(fileInfo.size(), 10)
				.arg(fileInfo.fileName(), 10).arg(fileInfo.path())) << endl;

			FindFile(fileInfo.filePath());
		}
		else{
			nFiles++;
			std::cout << qPrintable(QString("%1 %2 %3").arg(fileInfo.size(), 10)
				.arg(fileInfo.fileName(), 10).arg(fileInfo.path())) << endl;
		}
		i++;
	} while (i<list.size());
	return true;
}
*/

