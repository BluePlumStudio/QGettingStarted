#include "QGSUtil.h"

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

#define XMX_SMALLEST_M 128
#define CHAR_SPACE ' '
#define STRING_SPACE " "

//":"��"."���滻���š�
#ifdef Q_OS_WIN
const QString replacement0("\\");
#elif
const QString replacement0("/");
#endif


QGSUtil::QGSUtil()
{
}


QGSUtil::~QGSUtil()
{
}

QGSUtil * QGSUtil::getInstance()
{
	static QGSUtil instance;

	return &instance;
}

QGSAbstractLauncher::LauncherError QGSUtil::getLibrariesStringVector(QGSGame * game, QVector<QString> & item)
{
	QVector<QString> stringVector;

	do
	{
		QJsonObject jsonObject;
		jsonObject = game->getJsonDocument().object();
		if (!jsonObject.contains("libraries"))
		{
			return QGSAbstractLauncher::LauncherError(QString::fromLocal8Bit("Jsonδ����\"libraries\"����"), QGSAbstractLauncher::LauncherError::Error::JSON_LIBRARIES_NOT_INCLUDED);
		}
		//libraries�������顣
		QJsonArray jsonArray;
		jsonArray = jsonObject.value("libraries").toArray();
		const int size = jsonArray.size();
		for (uint i = 0; i < size; i++)
		{
			QJsonObject libraryObject = jsonArray.at(i).toObject();
			QString name;
			if (praseLibraryAllow(libraryObject))
			{
				praseLibraryName(libraryObject, name);
				if (!name.isEmpty())
				{
					stringVector.push_back(name);
				}

			}

		}
	} while (game = game->getFatherPtr());

	item = stringVector;

	return 	QGSAbstractLauncher::LauncherError(QString::fromLocal8Bit("��ȡLibrariesStringVector�ɹ���"), QGSAbstractLauncher::LauncherError::Error::NO_ERROR);
}

QGSAbstractLauncher::LauncherError QGSUtil::getMissingLibrariesStringVector(QGSGame * game, QVector<QString> & item)
{
	/*
	//ֻ��ȡ���İ汾ȱʧ�ļ�
	while (game->getFatherPtr())
	{
		game = game->getFatherPtr();
	}
	*/
	QVector<QString> jarFilePathVector;
	auto ret(getLibrariesStringVector(game, jarFilePathVector));

	if (ret.mLaunchError != QGSAbstractLauncher::LauncherError::Error::NO_ERROR)
	{
		return ret;
	}

	QFile jarFile;

	for (auto jarFilePath : jarFilePathVector)
	{
		jarFile.setFileName(game->getGamePath() + replacement0 + "libraries" + replacement0 + jarFilePath);

		if (!jarFile.exists())
		{
			item.push_back(jarFilePath);
		}
	}

	return ret = QGSAbstractLauncher::LauncherError(QString::fromLocal8Bit("��ȡMissingLibrariesStringVector�ɹ���"), QGSAbstractLauncher::LauncherError::Error::NO_ERROR);
}

