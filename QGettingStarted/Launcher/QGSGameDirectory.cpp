#include <QJsonDocument>
#include <QDebug>
#include <QTextStream>

#include "QGSGameDirectory.h"
#include "QGSGameVersionPraser.h"
#include "../Util/QGSExceptionVersionNotFound.h"
#include "../Util/QGSExceptionIO.h"
#include "../Util/QGSExceptionJsonPraseError.h"
#include "../GameVersion/QGSLibrary.h"
#include "../GameVersion/QGSAssetIndexInfoFactory.h"

static const QString SEPARATOR = QGSOperatingSystem::getInstance().getSeperator();

QGSGameDirectory::QGSGameDirectory(const QDir & baseDir, QObject * parent) :QObject(parent), mBaseDir(baseDir)
{
	init();
}

QGSGameDirectory::QGSGameDirectory(QDir && baseDir, QObject * parent) :QObject(parent), mBaseDir(baseDir)
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
			throw QGSExceptionIO(mBaseDir.absolutePath());
		}
	}
	
	/*
		"./versions/"
	*/
	QFile launcherProfilesJsonFile(mBaseDir.absolutePath() + SEPARATOR + "launcher_profiles.json");
	if (!launcherProfilesJsonFile.exists())
	{
		if (launcherProfilesJsonFile.open(QIODevice::WriteOnly | QIODevice::Truncate))
		{
			QByteArray defaultData{
				"{\"selectedProfile\": \"QGettingStarted\",\"profiles\": {\"(Default)\": {\"name\": \"(QGettingStarted)\"}},\"clientToken\": \"88888888-8888-8888-8888-888888888888\"}"};
			QTextStream textStream(&launcherProfilesJsonFile);
			textStream << defaultData;
		}
		else
		{
			throw QGSExceptionIO(launcherProfilesJsonFile.fileName());
		}
	}

	if (!mBaseDir.exists("." + SEPARATOR + "versions" + SEPARATOR))
	{
		if (!mBaseDir.mkpath("." + SEPARATOR + "versions" + SEPARATOR))
		{
			throw QGSExceptionIO(mBaseDir.absolutePath() + SEPARATOR + "versions" + SEPARATOR);
		}
	}

	if (!mBaseDir.exists("." + SEPARATOR + "libraries" + SEPARATOR))
	{
		if (!mBaseDir.mkpath("." + SEPARATOR + "libraries" + SEPARATOR))
		{
			throw QGSExceptionIO(mBaseDir.absolutePath() + SEPARATOR + "versions" + SEPARATOR);
		}
	}

	if (!mBaseDir.exists("." + SEPARATOR + "assets" + SEPARATOR))
	{
		if (!mBaseDir.mkpath("." + SEPARATOR + "assets" + SEPARATOR))
		{
			throw QGSExceptionIO(mBaseDir.absolutePath() + SEPARATOR + "assets" + SEPARATOR);
		}
	}
}

const QGSGameVersion & QGSGameDirectory::getVersion(const QString & version)
{
	if (version.isEmpty())
	{
		throw QGSExceptionVersionNotFound();
	}

	if (!containsGameVersion(version))
	{
		addGameVersion(version);
	}

	return mVersionMap[version];
}

const QGSGameVersion & QGSGameDirectory::getVersion(const QGSGameVersionInfo & gameVersionInfo)
{
	return getVersion(gameVersionInfo.getId());
}

const QGSGameVersion & QGSGameDirectory::addGameVersion(const QString version)
{
	QGSGameVersion newVersion;
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
		QStringList versionJsonList = versionDir.entryList(QStringList("*.json"), QDir::NoDotAndDotDot);
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
		throw QGSExceptionIO();
	}
	QJsonParseError jsonPraseError;
	QJsonDocument jsonDocument(QJsonDocument::fromJson(versionJsonFile.readAll(), &jsonPraseError));
	if (jsonPraseError.error != QJsonParseError::NoError)
	{
		versionJsonFile.flush();
		versionJsonFile.close();
		throw QGSExceptionJsonPraseError(jsonPraseError);
	}
	//解析json生成version
	QSharedPointer<QGSGameVersionPraser> versionPraser(new QGSGameVersionPraser());
	versionPraser->praseVersion(newVersion, jsonDocument);
	auto ret(mVersionMap.insert(version, newVersion));

	return !newVersion.getInheritsFrom().isEmpty() ? addGameVersion(newVersion.getInheritsFrom()) : *ret;
}

const QGSGameVersion & QGSGameDirectory::addGameVersion(const QGSGameVersionInfo & gameVersionInfo)
{
	return addGameVersion(gameVersionInfo.getId());
}

bool QGSGameDirectory::containsGameVersion(const QString & version)const
{
	return mVersionMap.contains(version);
}

bool QGSGameDirectory::containsGameVersion(const QGSGameVersionInfo & gameVersionInfo) const
{
	return containsGameVersion(gameVersionInfo.getId());
}

QFile * QGSGameDirectory::generateGameVersionJarFile(const QString & version, const bool withAbsolutePath)const
{
	return new QFile((withAbsolutePath ? mBaseDir.absolutePath() : "") + SEPARATOR + "versions" + SEPARATOR + version + SEPARATOR + version + ".jar");
}

