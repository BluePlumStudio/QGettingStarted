#include "QGSForgeVersionInfoListFactory.h"
#include "Util/QGSExceptionVersionNotFound.h"
#include "Util/QGSExceptionInvalidValue.h"
#include "Util/QGSExceptionFileIO.h"
#include "Util/QGSExceptionJsonPraseError.h"

QGSForgeVersionInfoListFactory::QGSForgeVersionInfoListFactory()
{
}

QGSForgeVersionInfoListFactory::~QGSForgeVersionInfoListFactory()
{
}

QGSForgeVersionInfoList QGSForgeVersionInfoListFactory::createForgeVersionInfoList(const QByteArray & jsonData, int offset, int limit)
{
	QGSForgeVersionInfoList ret;

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

inline void QGSForgeVersionInfoListFactory::praseForgeVersionInfoListStd(QJsonObject & jsonObject, int offset, int limit, QGSForgeVersionInfoList & forgeVersionInfoList)
{
	if (!jsonObject.contains("number"))
	{
		throw QGSExceptionJsonPraseError(QJsonParseError(), "\"number\" does not exeist!");
	}

	auto && numberObject{ jsonObject.value("number").toObject() };
	auto && keys{ numberObject.keys() };
	limit = qMin(limit, keys.size());
	for (int i = 0; i < limit; i += offset)
	{
		auto && infoObject{ numberObject.value(keys[i]).toObject() };
		QGSForgeVersionInfo newForgeVersionInfo;
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
		QList<QGSForgeVersionInfo::File> fileList;
		for (auto & j : fileArray)
		{
			auto && fileInfoArray{ j.toArray() };

			fileList.push_back(QGSForgeVersionInfo::File{ fileInfoArray.at(0).toString(),
				fileInfoArray.at(1).toString() ,
				fileInfoArray.at(2).toString() });
		}
		newForgeVersionInfo.setFiles(fileList);

		forgeVersionInfoList.addVersionInfo(newForgeVersionInfo);
	}
}

inline void QGSForgeVersionInfoListFactory::praseForgeVersionInfoListBMCLAPI(QJsonArray & jsonArray, int offset, int limit, QGSForgeVersionInfoList & forgeVersionInfoList)
{
	limit = qMin(limit, jsonArray.size());
	for (int i = 0; i < limit; i += offset)
	{
		auto && infoObject{ jsonArray.at(i).toObject() };
		QGSForgeVersionInfo newForgeVersionInfo;
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
		QList<QGSForgeVersionInfo::File> fileList;
		for (auto & j : fileArray)
		{
			auto && fileObject{ j.toObject() };

			fileList.push_back(QGSForgeVersionInfo::File{ fileObject.value("format").toString(),
				fileObject.value("category").toString() ,
				fileObject.value("hash").toString() ,
				fileObject.value("_id").toString() });
		}
		newForgeVersionInfo.setFiles(fileList);

		forgeVersionInfoList.addVersionInfo(newForgeVersionInfo);
	}
}
