#include <QDir>
#include <QFileInfoList>
#include <QCoreApplication>
#include <QSettings>

#include "QGSFileTools.h"
#include "QGSOperatingSystem.h"

static const QString SEPERATOR(QGSOperatingSystem::getInstance().getSeperator());

QGSFileTools::QGSFileTools(QObject * parent) :QObject(parent)
{
}

QGSFileTools & QGSFileTools::getInstance()
{
	static QGSFileTools instance(QCoreApplication::instance());
	return instance;
}

QGSFileTools::~QGSFileTools()
{
}

/*
bool QGSFileTools::compressDirectory(const QString & file, const QString & directory, bool recursive)
{
	bool ret = true;

	try
	{
		ret = JlCompress::compressDir(file, directory);
	}
	catch (...)
	{
		ret = false;
	}

	return ret;
}
*/

QStringList QGSFileTools::extractDirectory(const QString & file, const QString & directory, const QString & password)
{
	QStringList ret;

	unz_global_info64 gi;
	unz_file_info64 FileInfo;
	unzFile zFile(unzOpen64(file.toLocal8Bit().toStdString().c_str()));

	if (unzGetGlobalInfo64(zFile, &gi) == UNZ_OK)
	{
		for (int i = 0; i < gi.number_entry; i++)
		{
			char file[256]{ 0 };
			char ext[256]{ 0 };
			char com[1024]{ 0 };
			if (unzGetCurrentFileInfo64(zFile, &FileInfo, file, sizeof(file), ext, 256, com, 1024) != UNZ_OK)
			{
				unzClose(zFile);
				ret.clear();
				return ret;
			}
			if (!(FileInfo.external_fa & FILE_ATTRIBUTE_DIRECTORY))
			{
				unzOpenCurrentFile(zFile);//������
				unzOpenCurrentFilePassword(zFile, password.toLocal8Bit().toStdString().c_str());//������
				QString path(directory + SEPERATOR + file);
				ret << path;
				QFile targetFile(path);
				if (!targetFile.open(QIODevice::WriteOnly | QIODevice::Truncate))
				{
					unzClose(zFile);
					ret.clear();
					return ret;
				}
				while (true)
				{
					char data[256]{ 0 };
					int size(unzReadCurrentFile(zFile, data, 256));
					//qDebug() << size;
					if (size <= 0)
					{
						break;
					}
					targetFile.write(data, size);
				}
				targetFile.close();
				unzCloseCurrentFile(zFile);
			}
			else
			{
				QDir newDir;
				newDir.mkpath(directory + SEPERATOR + file);
				unzCloseCurrentFile(zFile);
			}
			unzGoToNextFile(zFile);
		}
		unzClose(zFile);
	}

	return ret;
}

bool QGSFileTools::removeDirectory(const QString & absolutPath)
{
	QDir dir(absolutPath);
	QFileInfoList fileInfoList;
	QFileInfo currentFileInfo;
	QFileInfoList fileInfoListTemp;
	qint32 infoNum;

	fileInfoList = dir.entryInfoList(QDir::Dirs | QDir::Files
		| QDir::Readable | QDir::Writable
		| QDir::Hidden | QDir::NoDotAndDotDot
		, QDir::Name);

	while (fileInfoList.size() > 0)
	{
		infoNum = fileInfoList.size();

		for (auto i = infoNum - 1; i >= 0; i--)
		{
			currentFileInfo = fileInfoList[i];
			if (currentFileInfo.isFile()) /* ������ļ���ɾ���ļ� */
			{
				QFile fileTemp(currentFileInfo.filePath());
				fileTemp.remove();
				fileInfoList.removeAt(i);
			}

			if (currentFileInfo.isDir()) /* ������ļ��� */
			{
				QDir dirTemp(currentFileInfo.filePath());
				fileInfoListTemp = dirTemp.entryInfoList(QDir::Dirs | QDir::Files
					| QDir::Readable | QDir::Writable
					| QDir::Hidden | QDir::NoDotAndDotDot
					, QDir::Name);
				if (fileInfoListTemp.size() == 0) /* �²�û���ļ����ļ��� ��ֱ��ɾ��*/
				{
					dirTemp.rmdir(".");
					fileInfoList.removeAt(i);
				}
				else /* �²����ļ��л��ļ� ����Ϣ��ӵ��б�*/
				{
					for (auto j = 0; j < fileInfoListTemp.size(); j++)
					{
						if (!(fileInfoList.contains(fileInfoListTemp[j])))
						{
							fileInfoList.append(fileInfoListTemp[j]);
						}
					}
				}
			}
		}
	}
	dir.rmdir(".");/*ɾ��Ŀ���ļ���,���ֻ������ļ���absolutPath�����ݶ���ɾ��absolutPath����,��ɾ�����м���*/
	return !dir.exists();
}

QMap<QString, QString> QGSFileTools::getJavaPathListFromSystemSettings()
{
	QMap<QString, QString> ret;

#ifdef Q_OS_WIN

	const auto && cpuArchitecture(QGSOperatingSystem::getInstance().getCurrentCpuArchitecture());
	QSettings * JavaEnvReg;

	//��ȡ����Java�汾
	if (cpuArchitecture == CpuArchitecture::ARM64 ||
		cpuArchitecture == CpuArchitecture::IA64 ||
		cpuArchitecture == CpuArchitecture::MIPS64 ||
		cpuArchitecture == CpuArchitecture::POWER64 ||
		cpuArchitecture == CpuArchitecture::X86_64)
	{
		JavaEnvReg = new QSettings("HKEY_LOCAL_MACHINE\\SOFTWARE\\JavaSoft\\Java Runtime Environment", QSettings::Registry64Format);
	}
	else
	{
		JavaEnvReg = new QSettings("HKEY_LOCAL_MACHINE\\SOFTWARE\\JavaSoft\\Java Runtime Environment", QSettings::Registry32Format);
	}

	if (!JavaEnvReg)
	{
		return ret;
	}

	auto && childGroups(JavaEnvReg->childGroups());
	for (auto & prefix : childGroups)
	{
		JavaEnvReg->beginGroup(prefix);
		QString str(JavaEnvReg->value("JavaHome").toString());

		if (!str.isEmpty())
		{
			if (!str[str.length() - 1].isLetterOrNumber())
			{
				str[str.length() - 1] = 0;
			}
			ret.insert(prefix, str + SEPERATOR + "bin");
		}

		JavaEnvReg->endGroup();
	}

	if (JavaEnvReg)
	{
		delete JavaEnvReg;
	}

#endif

	return ret;
}
