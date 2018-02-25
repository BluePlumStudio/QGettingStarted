#include <QJsonObject>
#include <QJsonArray>

#include "GeneralVersionPraser.h"
#include "../../Util/QGSExceptionJsonPraseError.h"

GeneralVersionPraser::GeneralVersionPraser(const int minimunLaunchVersion):IVersionPraser(minimunLaunchVersion)
{

}

GeneralVersionPraser::~GeneralVersionPraser()
{

}

void GeneralVersionPraser::praseVersion(Version & version, QJsonDocument & jsonDocument)const
{
	auto object = jsonDocument.object();
	version.clear();

	praseId(version, object);
	praseArguments(version, object);
	praseMainClass(version, object);
	praseInheritsFrom(version, object);
	praseJar(version, object);
	praseAssetIndex(version, object);
	praseAssets(version, object);
	praseLibraries(version, object);
	praseDownloads(version, object);
	praseLogging(version, object);
	praseType(version, object);
	praseTime(version, object);
	praseReleaseTime(version, object);
	praseMinimumLauncherVersion(version, object);

	return;
}

