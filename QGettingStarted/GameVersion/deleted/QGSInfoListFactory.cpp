#include "QGSInfoListFactory.h"
#include "Util/QGSExceptionVersionNotFound.h"
#include "Util/QGSExceptionInvalidValue.h"
#include "Util/QGSExceptionFileIO.h"
#include "Util/QGSExceptionJsonPraseError.h"

QGSInfoListFactory::QGSInfoListFactory()
{
}

QGSInfoListFactory::~QGSInfoListFactory()
{
}

GameVersionInfoList QGSInfoListFactory::createGameVersionInfoList(const QByteArray & jsonData)
{
	GameVersionInfoList ret;

	QJsonParseError jsonPraseError;
	QJsonDocument jsonDocument{ QJsonDocument::fromJson(jsonData,&jsonPraseError) };
	if (jsonPraseError.error != QJsonParseError::NoError)
	{
		throw QGSExceptionJsonPraseError(jsonPraseError);
	}
	auto && jsonObject{ jsonDocument.object() };
	//latest
	if (!jsonObject.contains("latest"))
	{
		throw QGSExceptionJsonPraseError(jsonPraseError, "\"latest\" does not exeist!");
	}
	auto && latestObject{ jsonObject.value("latest").toObject() };
	ret.setLatestRelease(latestObject.value("release").toString());
	ret.setLatestSnapshot(latestObject.value("snapshot").toString());
	//versions
	if (!jsonObject.contains("versions"))
	{
		throw QGSExceptionJsonPraseError(jsonPraseError, "\"versions\" does not exeist!");
	}
	auto && versionsArray{ jsonObject.value("versions").toArray() };
	for (auto & i : versionsArray)
	{
		auto && versionObject{ i.toObject() };
		ret.addVersionInfo(GameVersionInfo{ versionObject.value("id").toString(),
			versionObject.value("type").toString() ,
			versionObject.value("time").toString() ,
			versionObject.value("releaseTime").toString() ,
			versionObject.value("url").toString() });
	}

	return ret;
}

ForgeVersionInfoList QGSInfoListFactory::createForgeVersionInfoList(const QByteArray & jsonData, int offset, int limit)
{
	ForgeVersionInfoList ret;

	QJsonParseError jsonPraseError;
	QJsonDocument jsonDocument{ QJsonDocument::fromJson(jsonData,&jsonPraseError) };
	if (jsonPraseError.error != QJsonParseError::NoError)
	{
		throw QGSExceptionJsonPraseError(jsonPraseError);
	}

	if (jsonDocument.isArray())
	{
		praseForgeVersionInfoListBMCLAPI(jsonDocument.array(), offset, limit, ret);
	}
	else
	{
		praseForgeVersionInfoListStd(jsonDocument.object(), offset, limit, ret);
	}

	return ret;
}