QFile * QGSGameDirectory::generateGameVersionJarFile(const QGSGameVersionInfo & gameVersionInfo, const bool withAbsolutePath) const
{
	return generateGameVersionJarFile(gameVersionInfo.getId(), withAbsolutePath);
}

QFile * QGSGameDirectory::generateGameVersionJsonFile(const QString & version, const bool withAbsolutePath) const
{
	return new QFile((withAbsolutePath ? mBaseDir.absolutePath() : "") + SEPARATOR + "versions" + SEPARATOR + version + SEPARATOR + version + ".json");
}

QFile * QGSGameDirectory::generateGameVersionJsonFile(const QGSGameVersionInfo & gameVersionInfo, const bool withAbsolutePath) const
{
	return generateGameVersionJsonFile(gameVersionInfo.getId(), withAbsolutePath);
}

QFile * QGSGameDirectory::generateAssetIndexJsonFile(const QGSAssetIndex & assetIndex, const bool withAbsolutePath) const
{
	return new QFile((withAbsolutePath ? mBaseDir.absolutePath() : "") + SEPARATOR + "assets" + SEPARATOR + "indexes" + SEPARATOR + assetIndex.getId() + ".json");
}

QFile * QGSGameDirectory::generateAssetIndexJsonFile(const QString & version, const bool withAbsolutePath)
{
	return generateAssetIndexJsonFile(getVersion(version).getAssetIndex(), withAbsolutePath);
}

QFile * QGSGameDirectory::generateAssetIndexJsonFile(const QGSGameVersionInfo & gameVersionInfo, const bool withAbsolutePath)
{
	auto rootVersionId(gameVersionInfo.getId());

	while (!getVersion(rootVersionId).getInheritsFrom().isEmpty())
	{
		rootVersionId = getVersion(rootVersionId).getInheritsFrom();
	}

	return generateAssetIndexJsonFile(rootVersionId, withAbsolutePath);
}

QFile * QGSGameDirectory::generateLibraryFile(const QGSLibrary & library, const bool withAbsolutePath)const
{
	return new QFile((withAbsolutePath ? mBaseDir.absolutePath() : "") + SEPARATOR + "libraries" + SEPARATOR + praseLibraryName(library));
}

QVector<QFile *> QGSGameDirectory::generateLibraryFiles(const QList<QGSLibrary> & libraryList, const bool withAbsolutePath) const
{
	QVector<QFile *> ret;

	for (auto & i : libraryList)
	{
		ret.push_back(generateLibraryFile(i, withAbsolutePath));
	}

	return ret;
}

QFile * QGSGameDirectory::generateAssetObjectFile(const QGSAssetObject & assetObject, const bool withAbsolutePath)
{
	auto && hash(assetObject.getHash());
	return new QFile((withAbsolutePath ? mBaseDir.absolutePath() : "") +
		SEPARATOR + "assets" + SEPARATOR + "objects" + SEPARATOR + hash.left(2) + SEPARATOR + hash);
}

QDir QGSGameDirectory::generateVersionsDirectory(const bool withAbsolutePath) const
{
	return QDir((withAbsolutePath ? mBaseDir.absolutePath() : "") + SEPARATOR + "versions");
}

QDir QGSGameDirectory::generateLibrariesDirectory(const bool withAbsolutePath) const
{
	return QDir((withAbsolutePath ? mBaseDir.absolutePath() : "") + SEPARATOR + "libraries");
}

QDir QGSGameDirectory::generateAssetsDirectory(const bool withAbsolutePath)
{
	return QDir((withAbsolutePath ? mBaseDir.absolutePath() : "") + SEPARATOR + "assets");
}

QDir QGSGameDirectory::generateNativesDirectory(const QString & version, const bool withAbsolutePath)const
{
	return QDir((withAbsolutePath ? mBaseDir.absolutePath() : "") + SEPARATOR + "versions" + SEPARATOR + version + SEPARATOR + version + "-natives");
}

QDir QGSGameDirectory::generateNativesDirectory(const QGSGameVersionInfo & gameVersionInfo, const bool withAbsolutePath) const
{
	return generateNativesDirectory(gameVersionInfo.getId(), withAbsolutePath);
}

QDir QGSGameDirectory::getBaseDir() const
{
	return mBaseDir;
}

QString QGSGameDirectory::generateGameVersionJarFileName(const QString & version, const bool withAbsolutePath)const
{
	return (withAbsolutePath ? mBaseDir.absolutePath() : "") + SEPARATOR + "versions" + SEPARATOR + version + SEPARATOR + version + ".jar";
}

QString QGSGameDirectory::generateGameVersionJarFileName(const QGSGameVersionInfo & gameVersionInfo, const bool withAbsolutePath) const
{
	return generateGameVersionJarFileName(gameVersionInfo.getId(), withAbsolutePath);
}

