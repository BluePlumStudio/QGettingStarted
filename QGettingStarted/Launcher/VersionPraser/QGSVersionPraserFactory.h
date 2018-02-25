#pragma once

#include <QSharedPointer>

#include "IVersionPraser.h"

class QGSVersionPraserFactory
{
public:
	QGSVersionPraserFactory();

	QGSVersionPraserFactory(const QGSVersionPraserFactory & right) = delete;

	QGSVersionPraserFactory(QGSVersionPraserFactory && right) = delete;

	QGSVersionPraserFactory & operator=(const QGSVersionPraserFactory & right) = delete;

	QGSVersionPraserFactory & operator=(QGSVersionPraserFactory && right) = delete;

	~QGSVersionPraserFactory();

	IVersionPraser * createVersionPraser(QJsonDocument & jsonDocument)const;

private:
};