LiteLoaderVersionInfoList QGSInfoListFactory::createLiteLoaderVersionInfoList(const QByteArray & jsonData)
{
	LiteLoaderVersionInfoList ret;

	QJsonParseError jsonPraseError;
	QJsonDocument jsonDocument{ QJsonDocument::fromJson(jsonData,&jsonPraseError) };
	if (jsonPraseError.error != QJsonParseError::NoError)
	{
		throw QGSExceptionJsonPraseError(jsonPraseError);
	}

	auto && jsonObject{ jsonDocument.object() };
	if (!jsonObject.contains("versions"))
	{
		throw QGSExceptionJsonPraseError(jsonPraseError, "\"versions\" does not exeist!");
	}

	auto && versionsObject{ jsonObject.value("versions").toObject() };
	auto && keys{ versionsObject.keys() };
	for (auto & i : keys)
	{
		auto && versionInfoObject{ versionsObject.value(i).toObject() };
		LiteLoaderVersionInfo newVersionInfo;

		LiteLoaderVersionReposity reposity;
		auto && reposityObject{ versionInfoObject.value("repo").toObject() };
		reposity.setStream(reposityObject.value("stream").toString());
		reposity.setType(reposityObject.value("type").toString());
		reposity.setUrl(reposityObject.value("url").toString());
		reposity.setClassifier(reposityObject.value("classifier").toString());
		newVersionInfo.setLiteLoaderVersionReposity(reposity);

		QMap<QString, LiteLoaderVersionMeta> snapshotMetaMap;
		auto && snapshotMetaObject{ 
			versionInfoObject.value("snapshots").toObject().value("com.mumfrey:liteloader").toObject() };
		auto && snapshotMetaKeys{ snapshotMetaObject.keys() };
		for (auto & j : snapshotMetaKeys)
		{
			auto && metaObject{ snapshotMetaObject.value(j).toObject() };
			snapshotMetaMap.insert(j, praseLiteLoaderVersionMeta(metaObject));
		}
		newVersionInfo.setLiteLoaderVersionSnapshotMetaMap(snapshotMetaMap);

		QMap<QString, LiteLoaderVersionMeta> artefactMetaMap;
		auto && artefactMetaObject{
			versionInfoObject.value("artefacts").toObject().value("com.mumfrey:liteloader").toObject() };
		auto && artefactMetaKeys{ artefactMetaObject.keys() };
		for (auto & j : artefactMetaKeys)
		{
			auto && metaObject{ artefactMetaObject.value(j).toObject() };
			artefactMetaMap.insert(j, praseLiteLoaderVersionMeta(metaObject));
		}
		newVersionInfo.setLiteLoaderVersionArtefactMetaMap(artefactMetaMap);

		ret.addVersionInfo(i, newVersionInfo);
	}

	return ret;
}

AssetInfoList QGSInfoListFactory::createAssetInfoList(const QByteArray & jsonData)
{
	AssetInfoList ret;

	QJsonParseError jsonPraseError;
	QJsonDocument jsonDocument{ QJsonDocument::fromJson(jsonData,&jsonPraseError) };
	if (jsonPraseError.error != QJsonParseError::NoError)
	{
		throw QGSExceptionJsonPraseError(jsonPraseError);
	}

	auto && jsonObject{ jsonDocument.object() };
	if (!jsonObject.contains("objects"))
	{
		throw QGSExceptionJsonPraseError(jsonPraseError, "\"objects\" does not exeist!");
	}
	
	auto && assetInfoListObject{ jsonObject.value("objects").toObject() };
	auto && keys{ assetInfoListObject.keys() };
	for (auto & key : keys)
	{
		auto && assetInfoObject{ assetInfoListObject.value(key).toObject() };
		ret.addAssetInfo(key, AssetInfo{ assetInfoObject.value("hash").toString(),assetInfoObject.value("size").toInt() });
	}

	ret.setVirtual(jsonObject.value("virtual").toBool());

	return ret;
}

void QGSInfoListFactory::praseForgeVersionInfoListStd(QJsonObject & jsonObject, int offset, int limit, ForgeVersionInfoList & forgeVersionInfoList)
{
	if (!jsonObject.contains("number"))
	{
		throw QGSExceptionJsonPraseError(QJsonParseError(), "\"number\" does not exeist!");
	}

	auto && numberObject{ jsonObject.value("number").toObject() };
	auto && keys{ numberObject.keys() };
	if (limit > keys.size())
	{
		limit = keys.size();
	}
	for (int i = 0; i < limit; i += offset)
	{
		auto && infoObject{ numberObject.value(keys[i]).toObject() };
		ForgeVersionInfo newForgeVersionInfo;
		if (!infoObject.contains("build"))
		{
			throw QGSExceptionJsonPraseError(QJsonParseError(), "\"build\" does not exeist!");
		}
		newForgeVersionInfo.setBranch(infoObject.value("branch").toString());
		newForgeVersionInfo.setBuild(infoObject.value("build").toInt());
		newForgeVersionInfo.setMcversion(infoObject.value("mcversion").toString());
		newForgeVersionInfo.setModified(infoObject.value("modified").toString());
		newForgeVersionInfo.setVersion(infoObject.value("version").toString());
		newForgeVersionInfo.setId(infoObject.value("_id").toString());

		auto && fileArray{ infoObject.value("files").toArray() };
		QList<ForgeVersionInfo::File> fileList;
		for (auto & j : fileArray)
		{
			auto && fileInfoArray{ j.toArray() };
			
			fileList.push_back(ForgeVersionInfo::File{ fileInfoArray.at(0).toString(),
				fileInfoArray.at(1).toString() ,
				fileInfoArray.at(2).toString() });
		}
		newForgeVersionInfo.setFiles(fileList);

		forgeVersionInfoList.addVersionInfo(newForgeVersionInfo);
	}
}

