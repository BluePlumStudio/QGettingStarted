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
