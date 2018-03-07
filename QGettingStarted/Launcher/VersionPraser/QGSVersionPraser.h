#pragma once

#include <QSharedPointer>

#include "QGSIVersionPraseStrategy.h"

class QGSVersionPraser
{
public:
	QGSVersionPraser();

	QGSVersionPraser(const QGSVersionPraser & right) = delete;

	QGSVersionPraser(QGSVersionPraser && right) = delete;

	QGSVersionPraser & operator=(const QGSVersionPraser & right) = delete;

	QGSVersionPraser & operator=(QGSVersionPraser && right) = delete;

	~QGSVersionPraser();

	bool praseVersion(Version & version, QJsonDocument & jsonDocument)const;
private:
};

