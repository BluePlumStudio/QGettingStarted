#include <QJsonObject>
#include <QJsonArray>

#include "IVersionPraser.h"

IVersionPraser::IVersionPraser(const int minimunLaunchVersion) :mMinimunLaunchVersion(minimunLaunchVersion)
{

}

IVersionPraser::~IVersionPraser()
{

}


bool IVersionPraser::praseId(Version & version, QJsonObject & object)const
{
	if (!object.contains("id"))
	{
		return false;
	}

	version.setId(object.value("id").toString());
	return true;
}

bool IVersionPraser::praseArguments(Version & version, QJsonObject & object)const
{
	if (!object.contains("minecraftArguments") && !object.contains("arguments"))
	{
		return false;
	}

	if (object.contains("minecraftArguments"))
	{
		version.setMinecraftArguments(object.value("minecraftArguments").toString());
	}
	else if (object.contains("arguments"))
	{
		if (!object.contains("game") || !object.contains("jvm"))
		{
			return false;
		}

		QList<Arguments::Argument> jvm;
		QList<Arguments::Argument> game;
		auto arrayGame = object.value("game").toArray();
		auto arrayJvm = object.value("jvm").toArray();
		if (arrayGame.size() <= 0 || arrayJvm.size() <= 0)
		{
			return false;
		}
		for (auto & i : arrayGame)
		{
			if (i.isString())
			{
				game.push_back(Arguments::Argument{ i.toString() });
			}
			else if (i.isObject())
			{
				auto objectGame = i.toObject();
				//rules
				Rules rules;
				if (objectGame.contains("rules"))
				{
					rules = praseRules(objectGame.value("rules").toArray());
				}
				//value
				QStringList value;
				if (objectGame.contains("value"))
				{
					value = praseValue(objectGame.value("value"));
				}
				game.push_back(Arguments::Argument{ value,rules });
			}
		}
		for (auto & i : arrayJvm)
		{
			if (i.isString())
			{
				jvm.push_back(Arguments::Argument{ i.toString() });
			}
			else if (i.isObject())
			{
				auto objectGame = i.toObject();
				//rules
				Rules rules;
				if (objectGame.contains("rules"))
				{
					rules = praseRules(objectGame.value("rules").toArray());
				}
				//value
				QStringList value;
				if (objectGame.contains("value"))
				{
					value = praseValue(objectGame.value("value"));
				}
				jvm.push_back(Arguments::Argument{ value,rules });
			}
		}

		version.setArguments(Arguments{ jvm,game });
	}

	return true;
}

bool IVersionPraser::praseMainClass(Version & version, QJsonObject & object)const
{
	if (!object.contains("mainClass"))
	{
		return false;
	}

	version.setMainClass(object.value("mainClass").toString());
	return true;
}

bool IVersionPraser::praseInheritsFrom(Version & version, QJsonObject & object)const
{
	if (!object.contains("inheritsFrom"))
	{
		return false;
	}

	version.setInheritsFrom(object.value("inheritsFrom").toString());
	return true;
}

bool IVersionPraser::praseJar(Version & version, QJsonObject & object)const
{
	if (!object.contains("jar"))
	{
		return false;
	}

	version.setJar(object.value("jar").toString());
	return true;
}

bool IVersionPraser::praseAssetIndex(Version & version, QJsonObject & object)const
{
	if (!object.contains("assetIndex"))
	{
		return false;
	}

	auto assetIndexObject = object.value("assetIndex").toObject();
	if (!assetIndexObject.contains("id") ||
		!assetIndexObject.contains("sha1") ||
		!assetIndexObject.contains("size") ||
		!assetIndexObject.contains("url") ||
		!assetIndexObject.contains("totalSize"))
	{
		return false;
	}

	version.setAssetIndex(AssetIndex{
		assetIndexObject.value("size").toInt(),
		assetIndexObject.value("sha1").toString(),
		assetIndexObject.value("path").toString(),
		assetIndexObject.value("url").toString(),
		assetIndexObject.value("totalSize").toInt(),
		assetIndexObject.value("id").toString()
	});

	return true;
}

