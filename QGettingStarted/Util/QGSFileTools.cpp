#include <QDir>
#include <QFileInfoList>
#include <QCoreApplication>
#include <QSettings>
#include <QDebug>

#include "QGSFileTools.h"
#include "QGSOperatingSystem.h"

static const QString SEPARATOR(QGSOperatingSystem::getInstance().getSeperator());

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

QStringList QGSFileTools::extractDirectory(const QString & filePath, const QString & directory, const QString & password)
{
	QStringList ret;

	unz_global_info64 gi;
	unz_file_info64 fileInfo;
	unzFile zFile(unzOpen64(filePath.toLocal8Bit().toStdString().c_str()));

	if (unzGetGlobalInfo64(zFile, &gi) == UNZ_OK)
	{
		for (int i = 0; i < gi.number_entry; i++)
		{
			QDir newDir;
			char fileName[256]{ 0 };
			char ext[256]{ 0 };
			char com[1024]{ 0 };
			if (unzGetCurrentFileInfo64(zFile, &fileInfo, fileName, sizeof(fileName), ext, 256, com, 1024) != UNZ_OK)
			{
				unzClose(zFile);
				ret.clear();
				break;
			}

			QString unzFileName(QString::fromLocal8Bit(fileName));
			QString path(directory + SEPARATOR + unzFileName);
			QFileInfo targetInfo(path);

			ret << path;

			if (!(fileInfo.external_fa & FILE_ATTRIBUTE_DIRECTORY) && path.back() != "/"&& path.back() != "\\")
			{
				unzOpenCurrentFile(zFile);//无密码
				unzOpenCurrentFilePassword(zFile, password.toLocal8Bit().toStdString().c_str());//有密码

				QFile target(path);
				targetInfo.absoluteDir().mkpath("./");
				if (!target.open(QIODevice::WriteOnly | QIODevice::Truncate))
				{
					unzClose(zFile);
					ret.clear();
					break;
				}
				while (true)
				{
					char data[256]{ 0 };
					int size(unzReadCurrentFile(zFile, data, 256));
					if (size <= 0)
					{
						break;
					}
					target.write(data, size);
				}
				target.close();
				unzCloseCurrentFile(zFile);
			}
			else
			{
				newDir.mkpath(path);
				unzCloseCurrentFile(zFile);
			}

			unzGoToNextFile(zFile);
		}

		unzClose(zFile);
	}

	return ret;
}

QString QGSFileTools::extractFile(const QString & filePath, const QString & file, const QString & directory, const QString & password)
{
	QString ret;

	unz_global_info64 gi;
	unz_file_info64 fileInfo;
	unzFile zFile(unzOpen64(filePath.toLocal8Bit().toStdString().c_str()));

	if (unzGetGlobalInfo64(zFile, &gi) == UNZ_OK)
	{
		for (int i = 0; i < gi.number_entry; i++)
		{
			QDir newDir;
			char fileName[256]{ 0 };
			char ext[256]{ 0 };
			char com[1024]{ 0 };
			if (unzGetCurrentFileInfo64(zFile, &fileInfo, fileName, sizeof(fileName), ext, 256, com, 1024) != UNZ_OK)
			{
				unzClose(zFile);
				ret.clear();
				break;
			}

			QString unzFileName(QString::fromLocal8Bit(fileName));

			if (QDir::toNativeSeparators(unzFileName) == QDir::toNativeSeparators(file))
			{
				QString path(directory + QDir::separator() + unzFileName);

				if (!(fileInfo.external_fa & FILE_ATTRIBUTE_DIRECTORY))
				{
					unzOpenCurrentFile(zFile);//无密码
					unzOpenCurrentFilePassword(zFile, password.toLocal8Bit().toStdString().c_str());//有密码

					QFile target(path);
					QFileInfo(target).absoluteDir().mkpath("./");
					if (!target.open(QIODevice::WriteOnly | QIODevice::Truncate))
					{
						unzClose(zFile);
						ret.clear();
						break;
					}
					while (true)
					{
						char data[256]{ 0 };
						int size(unzReadCurrentFile(zFile, data, 256));
						if (size <= 0)
						{
							break;
						}
						target.write(data, size);
					}
					target.close();
					unzCloseCurrentFile(zFile);
				}
				else
				{
					newDir.mkpath(path);
					unzCloseCurrentFile(zFile);
				}

				ret = path;

				break;
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
			if (currentFileInfo.isFile()) /* 如果是文件，删除文件 */
			{
				QFile fileTemp(currentFileInfo.filePath());
				fileTemp.remove();
				fileInfoList.removeAt(i);
			}

			if (currentFileInfo.isDir()) /* 如果是文件夹 */
			{
				QDir dirTemp(currentFileInfo.filePath());
				fileInfoListTemp = dirTemp.entryInfoList(QDir::Dirs | QDir::Files
					| QDir::Readable | QDir::Writable
					| QDir::Hidden | QDir::NoDotAndDotDot
					, QDir::Name);
				if (fileInfoListTemp.size() == 0) /* 下层没有文件或文件夹 则直接删除*/
				{
					dirTemp.rmdir(".");
					fileInfoList.removeAt(i);
				}
				else /* 下层有文件夹或文件 则将信息添加到列表*/
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
	dir.rmdir(".");/*删除目标文件夹,如果只是清空文件夹absolutPath的内容而不删除absolutPath本身,则删掉本行即可*/
	return !dir.exists();
}

QMap<QString, QString> QGSFileTools::getJavaPathListFromSystemSettings()
{
	QMap<QString, QString> ret;

#ifdef Q_OS_WIN

	const auto && cpuArchitecture(QGSOperatingSystem::getInstance().getCurrentCpuArchitecture());
	QSettings * JavaEnvReg;

	//获取其他Java版本
	if (cpuArchitecture == QGSCpuArchitecture::ARM64 ||
		cpuArchitecture == QGSCpuArchitecture::IA64 ||
		cpuArchitecture == QGSCpuArchitecture::MIPS64 ||
		cpuArchitecture == QGSCpuArchitecture::POWER64 ||
		cpuArchitecture == QGSCpuArchitecture::X86_64)
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
			ret.insert(prefix, str + QDir::separator() + "bin");
		}

		JavaEnvReg->endGroup();
	}

	if (JavaEnvReg)
	{
		JavaEnvReg->deleteLater();
	}

#endif

	return ret;
}
