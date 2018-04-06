#include "QGSLiteLoaderVersionInfoListFactory.h"
#include "../Util/QGSExceptionVersionNotFound.h"
#include "../Util/QGSExceptionInvalidValue.h"
#include "../Util/QGSExceptionIO.h"
#include "../Util/QGSExceptionJsonPraseError.h"

QGSLiteLoaderVersionInfoListFactory::QGSLiteLoaderVersionInfoListFactory(QObject * parent) :QObject(parent)
{
}

QGSLiteLoaderVersionInfoListFactory::~QGSLiteLoaderVersionInfoListFactory()
{
}

QGSLiteLoaderVersionInfoList QGSLiteLoaderVersionInfoListFactory::createLiteLoaderVersionInfoList(const QByteArray & jsonData)
{
	QGSLiteLoaderVersionInfoList ret;

	QJsonParseError jsonPraseError;
	QJsonDocument jsonDocument(QJsonDocument::fromJson(jsonData,&jsonPraseError));
	if (jsonPraseError.error != QJsonParseError::NoError)
	{
		throw QGSExceptionJsonPraseError(jsonPraseError);
	}

	auto && jsonObject(jsonDocument.object());
	if (!jsonObject.contains("versions"))
	{
		throw QGSExceptionJsonPraseError(jsonPraseError, "\"versions\" does not exeist!");
	}

	auto && versionsObject(jsonObject.value("versions").toObject());
	auto && keys(versionsObject.keys());
	for (auto & i : keys)
	{
		auto && versionInfoObject(versionsObject.value(i).toObject());
		QGSLiteLoaderVersionInfo newVersionInfo;

		QGSLiteLoaderVersionReposity reposity;
		auto && reposityObject(versionInfoObject.value("repo").toObject());
		reposity.setStream(reposityObject.value("stream").toString());
		reposity.setType(reposityObject.value("type").toString());
		reposity.setUrl(reposityObject.value("url").toString());
		reposity.setClassifier(reposityObject.value("classifier").toString());
		newVersionInfo.setLiteLoaderVersionReposity(reposity);

		QMap<QString, QGSLiteLoaderVersionMeta> snapshotMetaMap;
		auto && snapshotMetaObject(versionInfoObject.value("snapshots").toObject().value("com.mumfrey:liteloader").toObject());
		auto && snapshotMetaKeys(snapshotMetaObject.keys());
		for (auto & j : snapshotMetaKeys)
		{
			auto && metaObject(snapshotMetaObject.value(j).toObject());
			snapshotMetaMap.insert(j, praseLiteLoaderVersionMeta(metaObject));
		}
		newVersionInfo.setLiteLoaderVersionSnapshotMetaMap(snapshotMetaMap);

		QMap<QString, QGSLiteLoaderVersionMeta> artefactMetaMap;
		auto && artefactMetaObject(versionInfoObject.value("artefacts").toObject().value("com.mumfrey:liteloader").toObject());
		auto && artefactMetaKeys(artefactMetaObject.keys());
		for (auto & j : artefactMetaKeys)
		{
			auto && metaObject(artefactMetaObject.value(j).toObject());
			artefactMetaMap.insert(j, praseLiteLoaderVersionMeta(metaObject));
		}
		newVersionInfo.setLiteLoaderVersionArtefactMetaMap(artefactMetaMap);

		ret.addVersionInfo(i, newVersionInfo);
	}

	return ret;
}

inline QGSLibrary QGSLiteLoaderVersionInfoListFactory::praseLiteLoaderVersionMetaLibrary(const QJsonObject & object) const
{
	QGSLibrary library;

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

inline QGSLiteLoaderVersionMeta QGSLiteLoaderVersionInfoListFactory::praseLiteLoaderVersionMeta(const QJsonObject & object)
{
	QGSLiteLoaderVersionMeta ret;

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
	QList<QGSLibrary> libraryList;
    const auto libraryArray = object.value("libraries").toArray();
    for (const auto & i : libraryArray)
	{
		libraryList.push_back(praseLiteLoaderVersionMetaLibrary(i.toObject()));
	}
	ret.setLibraries(libraryList);

	return ret;
}