bool IVersionPraser::praseAssets(Version & version, QJsonObject & object)const
{
	if (!object.contains("assets"))
	{
		return false;
	}

	version.setAssets(object.value("assets").toString());
	return true;
}

bool IVersionPraser::praseLibraries(Version & version, QJsonObject & object)const
{
	if (!object.contains("libraries"))
	{
		return false;
	}

	QList<Library> libraries;
	auto arrayLibraries = object.value("libraries").toArray();
	for (auto & i : arrayLibraries)
	{
		libraries.push_back(praseLibrary(i.toObject()));
	}

	version.setLibraries(libraries);
	return true;
}

bool IVersionPraser::praseDownloads(Version & version, QJsonObject & object)const
{
	if (!object.contains("downloads"))
	{
		return false;
	}

	QMap<QString, Downloads::Download> mapDownloads;
	auto objectDownloads = object.value("downloads").toObject();
	auto keys = objectDownloads.keys();
	for (auto & i : keys)
	{
		auto objectDownload = objectDownloads.value(i).toObject();

		mapDownloads.insert(
			i,
			Downloads::Download{
			objectDownload.contains("size") ? objectDownload.value("size").toInt() : 0,
			objectDownload.contains("sha1") ? objectDownload.value("sha1").toString() : "",
			objectDownload.contains("path") ? objectDownload.value("path").toString() : "",
			objectDownload.contains("url") ? objectDownload.value("url").toString() : ""
		});
	}

	return true;
}

bool IVersionPraser::praseLogging(Version & version, QJsonObject & object)const
{
	if (!object.contains("logging"))
	{
		return false;
	}

	auto objectLogging = object.value("logging").toObject();
	QMap<QString, Logging> mapLogging;

	auto keys = objectLogging.keys();
	for (auto & i : keys)
	{
		Logging logging;
		auto objectDownloadType = objectLogging.value(i).toObject();

		if (objectDownloadType.contains("file"))
		{
			auto objectFile = objectDownloadType.value("file").toObject();
			logging.setFile(Logging::File{
				objectFile.contains("size") ? objectFile.value("size").toInt() : 0,
				objectFile.contains("sha1") ? objectFile.value("sha1").toString() : "",
				objectFile.contains("path") ? objectFile.value("path").toString() : "",
				objectFile.contains("url") ? objectFile.value("url").toString() : "",
				objectFile.contains("id") ? objectFile.value("id").toString() : ""
			});
		}
		logging.setArgument(objectDownloadType.contains("argument") ? objectDownloadType.value("argument").toString() : "");
		logging.setType(objectDownloadType.contains("type") ? objectDownloadType.value("type").toString() : "");

		mapLogging.insert(i, logging);
	}

	version.setLogging(mapLogging);
	return true;
}

bool IVersionPraser::praseType(Version & version, QJsonObject & object)const
{
	if (!object.contains("type"))
	{
		return false;
	}

	version.setType(object.value("type").toString());
	return true;
}

bool IVersionPraser::praseTime(Version & version, QJsonObject & object)const
{
	if (!object.contains("time"))
	{
		return false;
	}

	version.setTime(object.value("time").toString());
	return true;
}

bool IVersionPraser::praseReleaseTime(Version & version, QJsonObject & object)const
{
	if (!object.contains("releaseTime"))
	{
		return false;
	}

	version.setReleaseTime(object.value("releaseTime").toString());
	return true;
}

