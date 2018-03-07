#include <QJsonObject>
#include <QJsonArray>

#include "QGSIVersionPraseStrategy.h"

QGSIVersionPraseStrategy::QGSIVersionPraseStrategy(const int minimunLaunchVersion) :mMinimunLaunchVersion(minimunLaunchVersion)
{

}

QGSIVersionPraseStrategy::~QGSIVersionPraseStrategy()
{

}


bool QGSIVersionPraseStrategy::praseId(Version & version, QJsonObject & object)const
{
	if (!object.contains("id"))
	{
		return false;
	}

	version.setId(object.value("id").toString());
	return true;
}

bool QGSIVersionPraseStrategy::praseArguments(Version & version, QJsonObject & object)const
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
		auto & argumentObject = object.value("arguments").toObject();
		if (!argumentObject.contains("game") || !argumentObject.contains("jvm"))
		{
			return false;
		}

		QList<Arguments::Argument> jvmList;
		QList<Arguments::Argument> gameList;
		auto gameArray = argumentObject.value("game").toArray();
		auto JvmArray = argumentObject.value("jvm").toArray();
		if (gameArray.size() <= 0 || JvmArray.size() <= 0)
		{
			return false;
		}
		for (auto & i : gameArray)
		{
			if (i.isString())
			{
				gameList.push_back(Arguments::Argument{ i.toString() });
			}
			else if (i.isObject())
			{
				auto gameObject = i.toObject();
				//rules
				Rules rules;
				if (gameObject.contains("rules"))
				{
					rules = praseRules(gameObject.value("rules").toArray());
				}
				//value
				QStringList value;
				if (gameObject.contains("value"))
				{
					value = praseValue(gameObject.value("value"));
				}
				gameList.push_back(Arguments::Argument{ value,rules });
			}
		}
		for (auto & i : JvmArray)
		{
			if (i.isString())
			{
				jvmList.push_back(Arguments::Argument{ i.toString() });
			}
			else if (i.isObject())
			{
				auto gameObject = i.toObject();
				//rules
				Rules rules;
				if (gameObject.contains("rules"))
				{
					rules = praseRules(gameObject.value("rules").toArray());
				}
				//value
				QStringList value;
				if (gameObject.contains("value"))
				{
					value = praseValue(gameObject.value("value"));
				}
				jvmList.push_back(Arguments::Argument{ value,rules });
			}
		}

		version.setArguments(Arguments{ jvmList,gameList });
	}

	return true;
}

bool QGSIVersionPraseStrategy::praseMainClass(Version & version, QJsonObject & object)const
{
	if (!object.contains("mainClass"))
	{
		return false;
	}

	version.setMainClass(object.value("mainClass").toString());
	return true;
}

bool QGSIVersionPraseStrategy::praseInheritsFrom(Version & version, QJsonObject & object)const
{
	if (!object.contains("inheritsFrom"))
	{
		return false;
	}

	version.setInheritsFrom(object.value("inheritsFrom").toString());
	return true;
}

bool QGSIVersionPraseStrategy::praseJar(Version & version, QJsonObject & object)const
{
	if (!object.contains("jar"))
	{
		return false;
	}

	version.setJar(object.value("jar").toString());
	return true;
}

bool QGSIVersionPraseStrategy::praseAssetIndex(Version & version, QJsonObject & object)const
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

bool QGSIVersionPraseStrategy::praseAssets(Version & version, QJsonObject & object)const
{
	if (!object.contains("assets"))
	{
		return false;
	}

	version.setAssets(object.value("assets").toString());
	return true;
}

bool QGSIVersionPraseStrategy::praseLibraries(Version & version, QJsonObject & object)const
{
	if (!object.contains("libraries"))
	{
		return false;
	}

	QList<Library> libraryList;
	auto libraryArray = object.value("libraries").toArray();
	for (auto & i : libraryArray)
	{
		libraryList.push_back(praseLibrary(i.toObject()));
	}

	version.setLibraries(libraryList);
	return true;
}

bool QGSIVersionPraseStrategy::praseDownloads(Version & version, QJsonObject & object)const
{
	if (!object.contains("downloads"))
	{
		return false;
	}

	QMap<QString, Downloads::Download> downloadMap;
	auto downloadsObject = object.value("downloads").toObject();
	auto keys = downloadsObject.keys();
	for (auto & i : keys)
	{
		auto downloadObject = downloadsObject.value(i).toObject();

		downloadMap.insert(
			i,
			Downloads::Download{
			downloadObject.contains("size") ? downloadObject.value("size").toInt() : 0,
			downloadObject.contains("sha1") ? downloadObject.value("sha1").toString() : "",
			downloadObject.contains("path") ? downloadObject.value("path").toString() : "",
			downloadObject.contains("url") ? downloadObject.value("url").toString() : ""
		});
	}

	return true;
}

