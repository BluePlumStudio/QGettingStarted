#include <QJsonObject>

#include "QGSVersionPraserFactory.h"
#include "GeneralVersionPraser.h"

QGSVersionPraserFactory::QGSVersionPraserFactory()
{

}

QGSVersionPraserFactory::~QGSVersionPraserFactory()
{
}

IVersionPraser * QGSVersionPraserFactory::createVersionPraser(QJsonDocument & jsonDocument)const
{
	QJsonObject object = jsonDocument.object();
	int minimumLauncherVersion =
		object.contains("minimumLauncherVersion") ?
		object.value("minimumLauncherVersion").toInt() : 0;
	
	return new GeneralVersionPraser(0);
}