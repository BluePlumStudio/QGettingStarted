#pragma once

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonValue>
#include <QString>
#include <QFile>
#include <QVector>
#include <QPair>

#include "QSolution.h"

class QConfig
{
public:
	QConfig();
	virtual ~QConfig();
public:
	bool readFile(QString filePath);

	bool writeFile(QString filePath);

	void appendSolution(QSolution & solution);

	int getSolutionSize();

	QSolution & getSolutionRef(int index);

	QSolution * getSolutionPtr(int index);
private:
	QVector<QSolution> mSolutionVector;
};