QString QGSGameDirectory::generateGameVersionJsonFileName(const QString & version, const bool withAbsolutePath) const
{
	return (withAbsolutePath ? mBaseDir.absolutePath() : "") + SEPARATOR + "versions" + SEPARATOR + version + SEPARATOR + version + ".json";
}

QString QGSGameDirectory::generateGameVersionJsonFileName(const QGSGameVersionInfo & gameVersionInfo, const bool withAbsolutePath) const
{
	return generateGameVersionJsonFileName(gameVersionInfo.getId(), withAbsolutePath);
}

QString QGSGameDirectory::generateLibraryFileName(const QGSLibrary & library, const bool withAbsolutePath) const
{
	return (withAbsolutePath ? mBaseDir.absolutePath() : "") + SEPARATOR + "libraries" + SEPARATOR + praseLibraryName(library);
}

QString QGSGameDirectory::generateAssetIndexJsonFileName(const QGSAssetIndex & assetIndex, const bool withAbsolutePath) const
{
	return (withAbsolutePath ? mBaseDir.absolutePath() : "") + SEPARATOR + "assets" + SEPARATOR + "indexes" + SEPARATOR + assetIndex.getId() + ".json";
}

QString QGSGameDirectory::generateAssetIndexJsonFileName(const QString & version, const bool withAbsolutePath)
{
	return generateAssetIndexJsonFileName(getVersion(version).getAssetIndex(), withAbsolutePath);
}

QString QGSGameDirectory::generateAssetIndexJsonFileName(const QGSGameVersionInfo & gameVersionInfo, const bool withAbsolutePath)
{
	auto rootVersionId(gameVersionInfo.getId());

	while (!getVersion(rootVersionId).getInheritsFrom().isEmpty())
	{
		rootVersionId = getVersion(rootVersionId).getInheritsFrom();
	}

	return generateAssetIndexJsonFileName(rootVersionId, withAbsolutePath);
}

QString QGSGameDirectory::generateAssetObjectFileName(const QGSAssetObject & assetObject, const bool withAbsolutePath)
{
	auto && hash(assetObject.getHash());
	return (withAbsolutePath ? mBaseDir.absolutePath() : "") +
		SEPARATOR + "assets" + SEPARATOR + "objects" + SEPARATOR + hash.left(2) + SEPARATOR + hash;
}

bool QGSGameDirectory::generateAssetsDirectory(QString version, const QGSAssetIndex & assetIndex, QDir & dir)
{
	bool ret = true;
	QString assetsBaseDirStr(mBaseDir.absolutePath() + SEPARATOR + "assets");

	if (!assetIndex.getId().isEmpty())
	{
		if (assetIndex.getId().contains("legacy"))
		{
			dir = QDir(assetsBaseDirStr + SEPARATOR + "virtual" + SEPARATOR + "legacy");
			ret = true;
		}
		else
		{
			dir = QDir(assetsBaseDirStr);
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
			int signPosition(version.indexOf("-"));
			if (signPosition != -1)
			{
				version.truncate(signPosition);
			}
			auto & rootVersion(getVersion(version));

			auto && assetIndex(rootVersion.getAssetIndex());
			QFile assetJsonFile(assetsBaseDirStr + SEPARATOR + "indexes" + SEPARATOR + assetIndex.getId() + ".json");
			if (!assetJsonFile.exists() || !assetJsonFile.open(QIODevice::ReadOnly))
			{
				dir = QDir(assetsBaseDirStr);
				ret = false;
			}
			else
			{
				QGSAssetIndexInfoFactory infoListFactory;
				auto && assetInfoList(infoListFactory.createAssetIndexInfo(assetJsonFile.readAll()));
				if (assetInfoList.getVirtual())
				{
					dir = QDir(assetsBaseDirStr + SEPARATOR + "virtual" + SEPARATOR + "legacy");
					ret = true;
				}
				else
				{
					dir = QDir(assetsBaseDirStr);
					ret = true;
				}
			}

		}
		catch (...)
		{
			if (version <= "1.7.2")
			{
				dir = QDir(assetsBaseDirStr + SEPARATOR + "virtual");
			}
			else
			{
				dir = QDir(assetsBaseDirStr);
			}
			ret = false;
		}
	}

	return ret;

}

QString QGSGameDirectory::praseLibraryName(const QGSLibrary & library)
{
	auto package(library.getPackage().replace(".", SEPARATOR));
	auto && name(library.getName());
	auto && version(library.getVersion());
	auto && nativesMap(library.getNatives());
	QString nativeString("");

	auto && keys(nativesMap.keys());
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

QString QGSGameDirectory::praseName(const QString & name)
{
	return QString(name.left(name.indexOf(":")).replace(".", SEPARATOR) +
		SEPARATOR + 
		name.mid(name.indexOf(":") + 1, name.lastIndexOf(":") - name.indexOf(":") - 1) + 
		SEPARATOR + 
		name.mid(name.lastIndexOf(":") + 1) + 
		SEPARATOR + 
		name.mid(name.indexOf(":") + 1, name.lastIndexOf(":") - name.indexOf(":") - 1) + 
		"-" + 
		name.mid(name.lastIndexOf(":") + 1) + 
		".jar");
}

