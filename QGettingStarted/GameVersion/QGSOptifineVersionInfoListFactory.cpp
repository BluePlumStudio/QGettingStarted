#include "QGSOptifineVersionInfoListFactory.h"
#include "Util/QGSExceptionVersionNotFound.h"
#include "Util/QGSExceptionInvalidValue.h"
#include "Util/QGSExceptionFileIO.h"
#include "Util/QGSExceptionJsonPraseError.h"

QGSOptifineVersionInfoListFactory::QGSOptifineVersionInfoListFactory()
{
}

QGSOptifineVersionInfoListFactory::~QGSOptifineVersionInfoListFactory()
{
}

QGSOptifineVersionInfoList QGSOptifineVersionInfoListFactory::createOptifineVersionInfoList(const QByteArray & jsonData)
{
	QGSOptifineVersionInfoList ret;

	QJsonParseError jsonPraseError;
	QJsonDocument jsonDocument{ QJsonDocument::fromJson(jsonData,&jsonPraseError) };
	if (jsonPraseError.error != QJsonParseError::NoError)
	{
		throw QGSExceptionJsonPraseError(jsonPraseError);
	}

    const auto && jsonArray{ jsonDocument.array() };
    for (const auto & jsonObject : jsonArray)
	{
		auto && versionInfoObject{ jsonObject.toObject() };
		ret.addVersionInfo(QGSOptifineVersionInfo{ versionInfoObject.value("_id").toString(),
			versionInfoObject.value("mcversion").toString(),
			versionInfoObject.value("type").toString(),
			versionInfoObject.value("patch").toString(),
			versionInfoObject.value("filename").toString() });
	}

	return ret;
}
