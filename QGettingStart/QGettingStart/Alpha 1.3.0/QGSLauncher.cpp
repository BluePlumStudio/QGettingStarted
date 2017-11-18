#include "QGSLauncher.h"

#include <iostream>

#define ARM		"arm"
#define ARM64	"arm64"
#define I386	"i386"
#define IA64	"ia64"
#define MIPS	"mips"
#define MIPS64	"mips64"
#define POWER	"power"
#define POWER64 "power64"
#define SPARC	"sparc"
#define SPARCV9 "sparcv9"
#define X86_64	"x86_64"

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

	//需要game的选项
	if (tmpGame)
	{
		if (option & LIBRARIES)
		{
			strVector = mLauncher.getStyledLibrariesStringVector(tmpGame->mGame, true);
		}
		else if (option & LIBRARIES_MISSING)
		{
			strVector = mLauncher.getMissingLibrariesStringVector(tmpGame->mGame, true);
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

	//不需要game的选项
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

	return ret;
}

QString QGSLauncher::getString(Game * game, OptionFlags option, QString arg)
{
	QGSGame * tmpGame = (QGSGame *)game;
	string str;
	QString ret;

	if (tmpGame)
	{
		if (option & Option::LAUNCH)
		{
			int pos = -1;
			QString JVMArgument = tmpGame->getJVMArgument();
			QString preInstruction = tmpGame->getPreInstruction();
			QString serverAddress = tmpGame->getServerAddress();
			QString gameArgument = tmpGame->getGameArgument();

			mLauncher.getLaunchString(tmpGame->mGame, str);
			ret = QString::fromLocal8Bit(str.c_str());

			if (!JVMArgument.isEmpty())
			{
				pos = ret.indexOf("\"", ret.indexOf("\"") + 1);
				if (pos != -1)
				{
					ret.insert(pos + 1, " " + JVMArgument);
					pos = -1;
				}
			}

			if (!preInstruction.isEmpty())
			{
				pos = ret.indexOf("\"");
				if (pos != -1)
				{
					ret.insert(pos, preInstruction + " ");
					pos = -1;
				}
			}

			if (!serverAddress.isEmpty())
			{
				QString address = "";
				QString port = "";
				QString argument = "";
				praseServerAddress(serverAddress, address, port);
				//--server 127.0.0.1 --port 6666
				argument = QString(" --server %1 --port %2").arg(address).arg(port);
				ret.insert(ret.length(), argument);
			}

			if (!gameArgument.isEmpty())
			{
				ret.insert(ret.length(), " " + gameArgument);
			}
		}
		else if (option & Option::MINECRAFT_ARGUMENTS)
		{
			str = mLauncher.getStyledMinecraftArgumentsString(tmpGame->mGame);
			ret = QString::fromLocal8Bit(str.c_str());
		}
		else
		{
			str = "";
			ret = "";
		}
	}

	return ret;
}

bool QGSLauncher::getJavaPathVectorFromStorage(QVector<QString> & vector, QString baseDirectory)
{
	QDir dir;
	int i = 0;
	QFileInfoList fileInfoList;
	QSysInfo::WinVersion winVersion = QSysInfo::windowsVersion();
	
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
			if (winVersion != QSysInfo::WV_None)
			{
				if (fileInfo.fileName() == "javaw.exe")
				{
					vector.push_back(fileInfo.path());
					//cout << fileInfo.filePath().toLocal8Bit().toStdString() << endl;
				}

			}
			else
			{
				if (fileInfo.fileName() == "java")
				{
					vector.push_back(fileInfo.path());
					//cout << fileInfo.filePath().toLocal8Bit().toStdString() << endl;
				}
			}

		}

		i++;
	}

	return true;
}

bool QGSLauncher::getJavaPathVectorFromSystemSettings(QVector<QString> & vector)
{
	QStringList list;
	const QString cpuArchitecture = QSysInfo::currentCpuArchitecture();
	QSettings * JavaEnvReg;
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
	if (cpuArchitecture == ARM64 ||
		cpuArchitecture == IA64 ||
		cpuArchitecture == MIPS64 ||
		cpuArchitecture == POWER64 ||
		cpuArchitecture == X86_64)
	{
		JavaEnvReg = new QSettings("HKEY_LOCAL_MACHINE\\SOFTWARE\\JavaSoft\\Java Runtime Environment", QSettings::Registry64Format);
	}
	else
	{
		JavaEnvReg = new QSettings("HKEY_LOCAL_MACHINE\\SOFTWARE\\JavaSoft\\Java Runtime Environment", QSettings::Registry32Format);
	}
	
	if (!JavaEnvReg)
	{
		return false;
	}
	
	list = JavaEnvReg->childGroups();
	//cout << list.size() << endl << endl;

	for (int i = 0; i < list.size(); i++)
	{
		QString var = list[i];
		JavaEnvReg->beginGroup(var);

		QString str = JavaEnvReg->value("JavaHome").toString();

		if (!str.isEmpty())
		{
			if (!str[str.length() - 1].isLetterOrNumber())
			{
				str[str.length() - 1] = 0;
			}
			vector.push_back(str + "\\bin");
			//cout << ins.toLocal8Bit().toStdString() << endl;
		}

		JavaEnvReg->endGroup();
	}

	if (JavaEnvReg)
	{
		delete JavaEnvReg;
	}

	return true;
}

void QGSLauncher::praseServerAddress(QString serverAddress, QString & address, QString & port)
{
	address = serverAddress.section(":", 0, 0);
	port = serverAddress.section(":", 1, 1);
}