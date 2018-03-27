#include "QGSFileTools.h"

QGSFileTools::QGSFileTools()
{
}

QGSFileTools & QGSFileTools::getInstance()
{
	static QGSFileTools instance;
	return instance;
}

QGSFileTools::~QGSFileTools()
{
}

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

QStringList QGSFileTools::extractDirectory(const QString & file, const QString & directory)
{
	QStringList ret;

	try
	{
		ret = JlCompress::extractDir(file, directory);
	}
	catch (...)
	{
		ret.clear();
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
