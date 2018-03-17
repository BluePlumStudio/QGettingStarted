#pragma once

#include <QSharedPointer>

#include "QGSIGameVersionPraseStrategy.h"

class QGSGameVersionPraser
{
public:
	QGSGameVersionPraser();

	QGSGameVersionPraser(const QGSGameVersionPraser & right) = delete;

	QGSGameVersionPraser(QGSGameVersionPraser && right) = delete;

	QGSGameVersionPraser & operator=(const QGSGameVersionPraser & right) = delete;

	QGSGameVersionPraser & operator=(QGSGameVersionPraser && right) = delete;

	~QGSGameVersionPraser();

	bool praseVersion(GameVersion & version, QJsonDocument & jsonDocument)const;
private:
};