bool IVersionPraser::praseMinimumLauncherVersion(Version & version, QJsonObject & object)const
{
	if (!object.contains("minimumLauncherVersion"))
	{
		return false;
	}

	version.setMinimumLauncherVersion(object.value("minimumLauncherVersion").toInt());
	return true;
}
/**/
Rules IVersionPraser::praseRules(QJsonArray & arrayRules)const
{
	Rules rules;

	for (auto & i : arrayRules)
	{
		auto objectRule = i.toObject();

		auto action{ objectRule.contains("action") ? objectRule.value("action").toString() : Action::ALLOW };
		QMap<QString, bool> mapFeatures;
		QString os{ OS::UNKNOWN };
		QString osVersion;
		if (objectRule.contains("os"))
		{
			auto objectOs = objectRule.value("os").toObject();
			os = objectOs.contains("name") ? objectOs.value("name").toString() : OS::UNKNOWN;
			osVersion = objectOs.contains("version") ? objectOs.value("version").toString() : "";
		}
		if (objectRule.contains("features"))
		{
			auto objectFeatures = objectRule.value("features").toObject();

			auto keys = objectFeatures.keys();
			for (auto & k : keys)
			{
				mapFeatures.insert(k, objectFeatures.value(k).toBool());
			}
		}
		rules.addRule(Rules::Rule{ action,mapFeatures,os,osVersion });
	}

	return rules;
}

QStringList IVersionPraser::praseValue(QJsonValue & valueValue)const
{
	QStringList value;

	if (valueValue.isString())
	{
		value = QStringList(valueValue.toString());
	}
	else if (valueValue.isArray())
	{
		auto arrayValue = valueValue.toArray();
		for (auto & j : arrayValue)
		{
			value.push_back(j.toString());
		}
	}

	return value;
}
/**/
Library IVersionPraser::praseLibrary(QJsonObject & object)const
{
	Library library;

	//name
	if (object.contains("name"))
	{
		auto name = object.value("name").toString();

		library.setPackage(name.left(name.indexOf(":")));
		library.setName(name.mid(name.indexOf(":") + 1, name.lastIndexOf(":") - name.indexOf(":") - 1));
		library.setVersion(name.mid(name.lastIndexOf(":") + 1));
	}
	//natives
	if (object.contains("natives"))
	{
		auto objectNatives = object.value("natives").toObject();
		QMap<QString, QString> natives;

		auto keys = objectNatives.keys();
		for (auto & i : keys)
		{
			natives.insert(i, objectNatives.value(i).toString());
		}

		library.setNatives(natives);
		library.setNative(true);
	}
	//extract
	if (object.contains("extract"))
	{
		auto objectExtract = object.value("extract").toObject();
		Extract extract;

		if (objectExtract.contains("exclude"))
		{
			auto arrayExclude = objectExtract.value("exclude").toArray();
			QStringList exclude;

			for (auto & i : arrayExclude)
			{
				exclude.push_back(i.toString());
			}

			extract.setExclude(exclude);
		}

		library.setExtract(extract);
	}
	//rules
	if (object.contains("rules"))
	{
		library.setRules(praseRules(object.value("rules").toArray()));
	}
	//downloads
	if (object.contains("downloads"))
	{
		auto objectDownloads = object.value("downloads").toObject();
		Downloads downloads;
		//classifiers
		if (objectDownloads.contains("classifiers"))
		{
			QMap<QString, Downloads::Download> classifiers;
			auto objectClassifiers = objectDownloads.value("classifiers").toObject();

			auto keys = objectClassifiers.keys();
			for (auto & i : keys)
			{
				auto objectClassifier = objectClassifiers.value(i).toObject();

				classifiers.insert(i, Downloads::Download{
					objectClassifier.contains("size") ? objectClassifier.value("size").toInt() : 0,
					objectClassifier.contains("sha1") ? objectClassifier.value("sha1").toString() : "",
					objectClassifier.contains("path") ? objectClassifier.value("path").toString() : "",
					objectClassifier.contains("url") ? objectClassifier.value("url").toString() : ""
				});
			}

			downloads.setClassifiers(classifiers);
		}
		//artifact
		if (objectDownloads.contains("artifact"))
		{
			auto objectArtifact = objectDownloads.value("artifact").toObject();
			downloads.setArtifact(Downloads::Download{
				objectArtifact.contains("size") ? objectArtifact.value("size").toInt() : 0,
				objectArtifact.contains("sha1") ? objectArtifact.value("sha1").toString() : "",
				objectArtifact.contains("path") ? objectArtifact.value("path").toString() : "",
				objectArtifact.contains("url") ? objectArtifact.value("url").toString() : ""
			});
		}

		library.setDownloads(downloads);
	}

	return library;
}
