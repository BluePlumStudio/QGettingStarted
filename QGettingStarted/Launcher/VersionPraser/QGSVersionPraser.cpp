#include <QJsonObject>

#include "QGSVersionPraser.h"
#include "QGSGeneralVersionPraseStrategy.h"

QGSVersionPraser::QGSVersionPraser()
{

}

QGSVersionPraser::~QGSVersionPraser()
{
}

bool QGSVersionPraser::praseVersion(Version & version, QJsonDocument & jsonDocument) const
{
	QJsonObject object = jsonDocument.object();
	int minimumLauncherVersion =
		object.contains("minimumLauncherVersion") ?
		object.value("minimumLauncherVersion").toInt() : 0;

	QSharedPointer<QGSIVersionPraseStrategy>versionPraseStrategy{ new QGSGeneralVersionPraseStrategy };

	versionPraseStrategy->praseVersion(version, jsonDocument);

	return true;
}