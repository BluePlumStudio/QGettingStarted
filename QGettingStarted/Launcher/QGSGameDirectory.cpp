#include <QJsonDocument>
#include <QDebug>

#include "QGSGameDirectory.h"
#include "../Util/QGSExceptionVersionNotFound.h"
#include "../Util/QGSExceptionFileIO.h"
#include "../Util/QGSExceptionJsonPraseError.h"
#include "VersionPraser/QGSGameVersionPraser.h"
#include "../GameVersion/Library.h"
#include "../GameVersion/QGSAssetIndexInfoFactory.h"

static const QString SEPARATOR = QGSOperatingSystem::getInstance().getSeparator();

QGSGameDirectory::QGSGameDirectory(const QDir & baseDir) :mBaseDir(baseDir)
{
	init();
}

QGSGameDirectory::QGSGameDirectory(QDir && baseDir) : mBaseDir(baseDir)
{
	init();
}

QGSGameDirectory::~QGSGameDirectory()
{
}

void QGSGameDirectory::init()
{
	if (!mBaseDir.exists())
	{
		if (!mBaseDir.mkpath("." + SEPARATOR))
		{
			throw QGSExceptionFileIO(mBaseDir.absolutePath());
		}
	}
	
	/*
		"./versions/"
	*/
	if (!mBaseDir.exists("." + SEPARATOR + "versions" + SEPARATOR))
	{
		if (!mBaseDir.mkpath("." + SEPARATOR + "versions" + SEPARATOR))
		{
			throw QGSExceptionFileIO(mBaseDir.absolutePath() + SEPARATOR + "versions" + SEPARATOR);
		}
	}

	if (!mBaseDir.exists("." + SEPARATOR + "libraries" + SEPARATOR))
	{
		if (!mBaseDir.mkpath("." + SEPARATOR + "libraries" + SEPARATOR))
		{
			throw QGSExceptionFileIO(mBaseDir.absolutePath() + SEPARATOR + "versions" + SEPARATOR);
		}
	}

	if (!mBaseDir.exists("." + SEPARATOR + "assets" + SEPARATOR))
	{
		if (!mBaseDir.mkpath("." + SEPARATOR + "assets" + SEPARATOR))
		{
			throw QGSExceptionFileIO(mBaseDir.absolutePath() + SEPARATOR + "assets" + SEPARATOR);
		}
	}
}

const GameVersion & QGSGameDirectory::getVersion(const QString & version)
{
	if (version.isEmpty())
	{
		throw QGSExceptionVersionNotFound();
	}

	if (!containsVersion(version))
	{
		addVersion(version);
	}

	return mVersionMap[version];
}

bool QGSGameDirectory::containsVersion(const QString & version)const
{
	return mVersionMap.contains(version);
}

QFile * QGSGameDirectory::generateGameVersionJarFile(const QString & version, const bool withAbsolutePath)const
{
	return new QFile((withAbsolutePath ? mBaseDir.absolutePath() : "") + SEPARATOR + "versions" + SEPARATOR + version + SEPARATOR + version + ".jar");
}

QFile * QGSGameDirectory::generateGameVersionJsonFile(const QString & version, const bool withAbsolutePath) const
{
	return new QFile((withAbsolutePath ? mBaseDir.absolutePath() : "") + SEPARATOR + "versions" + SEPARATOR + version + SEPARATOR + version + ".json");
}

QFile * QGSGameDirectory::generateAssetIndexJsonFile(const AssetIndex & assetIndex, const bool withAbsolutePath) const
{
	return new QFile((withAbsolutePath ? mBaseDir.absolutePath() : "") + SEPARATOR + "assets" + SEPARATOR + "indexes" + SEPARATOR + assetIndex.getId() + ".json");
}

QFile * QGSGameDirectory::generateLibraryFile(const Library & library, const bool withAbsolutePath)const
{
	return new QFile((withAbsolutePath ? mBaseDir.absolutePath() : "") + SEPARATOR + "libraries" + SEPARATOR + praseLibraryName(library));
}

QVector<QFile *> QGSGameDirectory::generateLibraryFiles(const QList<Library> & libraryList, const bool withAbsolutePath) const
{
	QVector<QFile *> ret;

	for (auto & i : libraryList)
	{
		ret.push_back(generateLibraryFile(i, withAbsolutePath));
	}

	return ret;
}

QDir QGSGameDirectory::generateNativesDirectory(const QString & version, const bool withAbsolutePath)const
{
	return QDir((withAbsolutePath ? mBaseDir.absolutePath() : "") + SEPARATOR + "versions" + SEPARATOR + version + SEPARATOR + version + "-natives");
}

QDir QGSGameDirectory::getBaseDir() const
{
	return mBaseDir;
}

QString QGSGameDirectory::praseLibraryName(const Library & library)
{
	auto package{ library.getPackage().replace(".", SEPARATOR) };
	auto && name{ library.getName() };
	auto && version{ library.getVersion() };
	auto && nativesMap{ library.getNatives() };
	QString nativeString{ "" };

	auto && keys{ nativesMap.keys() };
	for (auto & i : keys)
	{
		if (i.contains(QGSOperatingSystem::getInstance().getProductType()))
		{
			nativeString = "-" + nativesMap[i];
			nativeString.replace("${arch}", QString::number(QGSOperatingSystem::getInstance().getCurrentCpuArchitectureNumber()));
			break;
		}
	}

	return QString(package + SEPARATOR + name + SEPARATOR + version + SEPARATOR + name + "-" + version + nativeString + ".jar");
}

