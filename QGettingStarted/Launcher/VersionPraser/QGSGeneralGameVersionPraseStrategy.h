#pragma once

#include "QGSIGameVersionPraseStrategy.h"

class QGSGeneralGameVersionPraseStrategy :public QGSIGameVersionPraseStrategy
{
public:
	QGSGeneralGameVersionPraseStrategy(const int minimunLaunchVersion = 0);

	QGSGeneralGameVersionPraseStrategy(const QGSGeneralGameVersionPraseStrategy & right) = default;

	QGSGeneralGameVersionPraseStrategy(QGSGeneralGameVersionPraseStrategy && right) = default;

	QGSGeneralGameVersionPraseStrategy & operator=(const QGSGeneralGameVersionPraseStrategy & right) = default;

	QGSGeneralGameVersionPraseStrategy & operator=(QGSGeneralGameVersionPraseStrategy && right) = default;

	virtual ~QGSGeneralGameVersionPraseStrategy();

	virtual void praseVersion(QGSGameVersion & version, QJsonDocument & jsonDocument)const override;
protected:
	bool praseId(QGSGameVersion & version, QJsonObject & object)const;
	bool praseArguments(QGSGameVersion & version, QJsonObject & object)const;
	bool praseMainClass(QGSGameVersion & version, QJsonObject & object)const;
	bool praseInheritsFrom(QGSGameVersion & version, QJsonObject & object)const;
	bool praseJar(QGSGameVersion & version, QJsonObject & object)const;
	bool praseAssetIndex(QGSGameVersion & version, QJsonObject & object)const;
	bool praseAssets(QGSGameVersion & version, QJsonObject & object)const;
	bool praseLibraries(QGSGameVersion & version, QJsonObject & object)const;
	bool praseDownloads(QGSGameVersion & version, QJsonObject & object)const;
	bool praseLogging(QGSGameVersion & version, QJsonObject & object)const;
	bool praseType(QGSGameVersion & version, QJsonObject & object)const;
	bool praseTime(QGSGameVersion & version, QJsonObject & object)const;
	bool praseReleaseTime(QGSGameVersion & version, QJsonObject & object)const;
	bool praseMinimumLauncherVersion(QGSGameVersion & version, QJsonObject & object)const;
private:
	inline QGSRules praseRules(QJsonArray & arrayRules)const;
	inline QStringList praseValue(QJsonValue & valueValue)const;
	/**/
	inline QGSLibrary praseLibrary(QJsonObject & object)const;
};
