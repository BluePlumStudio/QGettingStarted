#include "QGSLauncher.h"

#include <iostream>

using namespace std;

QGSLauncher::QGSLauncher()
{
}


QGSLauncher::~QGSLauncher()
{
}

QVector<QString> QGSLauncher::getStringVector(Game * game, OptionFlags option, QString arg)
{
	QGSGame * tmpGame = dynamic_cast<QGSGame *>(game);
	vector<string> strVector;
	QVector<QString> ret;
	QFileInfoList fileInfoList = QDir::drives();

	if (tmpGame)
	{
		if (option & LIBRARIES)
		{
			strVector = mLauncher.getStyledLibrariesStringVector(tmpGame->game, true);
		}
		else if (option & LIBRARIES_MISSING)
		{
			strVector = mLauncher.getMissingLibrariesStringVector(tmpGame->game, true);
		}
		else
		{
			strVector.clear();
			ret.clear();
		}

		for (vector<string>::iterator it = strVector.begin(); it != strVector.end(); ++it)
		{
			ret.push_back(QString::fromLocal8Bit((*it).c_str()));
		}
	}
	else
	{
		if (option & JAVA_PATH)
		{
			if (option & SYSTEM_SETTINGS)
			{
				getJavaPathVectorFromSystemSettings(ret);
			}
			else
			{
				if (arg.isEmpty())
				{
					for (int i = 0; i < fileInfoList.size(); i++)
					{
						cout << fileInfoList[i].filePath().toLocal8Bit().toStdString() << endl;
						getJavaPathVectorFromStorage(ret, fileInfoList[i].filePath());
					}
				}
				else
				{
					getJavaPathVectorFromStorage(ret, arg);
				}
			}

		}
	}

	return ret;
}

QString QGSLauncher::getString(Game * game, OptionFlags option, QString arg)
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

bool QGSLauncher::getJavaPathVectorFromStorage(QVector<QString> & vector, QString baseDirectory)
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
			getJavaPathVectorFromStorage(vector, fileInfo.filePath());
		}
		else
		{
#ifdef Q_OS_WIN32
			if (fileInfo.fileName() == "javaw.exe")
			{
				vector.push_back(fileInfo.path());
				//cout << fileInfo.filePath().toLocal8Bit().toStdString() << endl;
			}
#else
			if (fileInfo.fileName() == "java")
			{
				vector.push_back(fileInfo.path());
				//cout << fileInfo.filePath().toLocal8Bit().toStdString() << endl;
			}
#endif
		}

		i++;
	}

	return true;
}

bool QGSLauncher::getJavaPathVectorFromSystemSettings(QVector<QString> & vector)
{
#ifdef Q_OS_WIN32
	QStringList list;
	/*
	//获取默认Java版本
#ifdef Q_OS_WIN64
	QSettings uninstallReg("HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall", QSettings::Registry64Format);
#else
	QSettings uninstallReg("HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall", QSettings::Registry32Format);
#endif
	list = uninstallReg.childGroups();
	//cout << list.size() << endl << endl;

	for (int i = 0; i < list.size(); i++)
	{
		QString var = list[i];
		uninstallReg.beginGroup(var);

		QString str = uninstallReg.value("Contact").toString();

		if (str == "http://java.com")
		{
			QString ins = uninstallReg.value("InstallLocation").toString();
			if (!ins[ins.length() - 1].isLetterOrNumber())
			{
				ins[ins.length() - 1] = 0;
			}
			vector.push_back(ins + "\\bin");
			//cout << ins.toLocal8Bit().toStdString() << endl;
		}

		uninstallReg.endGroup();
	}
	*/

	//获取其他Java版本
#ifdef Q_OS_WIN64
	QSettings JavaEnvReg("HKEY_LOCAL_MACHINE\\SOFTWARE\\JavaSoft\\Java Runtime Environment", QSettings::Registry64Format);
#else
	QSettings JavaEnvReg("HKEY_LOCAL_MACHINE\\SOFTWARE\\JavaSoft\\Java Runtime Environment", QSettings::Registry32Format);
#endif
	list = JavaEnvReg.childGroups();
	//cout << list.size() << endl << endl;

	for (int i = 0; i < list.size(); i++)
	{
		QString var = list[i];
		JavaEnvReg.beginGroup(var);

		QString str = JavaEnvReg.value("JavaHome").toString();

		if (!str.isEmpty())
		{
			if (!str[str.length() - 1].isLetterOrNumber())
			{
				str[str.length() - 1] = 0;
			}
			vector.push_back(str + "\\bin");
			//cout << ins.toLocal8Bit().toStdString() << endl;
		}

		JavaEnvReg.endGroup();
	}

#endif

	return true;
}