bool QGSGameDirectory::generateAssetsDirectory(QString version, const AssetIndex & assetIndex, QDir & dir)
{
	bool ret = true;
	QString assetsBaseDirStr{ mBaseDir.absolutePath() + SEPARATOR + "assets" };

	if (!assetIndex.getId().isEmpty())
	{
		if (assetIndex.getId().contains("legacy"))
		{
			dir = QDir{assetsBaseDirStr + SEPARATOR + "virtual" };
			ret = true;
		}
		else
		{
			dir = QDir{ assetsBaseDirStr };
			ret = true;
		}
	}
	else
	{
		try
		{
			while (!getVersion(version).getInheritsFrom().isEmpty())
			{
				version = getVersion(version).getInheritsFrom();
			}
			int signPosition{ version.indexOf("-") };
			if (signPosition != -1)
			{
				version.truncate(signPosition);
			}
			auto & rootVersion{ getVersion(version) };

			auto && assetIndex{ rootVersion.getAssetIndex() };
			QFile assetJsonFile{ assetsBaseDirStr + SEPARATOR + "indexes" + SEPARATOR + assetIndex.getId() + ".json" };
			if (!assetJsonFile.exists())
			{
				dir = QDir{ assetsBaseDirStr };
				ret = false;
			}
			if (!assetJsonFile.open(QIODevice::ReadOnly))
			{
				dir = QDir{ assetsBaseDirStr };
				ret = false;
			}
			QGSAssetIndexInfoFactory infoListFactory;
			auto && assetInfoList{ infoListFactory.createAssetIndexInfo(assetJsonFile.readAll()) };
			if (assetInfoList.getVirtual())
			{
				dir = QDir{ assetsBaseDirStr + SEPARATOR + "virtual" };
				ret = true;
			}
			else
			{
				dir = QDir{ assetsBaseDirStr };
				ret = true;
			}
		}
		catch (...)
		{
			if (version <= "1.7.2")
			{
				dir = QDir{ assetsBaseDirStr + SEPARATOR + "virtual" };
			}
			else
			{
				dir = QDir{ assetsBaseDirStr };
			}
			ret = false;
		}
	}

	return ret;

}

QDir QGSGameDirectory::generateAssetsDirectory(const bool withAbsolutePath)
{
	return QDir((withAbsolutePath ? mBaseDir.absolutePath() : "") + SEPARATOR + "assets");
}

QFile * QGSGameDirectory::generateAssetObjectFile(const AssetObject & assetObject, const bool withAbsolutePath)
{
	auto && hash{ assetObject.getHash() };
	return new QFile((withAbsolutePath ? mBaseDir.absolutePath() : "") +
		SEPARATOR + "assets" + SEPARATOR + "objects" + SEPARATOR + hash.left(2) + SEPARATOR + hash);
}

const GameVersion & QGSGameDirectory::addVersion(const QString version)
{
	GameVersion newVersion;
	//检查versions目录是否存在
	QDir versionDir(mBaseDir.absolutePath() + SEPARATOR + "versions" + SEPARATOR + version);
	if (!versionDir.exists())
	{
		throw QGSExceptionVersionNotFound();
	}
	//检查version.json文件是否存在
	QFile versionJsonFile(mBaseDir.absolutePath() + SEPARATOR + "versions" + SEPARATOR + version + SEPARATOR + version + ".json");
	if (!versionJsonFile.exists())
	{
		QStringList versionJsonList = versionDir.entryList(QStringList{ "*.json" }, QDir::NoDotAndDotDot);
		const QString versionJsonFileName = version + ".json";
		if (!versionJsonList.size())
		{
			throw QGSExceptionVersionNotFound();
		}
		if (versionJsonList[0] != versionJsonFileName)
		{
			versionDir.rename(versionJsonList[0], versionJsonFileName);
		}
	}
	//打开文件读取json
	if (!versionJsonFile.open(QIODevice::ReadOnly))
	{
		throw QGSExceptionFileIO();
	}
	QJsonParseError jsonPraseError;
	QJsonDocument jsonDocument{ QJsonDocument::fromJson(versionJsonFile.readAll(),&jsonPraseError) };
	if (jsonPraseError.error != QJsonParseError::NoError)
	{
		versionJsonFile.flush();
		versionJsonFile.close();
		throw QGSExceptionJsonPraseError(jsonPraseError);
	}
	//解析json生成version
	QSharedPointer<QGSGameVersionPraser> versionPraser{ new QGSGameVersionPraser() };
	versionPraser->praseVersion(newVersion, jsonDocument);
	auto ret{ mVersionMap.insert(version, newVersion) };

	return !newVersion.getInheritsFrom().isEmpty() ? addVersion(newVersion.getInheritsFrom()) : *ret;
}