bool QGSIVersionPraseStrategy::praseLogging(Version & version, QJsonObject & object)const
{
	if (!object.contains("logging"))
	{
		return false;
	}

	auto loggingObject = object.value("logging").toObject();
	QMap<QString, Logging> loggingMap;

	auto keys = loggingObject.keys();
	for (auto & i : keys)
	{
		Logging logging;
		auto downloadTypeObject = loggingObject.value(i).toObject();

		if (downloadTypeObject.contains("file"))
		{
			auto fileObject = downloadTypeObject.value("file").toObject();
			logging.setFile(Logging::File{
				fileObject.contains("size") ? fileObject.value("size").toInt() : 0,
				fileObject.contains("sha1") ? fileObject.value("sha1").toString() : "",
				fileObject.contains("path") ? fileObject.value("path").toString() : "",
				fileObject.contains("url") ? fileObject.value("url").toString() : "",
				fileObject.contains("id") ? fileObject.value("id").toString() : ""
			});
		}
		logging.setArgument(downloadTypeObject.contains("argument") ? downloadTypeObject.value("argument").toString() : "");
		logging.setType(downloadTypeObject.contains("type") ? downloadTypeObject.value("type").toString() : "");

		loggingMap.insert(i, logging);
	}

	version.setLogging(loggingMap);
	return true;
}

bool QGSIVersionPraseStrategy::praseType(Version & version, QJsonObject & object)const
{
	if (!object.contains("type"))
	{
		return false;
	}

	version.setType(object.value("type").toString());
	return true;
}

bool QGSIVersionPraseStrategy::praseTime(Version & version, QJsonObject & object)const
{
	if (!object.contains("time"))
	{
		return false;
	}

	version.setTime(object.value("time").toString());
	return true;
}

bool QGSIVersionPraseStrategy::praseReleaseTime(Version & version, QJsonObject & object)const
{
	if (!object.contains("releaseTime"))
	{
		return false;
	}

	version.setReleaseTime(object.value("releaseTime").toString());
	return true;
}

bool QGSIVersionPraseStrategy::praseMinimumLauncherVersion(Version & version, QJsonObject & object)const
{
	if (!object.contains("minimumLauncherVersion"))
	{
		return false;
	}

	version.setMinimumLauncherVersion(object.value("minimumLauncherVersion").toInt());
	return true;
}
/**/
Rules QGSIVersionPraseStrategy::praseRules(QJsonArray & arrayRules)const
{
	Rules rules;

	for (auto & i : arrayRules)
	{
		auto ruleObject = i.toObject();

		auto action{ ruleObject.contains("action") ? ruleObject.value("action").toString() : Action::ALLOW };
		QMap<QString, bool> featureMap;
		QString os{ OS::UNKNOWN };
		QString osVersion;
		if (ruleObject.contains("os"))
		{
			auto objectOs = ruleObject.value("os").toObject();
			os = objectOs.contains("name") ? objectOs.value("name").toString() : OS::UNKNOWN;
			osVersion = objectOs.contains("version") ? objectOs.value("version").toString() : "";
		}
		if (ruleObject.contains("features"))
		{
			auto objectFeatures = ruleObject.value("features").toObject();

			auto keys = objectFeatures.keys();
			for (auto & k : keys)
			{
				featureMap.insert(k, objectFeatures.value(k).toBool());
			}
		}
		rules.addRule(Rules::Rule{ action,featureMap,os,osVersion });
	}

	return rules;
}

QStringList QGSIVersionPraseStrategy::praseValue(QJsonValue & valueValue)const
{
	QStringList value;

	if (valueValue.isString())
	{
		value = QStringList(valueValue.toString());
	}
	else if (valueValue.isArray())
	{
		auto valueArray = valueValue.toArray();
		for (auto & j : valueArray)
		{
			value.push_back(j.toString());
		}
	}

	return value;
}
/**/
Library QGSIVersionPraseStrategy::praseLibrary(QJsonObject & object)const
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
		auto NativesObject = object.value("natives").toObject();
		QMap<QString, QString> nativesMap;

		auto keys = NativesObject.keys();
		for (auto & i : keys)
		{
			nativesMap.insert(i, NativesObject.value(i).toString());
		}

		library.setNatives(nativesMap);
		library.setNative(true);
	}
	//extract
	if (object.contains("extract"))
	{
		auto extractObject = object.value("extract").toObject();
		Extract extract;

		if (extractObject.contains("exclude"))
		{
			auto arrayExclude = extractObject.value("exclude").toArray();
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
		auto downloadsObject = object.value("downloads").toObject();
		Downloads downloads;
		//classifiers
		if (downloadsObject.contains("classifiers"))
		{
			QMap<QString, Downloads::Download> classifiers;
			auto classifiersObject = downloadsObject.value("classifiers").toObject();

			auto keys = classifiersObject.keys();
			for (auto & i : keys)
			{
				auto objectClassifier = classifiersObject.value(i).toObject();

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
		if (downloadsObject.contains("artifact"))
		{
			auto artifactObject = downloadsObject.value("artifact").toObject();
			downloads.setArtifact(Downloads::Download{
				artifactObject.contains("size") ? artifactObject.value("size").toInt() : 0,
				artifactObject.contains("sha1") ? artifactObject.value("sha1").toString() : "",
				artifactObject.contains("path") ? artifactObject.value("path").toString() : "",
				artifactObject.contains("url") ? artifactObject.value("url").toString() : ""
			});
		}

		library.setDownloads(downloads);
	}

	return library;
}
