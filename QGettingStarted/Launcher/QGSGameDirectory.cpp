#include <QJsonDocument>

#include "QGSGameDirectory.h"
#include "../Util/QGSExceptionVersionNotFound.h"
#include "../Util/QGSExceptionFileIO.h"
#include "../Util/QGSExceptionJsonPraseError.h"
#include "VersionPraser/QGSVersionPraser.h"
#include "../Version/Library.h"

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
		throw QGSExceptionFileIO(mBaseDir.absolutePath());
	}
	
	/*
		"./versions/"
	*/
	if (!mBaseDir.exists("." + SEPARATOR + "versions" + SEPARATOR))
	{
		throw QGSExceptionFileIO(mBaseDir.absolutePath() + SEPARATOR + "versions" + SEPARATOR);
	}
}

const Version & QGSGameDirectory::getVersion(const QString & version)
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

QFile * QGSGameDirectory::generateVersionJarFile(const QString & version)const
{
	return new QFile(mBaseDir.absolutePath() + SEPARATOR + "versions" + SEPARATOR + version + SEPARATOR + version + ".jar");
}

QFile * QGSGameDirectory::generateLibraryFile(const Library & library)const
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

	return new QFile(
		mBaseDir.absolutePath() + SEPARATOR + "libraries" + SEPARATOR + package + SEPARATOR + name + SEPARATOR + version + SEPARATOR + name + "-" + version + nativeString + ".jar");
}

QDir QGSGameDirectory::generateNativesDirectory(const QString & version)const
{
	return QDir(mBaseDir.absolutePath() + SEPARATOR + "versions" + SEPARATOR + version + SEPARATOR + version + "-natives");
}

QDir QGSGameDirectory::getBaseDir() const
{
	return mBaseDir;
}

QDir QGSGameDirectory::generateAssetDirectory(const QString & version, const AssetIndex & assetIndex)
{
	/*
	QFile fileAssetJson{ mBaseDir.absolutePath() + SEPARATOR + "assets" + SEPARATOR + "indexes" + SEPARATOR + assetIndex.getId() + ".json" };
	if (!fileAssetJson.exists())
	{
		throw QGSExceptionFileIO(fileAssetJson.fileName());
	}
	*/
	if (assetIndex.getId().contains("legacy"))
	{
		return QDir(mBaseDir.absolutePath() + SEPARATOR + "assets" + SEPARATOR + "virtual");
	}
	else
	{
		return QDir(mBaseDir.absolutePath() + SEPARATOR + "assets");
	}
}

const Version & QGSGameDirectory::addVersion(const QString & version)
{
	Version newVersion;
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
	QSharedPointer<QGSVersionPraser> versionPraser{ new QGSVersionPraser() };
	versionPraser->praseVersion(newVersion, jsonDocument);
	return !newVersion.getInheritsFrom().isEmpty()
		? addVersion(newVersion.getInheritsFrom())
		: *(mVersionMap.insert(version, newVersion));
}