#include <QJsonObject>
#include <QJsonArray>

#include "QGSGeneralGameVersionPraseStrategy.h"
#include "../../Util/QGSExceptionJsonPraseError.h"

QGSGeneralGameVersionPraseStrategy::QGSGeneralGameVersionPraseStrategy(const int minimunLaunchVersion):QGSIGameVersionPraseStrategy(minimunLaunchVersion)
{

}

QGSGeneralGameVersionPraseStrategy::~QGSGeneralGameVersionPraseStrategy()
{

}

void QGSGeneralGameVersionPraseStrategy::praseVersion(GameVersion & version, QJsonDocument & jsonDocument)const
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

