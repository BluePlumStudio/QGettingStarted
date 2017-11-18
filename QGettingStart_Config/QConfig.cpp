#include "QConfig.h"


QConfig::QConfig()
{
}


QConfig::~QConfig()
{
}

/**/

bool QConfig::readFile(QString filePath)
{
	QFile file;
	QByteArray data;
	QJsonParseError jsonParseError;
	QJsonDocument jsonDocument;
	QJsonArray jsonArray;

	file.setFileName(filePath);
	if (!file.open(QIODevice::ReadOnly))
	{
		return false;
	}
	data = file.readAll();
	file.close();

	jsonDocument = QJsonDocument::fromJson(data, &jsonParseError);
	if (jsonParseError.error != QJsonParseError::NoError)
	{
		return false;
	}

	if (!jsonDocument.isArray())
	{
		return false;
	}
	jsonArray = jsonDocument.array();

	for (int i = 0; i < jsonArray.size(); i++)
	{
		QSolution solution;
		QJsonObject jsonObject = jsonArray.at(i).toObject();

		solution.loadFromJsonObject(jsonObject);

		mSolutionVector.push_back(solution);
	}

	return true;
}

bool QConfig::writeFile(QString filePath)
{
	QFile file;
	QJsonDocument jsonDocument;
	QJsonArray jsonArray;

	file.setFileName(filePath);
	if (!file.open(QIODevice::Truncate | QIODevice::WriteOnly))
	{
		return false;
	}

	for (int i = 0; i < mSolutionVector.size(); i++)
	{
		mSolutionVector[i].apply();
		jsonArray.push_back(mSolutionVector.at(i).mJsonObject);
	}
	jsonDocument.setArray(jsonArray);
	file.write(jsonDocument.toJson());

	return true;
}

void QConfig::appendSolution(QSolution & solution)
{
	mSolutionVector.push_back(solution);
}

int QConfig::getSolutionSize()
{
	return mSolutionVector.size();
}

QSolution & QConfig::getSolutionRef(int index)
{
	return mSolutionVector[index];
}

QSolution * QConfig::getSolutionPtr(int index)
{
	return &mSolutionVector[index];
}