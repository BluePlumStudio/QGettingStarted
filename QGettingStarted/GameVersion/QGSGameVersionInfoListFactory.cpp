#include "QGSGameVersionInfoListFactory.h"
#include "../Util/QGSExceptionVersionNotFound.h"
#include "../Util/QGSExceptionInvalidValue.h"
#include "../Util/QGSExceptionIO.h"
#include "../Util/QGSExceptionJsonPraseError.h"

QGSGameVersionInfoListFactory::QGSGameVersionInfoListFactory(QObject * parent) :QObject(parent)
{
}

QGSGameVersionInfoListFactory::~QGSGameVersionInfoListFactory()
{
}

QGSGameVersionInfoList QGSGameVersionInfoListFactory::createGameVersionInfoList(const QByteArray & jsonData)
{
	QGSGameVersionInfoList ret;

	QJsonParseError jsonPraseError;
	QJsonDocument jsonDocument(QJsonDocument::fromJson(jsonData,&jsonPraseError));
	if (jsonPraseError.error != QJsonParseError::NoError)
	{
		throw QGSExceptionJsonPraseError(jsonPraseError);
	}
	auto && jsonObject(jsonDocument.object());
	//latest
	if (!jsonObject.contains("latest"))
	{
		throw QGSExceptionJsonPraseError(jsonPraseError, "\"latest\" does not exeist!");
	}
	auto && latestObject(jsonObject.value("latest").toObject());
	ret.setLatestRelease(latestObject.value("release").toString());
	ret.setLatestSnapshot(latestObject.value("snapshot").toString());
	//versions
	if (!jsonObject.contains("versions"))
	{
		throw QGSExceptionJsonPraseError(jsonPraseError, "\"versions\" does not exeist!");
	}
	auto && versionsArray(jsonObject.value("versions").toArray());
    for (const auto & i : versionsArray)
	{
		auto && versionObject(i.toObject());
		ret.addVersionInfo(QGSGameVersionInfo(versionObject.value("id").toString(),
			versionObject.value("type").toString() ,
			versionObject.value("time").toString() ,
			versionObject.value("releaseTime").toString() ,
			versionObject.value("url").toString()));
	}

	return ret;
}
