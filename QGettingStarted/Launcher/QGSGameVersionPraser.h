#pragma once

#include <QObject>

#include "QGSIGameVersionPraseStrategy.h"

class QGSGameVersionPraser :public QObject
{
	Q_OBJECT

public:
	QGSGameVersionPraser(QObject * parent = nullptr);

	QGSGameVersionPraser(const QGSGameVersionPraser & right) = delete;

	QGSGameVersionPraser(QGSGameVersionPraser && right) = delete;

	QGSGameVersionPraser & operator=(const QGSGameVersionPraser & right) = delete;

	QGSGameVersionPraser & operator=(QGSGameVersionPraser && right) = delete;

	virtual ~QGSGameVersionPraser();

	bool praseVersion(QGSGameVersion & version, QJsonDocument & jsonDocument)const;
private:
};