QGSAbstractLauncher::LauncherError QGSUtil::getMinecraftArgumentsString(QGSGame * game, QString & item)
{
	QJsonObject jsonObject = game->getJsonDocument().object();

	//����Ƿ����minecraftArguments��
	if (!jsonObject.contains("minecraftArguments"))
	{
		return QGSAbstractLauncher::LauncherError(QString::fromLocal8Bit("Jsonδ����\"minecraftArguments\"�ַ�����"), QGSAbstractLauncher::LauncherError::Error::JSON_MINECRAFT_ARGUMENTS_NOT_INCLUDED);
	}

	QString minecraftArguments(jsonObject.value("minecraftArguments").toString());
	minecraftArguments = jsonObject.value("minecraftArguments").toString();
	auto * gamePtr = game;//����Ѱ�Ҽ̳а汾��

	//�����滻���ݿ������д
	replaceVariable(minecraftArguments, "version", "\"BluePlum Studio.\"");

	//��Ϸ·����.minecraft��
	replaceVariable(minecraftArguments, "gameDir", "\"" + game->getGamePath() + "\"");

	//��Դ�ļ���·��
	replaceVariable(minecraftArguments, "assetsDir", "\"" + game->getGamePath() + replacement0 + "assets\"");

	//�ҵ����ļ̳а汾
	while (gamePtr->getFatherPtr())
	{
		gamePtr = gamePtr->getFatherPtr();
	}

	//�����е�һ����--assetIndex ${assets_index_name} ��Ҫ���ⷽ����ȡ��
	jsonObject = gamePtr->getJsonDocument().object();
	/*
	if (!jsonObject.contains("assets"))
	{
		return QGSAbstractLauncher::LauncherError("minecraftArgumentsδ����\"assets\"������", QGSAbstractLauncher::LauncherError::Error::MINECRAFT_ARGUMENTS_VARIABLE_NOT_INCLUDED);
	}
	QString assetsIndexName(jsonObject.value("assets").toString());
	//replaceVariable(minecraftArguments, "assets", assetsIndexName);
	replaceVariable(minecraftArguments, "assetIndex", assetsIndexName);
	*/
	if (jsonObject.contains("assets"))
	{
		QString assetsIndex(jsonObject.value("assets").toString());
		replaceVariable(minecraftArguments, "assetIndex", assetsIndex);
	}
	else if (jsonObject.contains("assetIndex"))
	{
		QString assetsIndex(jsonObject.value("assetIndex").toObject().value("id").toString());
		replaceVariable(minecraftArguments, "assetIndex", assetsIndex);
	}

	//�û�
	//Legacy
	QString userType = game->getUserType();
	if (userType == "Legacy")
	{
		QString LegacyUUID = getUUID(game->getPlayerName());
		replaceVariable(minecraftArguments, "username", game->getPlayerName());
		//uuid�����ߵĿ������д��32λ��ֻҪ�������ظ�
		replaceVariable(minecraftArguments, "uuid", LegacyUUID);
		//accessToken�����ߺ�����һ��
		replaceVariable(minecraftArguments, "accessToken", LegacyUUID);
		//session��1.6
		replaceVariable(minecraftArguments, "session", LegacyUUID);
		//�û����ͣ�����Legacy��
		replaceVariable(minecraftArguments, "userType", userType);
	}
	//mojang
	else if (userType == "mojang")
	{

	}

	//�еİ汾�Ѿ�д�ã�����Forge�汾�������д��Forge
	replaceVariable(minecraftArguments, "versionType", "\"BluePlum Studio.\"");

	//�������ʶ�𲻵��Ĳ��������磺--userType ${user_type}ʶ�𲻵������Ϊ--userType {}
	int location = -1;//������λ�á�
	while ((location = minecraftArguments.indexOf("$")) != -1)
	{
		minecraftArguments.replace(minecraftArguments.indexOf("$", location),
			minecraftArguments.indexOf("}", location) - minecraftArguments.indexOf("$", location) + 1,
			"{}");
		location = -1;
	}

	item = minecraftArguments;

	return QGSAbstractLauncher::LauncherError(QString::fromLocal8Bit("��ȡMinecraftArgumentsString�ɹ���"), QGSAbstractLauncher::LauncherError::Error::NO_ERROR);
}

QGSAbstractLauncher::LauncherError QGSUtil::getLibrariesVector(QGSGame * game, QVector<Library> & item)
{
	QVector<Library> libraryVector;

	do
	{
		Library library;
		QJsonObject jsonObject;
		jsonObject = game->getJsonDocument().object();
		if (!jsonObject.contains("libraries"))
		{
			return QGSAbstractLauncher::LauncherError(QString::fromLocal8Bit("Jsonδ����\"libraries\"����"), QGSAbstractLauncher::LauncherError::Error::JSON_LIBRARIES_NOT_INCLUDED);
		}
		//libraries�������顣
		QJsonArray jsonArray;
		jsonArray = jsonObject.value("libraries").toArray();
		const int size = jsonArray.size();
		for (uint i = 0; i < size; i++)
		{
			QJsonObject libraryObject = jsonArray.at(i).toObject();
			//����name��
			if (praseLibraryAllow(libraryObject))
			{
				praseLibraryName(libraryObject, library.mName);
				if (library.mName.isEmpty())
				{
					continue;
				}

				//����ԭ��downloads
				if (!game->getFatherPtr())
				{
					praseOriginLibraryDownloads(libraryObject, library);
				}

				libraryVector.push_back(library);
			}


		}
	} while (game = game->getFatherPtr());

	item = libraryVector;

	return 	QGSAbstractLauncher::LauncherError(QString::fromLocal8Bit("��ȡLibrariesVector�ɹ���"), QGSAbstractLauncher::LauncherError::Error::NO_ERROR);
}

bool QGSUtil::replaceVariable(QString & arguments, QString before, QString after)
{
	int location = -1;//��������������λ��
	int begin = -1;//�滻�ַ�����λ��
	int end = -1;//βλ��

	if ((location = arguments.indexOf(before)) != -1)//����Ƿ��иñ���
	{
		if ((begin = arguments.indexOf(" ", location)) != -1)
		{
			++begin;
			if (arguments[begin] == '$')
			{
				if ((end = arguments.indexOf(" ", begin)) == -1)
				{
					end = arguments.length();
				}

				arguments.replace(begin, end - begin, after);

				return true;
			}
		}
	}

	return false;
}

