#include "QGSAssetIndexInfoFactory.h"
#include "Util/QGSExceptionVersionNotFound.h"
#include "Util/QGSExceptionInvalidValue.h"
#include "Util/QGSExceptionFileIO.h"
#include "Util/QGSExceptionJsonPraseError.h"

QGSAssetIndexInfoFactory::QGSAssetIndexInfoFactory()
{
}

QGSAssetIndexInfoFactory::~QGSAssetIndexInfoFactory()
{
}

AssetIndexInfo QGSAssetIndexInfoFactory::createAssetIndexInfo(const QByteArray & jsonData)
{
	AssetIndexInfo ret;

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
		ret.addAssetObject(key, AssetObject{ assetInfoObject.value("hash").toString(),assetInfoObject.value("size").toInt() });
	}

	ret.setVirtual(jsonObject.value("virtual").toBool());

	return ret;
}