void QGSInfoListFactory::praseForgeVersionInfoListBMCLAPI(QJsonArray & jsonArray, int offset, int limit, ForgeVersionInfoList & forgeVersionInfoList)
{
	if (limit > jsonArray.size())
	{
		limit = jsonArray.size();
	}
	for (int i = 0; i < limit; i += offset)
	{
		auto && infoObject{ jsonArray.at(i).toObject() };
		ForgeVersionInfo newForgeVersionInfo;
		if (!infoObject.contains("build"))
		{
			throw QGSExceptionJsonPraseError(QJsonParseError(), "\"build\" does not exeist!");
		}
		newForgeVersionInfo.setBranch(infoObject.value("branch").toString());
		newForgeVersionInfo.setBuild(infoObject.value("build").toInt());
		newForgeVersionInfo.setMcversion(infoObject.value("mcversion").toString());
		newForgeVersionInfo.setModified(infoObject.value("modified").toString());
		newForgeVersionInfo.setVersion(infoObject.value("version").toString());
		newForgeVersionInfo.setId(infoObject.value("_id").toString());

		auto && fileArray{ infoObject.value("files").toArray() };
		QList<ForgeVersionInfo::File> fileList;
		for (auto & j : fileArray)
		{
			auto && fileObject{ j.toObject() };

			fileList.push_back(ForgeVersionInfo::File{ fileObject.value("format").toString(),
				fileObject.value("category").toString() ,
				fileObject.value("hash").toString() ,
				fileObject.value("_id").toString() });
		}
		newForgeVersionInfo.setFiles(fileList);

		forgeVersionInfoList.addVersionInfo(newForgeVersionInfo);
	}
}

inline Library QGSInfoListFactory::praseLiteLoaderVersionMetaLibrary(QJsonObject & object) const
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
	//url
	if (object.contains("url"))
	{
		library.serUrl(object.value("url").toString());
	}

	return library;
}

inline LiteLoaderVersionMeta QGSInfoListFactory::praseLiteLoaderVersionMeta(QJsonObject & object)
{
	LiteLoaderVersionMeta ret;

	ret.setTweakClass(object.value("tweakClass").toString());
	ret.setSrcJar(object.value("srcJar").toString());
	ret.setMcpJar(object.value("mcpJar").toString());
	ret.setStream(object.value("stream").toString());
	ret.setFile(object.value("file").toString());
	ret.setVersion(object.value("version").toString());
	ret.setBuild(object.value("build").toString());
	ret.setMd5(object.value("md5").toString());
	ret.setTimestamp(object.value("timestamp").toString());
	ret.setLastSuccessfulBuild(object.value("lastSuccessfulBuild").toInt());
	QList<Library> libraryList;
	auto libraryArray = object.value("libraries").toArray();
	for (auto & i : libraryArray)
	{
		libraryList.push_back(praseLiteLoaderVersionMetaLibrary(i.toObject()));
	}
	ret.setLibraries(libraryList);

	return ret;
}
