#include <QJsonDocument>

#include "QGSGameDirectory.h"
#include "../Util/QGSExceptionInvalidBaseDirectory.h"
#include "../Util/QGSExceptionInvalidVersionsDirectory.h"
#include "../Util/QGSExceptionVersionNotFound.h"
#include "../Util/QGSExceptionFileOpenFailure.h"
#include "../Util/QGSExceptionJsonDocumentCreateFailure.h"
#include "VersionPraseStrategy/QGSVersionPraseStrategyFactory.h"

static const QString SEPARATOR = QGSOperatingSystem::getInstance().getSeparator();

QGSGameDirectory::QGSGameDirectory(const QDir & baseDir) :IGameDirectory(baseDir)
{
	init();
}

QGSGameDirectory::QGSGameDirectory(QDir && baseDir) : IGameDirectory(baseDir)
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
		throw QGSExceptionInvalidBaseDirectory();
	}
	
	/*
		"./versions/"
	*/
	if (!mBaseDir.exists("." + SEPARATOR + "versions" + SEPARATOR))
	{
		throw QGSExceptionInvalidVersionsDirectory();
	}
}

const Version & QGSGameDirectory::getVersion(const QString & version)
{
	if (containsVersion(version))
	{
		return mMapVersions[version];
	}
	else
	{
		return addVersion(version);
	}
}

bool QGSGameDirectory::containsVersion(const QString & version)const
{
	return mMapVersions.contains(version);
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
		throw QGSExceptionFileOpenFailure();
	}
	QJsonParseError jsonPraseError;
	QJsonDocument jsonDocument{ QJsonDocument::fromJson(versionJsonFile.readAll(),&jsonPraseError) };
	if (jsonPraseError.error != QJsonParseError::NoError)
	{
		versionJsonFile.flush();
		versionJsonFile.close();
		throw QGSExceptionJsonDocumentCreateFailure(jsonPraseError);
	}
	//解析json生成version
	QSharedPointer<QGSVersionPraseStrategyFactory> factory{ new QGSVersionPraseStrategyFactory() };
	auto & strategy = factory->getVersionPraseStrategy(jsonDocument);
	strategy.praseVersion(newVersion, jsonDocument);
	return *(mMapVersions.insert(version, newVersion));
}