bool QGSUtil::getJavaPathVectorFromStorage(QVector<QString> & vector, QString baseDirectory)
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
#ifdef Q_OS_WIN
			if (fileInfo.fileName() == "javaw.exe")
			{
				vector.push_back(fileInfo.path());
				//cout << fileInfo.filePath().toLocal8Bit().toStdString() << endl;
			}
#elif
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

bool QGSUtil::getJavaPathVectorFromSystemSettings(QVector<QString> & vector)
{
	QStringList list;
	const QString cpuArchitecture(QSysInfo::currentCpuArchitecture());
	QSettings * JavaEnvReg;
	/*
	//��ȡĬ��Java�汾
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

	//��ȡ����Java�汾
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
		QString var(list[i]);
		JavaEnvReg->beginGroup(var);

		QString str(JavaEnvReg->value("JavaHome").toString());

		if (!str.isEmpty())
		{
			if (!str[str.length() - 1].isLetterOrNumber())
			{
				str[str.length() - 1] = 0;
			}
			vector.push_back(str + replacement0 + "bin");
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

void QGSUtil::praseServerAddress(QString serverAddress, QString & address, QString & port)
{
	address = serverAddress.section(":", 0, 0);
	port = serverAddress.section(":", 1, 1);
}

void QGSUtil::praseLibraryName(QJsonObject & libraryObject, QString & name)
{
	int last0 = 0;//":"
	int index1 = 0;//"."
	int first0 = 0;//":"
	if (!libraryObject.contains("name"))
	{
		return;
	}
	QString origin(libraryObject.value("name").toString());
	//��ȡ��һ��":"��
	if (origin.indexOf(":", first0) != -1)
	{
		first0 = last0 = origin.indexOf(":", first0);
	}
	QString jarFileName(origin.begin() + first0 + 1);//Jar�ļ�����
	while (origin.indexOf(":", last0) != -1)//�����µ�":"ȫ���滻��
	{
		last0 = origin.indexOf(":", last0);
		origin.replace(last0, 1, replacement0);
	}

	while (origin.indexOf(".", index1) != -1)
	{
		index1 = origin.indexOf(".", index1);
		if (first0 == -1 || index1 < first0)
		{
			origin.replace(index1, 1, replacement0);
		}
		else//Json���ݴ��󣬲�����":"��index1 < first0��
		{
			break;
		}
	}
	//��ȡ�ļ�����׺natives....��
	QString natives;
	if (libraryObject.contains("natives"))
	{
		QJsonObject nativesObject = libraryObject.value("natives").toObject();

#ifdef Q_OS_WIN
		if (nativesObject.contains("windows"))
		{
			natives = nativesObject.value("windows").toString();
		}
#endif

#ifdef Q_OS_MACOS
		if (nativesObject.contains("osx"))
		{
			natives = nativesObject.value("osx").toString();
		}
#endif

#ifndef Q_OS_WIN
#ifndef Q_OS_MACOS
		if (nativesObject.contains("linux"))
		{
			natives = nativesObject.value("linux").toString();
		}
#endif
#endif
	}
	//ת��Jar�ļ�����
	while (jarFileName.indexOf(":") != -1)
	{
		jarFileName.replace(":", "-");
	}
	if (!natives.isEmpty())//����natives��׺
	{
		jarFileName.append("-" + natives);
	}
	jarFileName.append(".jar");//����".jar"��׺��

	name = origin + replacement0 + jarFileName;
}

bool QGSUtil::praseLibraryAllow(QJsonObject & libraryObject)
{
	QJsonArray rulesArray;
	bool allowed = false;// �Ƿ�����������

	//���rules�Ƿ�����������
	if (libraryObject.contains("rules"))
	{
		rulesArray = libraryObject.value("rules").toArray();
		for (uint j = 0; j < rulesArray.size(); j++)
		{
			QJsonObject ruleObject = rulesArray[j].toObject();

			if (!ruleObject.contains("action"))
			{
				continue;
			}

			QString action(ruleObject.value("action").toString());

			if (action == "allow")
			{
				if (ruleObject.contains("os"))
				{
					QString OSName(ruleObject.value("os").toString());
#ifdef Q_OS_WIN
					if (OSName == "windows")
					{
						allowed = true;
						break;
					}
#endif

#ifdef Q_OS_MACOS
					if (OSName == "osx")
					{
						allowed = true;
						break;
					}
#endif

#ifndef Q_OS_WIN
#ifndef Q_OS_MACOS
					if (OSName == "linux")
					{
						allowed = true;
						break;
					}
#endif
#endif
				}
				else
				{
					allowed = true;
					break;
				}
			}
			else if (action == "disallow")
			{
				if (ruleObject.contains("os"))
				{
					QString OSName(ruleObject.value("os").toString());
#ifdef Q_OS_WIN
					if (OSName == "windows")
					{
						allowed = false;
						break;
					}
#endif

#ifdef Q_OS_MACOS
					if (OSName == "osx")
					{
						allowed = false;
						break;
					}
#endif

#ifndef Q_OS_WIN
#ifndef Q_OS_MACOS
					if (OSName == "linux")
					{
						allowed = false;
						break;
					}
#endif
#endif
				}
				else
				{
					allowed = false;
					break;
				}
			}
		}
	}
	else
	{
		allowed = true;
	}

	return allowed;
}

void QGSUtil::praseOriginLibraryDownloads(QJsonObject & libraryObject, Library & library, QString URL)
{
	Library::Downloads newDownloads;
	if (libraryObject.contains("downloads"))
	{
		QJsonObject downloadsObject(libraryObject.value("downloads").toObject());
		if (downloadsObject.contains("classifiers"))
		{
			QJsonObject classifiersObject(downloadsObject.value("classifiers").toObject());
			QJsonObject nativesObject;
#ifdef Q_OS_WIN
			if (classifiersObject.contains("natives-windows"))
			{
				nativesObject = classifiersObject.value("natives-windows").toObject();
			}
#endif

#ifdef Q_OS_MACOS
			if (classifiersObject.contains("natives-osx"))
			{
				nativesObject = classifiersObject.value("natives-osx").toObject();
			}
#endif

#ifndef Q_OS_WIN
#ifndef Q_OS_MACOS
			if (classifiersObject.contains("natives-linux"))
			{
				nativesObject = classifiersObject.value("natives-linux").toObject();
			}
#endif
#endif
			if (nativesObject.contains("size"))
			{
				newDownloads.mSize = nativesObject.value("size").toInt();
			}

			if (nativesObject.contains("sha1"))
			{
				newDownloads.mSHA1 = nativesObject.value("sha1").toString();
			}

			if (nativesObject.contains("path"))
			{
				newDownloads.mPath = nativesObject.value("path").toString();
			}

			if (nativesObject.contains("url"))
			{
				newDownloads.mURL = nativesObject.value("url").toString();
			}
		}
		else if (downloadsObject.contains("artifact"))
		{
			QJsonObject artifactObject(downloadsObject.value("artifact").toObject());

			if (artifactObject.contains("size"))
			{
				newDownloads.mSize = artifactObject.value("size").toInt();
			}

			if (artifactObject.contains("sha1"))
			{
				newDownloads.mSHA1 = artifactObject.value("sha1").toString();
			}

			if (artifactObject.contains("path"))
			{
				newDownloads.mPath = artifactObject.value("path").toString();
			}

			if (artifactObject.contains("url"))
			{
				newDownloads.mURL = artifactObject.value("url").toString();
			}
		}
	}

	if (libraryObject.contains("url"))
	{
		newDownloads.mURL = libraryObject.value("url").toString();
	}

	if (newDownloads.mURL.isEmpty() && !URL.isEmpty())
	{
		int index = -1;
		QString name = library.mName;
		if (name.isEmpty())
		{
			praseLibraryName(libraryObject, name);
		}

		name.replace(replacement0, "/");

		newDownloads.mURL = URL + name;
	}

	if (newDownloads.mPath.isEmpty())
	{
		newDownloads.mPath = library.mName;
	}

	library.mDownloads = newDownloads;
}

QString QGSUtil::getUUID(QString seed)
{
	QString UUID;
	char * code = "x@&asd%j2813";
	char UUIDChars[] = "bad260ecde3bfe752a";
	int i = 0;

	if (seed.isEmpty())
	{
		return UUID;
	}

	while (UUID.length() < 32)
	{
		char c1 = 0;
		char c2 = 0;
		char c = 0;

		srand(seed[(i + code[i % strlen(code)]) % seed.length()].toLatin1() + i);
		c1 = 'a' + rand() % 6;
		c2 = '0' + rand() % 10;
		c = rand() % 32;
		if (c>16)
		{
			if (rand() % 2)
			{
				UUID.push_back(c1);
			}
			else
			{
				UUID.push_back(c2);
			}
		}
		else
		{
			UUID.push_back(UUIDChars[c]);
		}


		i = (i + 1) % 65536;
	}

	return UUID;
}