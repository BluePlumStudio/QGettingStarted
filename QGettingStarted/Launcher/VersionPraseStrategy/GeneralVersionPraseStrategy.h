#pragma once

#include "IVersionPraseStrategy.h"

class GeneralVersionPraseStrategy :public IVersionPraseStrategy
{
public:
	GeneralVersionPraseStrategy(const int minimunLaunchVersion = 0);

	GeneralVersionPraseStrategy(const GeneralVersionPraseStrategy & right) = default;

	GeneralVersionPraseStrategy(GeneralVersionPraseStrategy && right) = default;

	GeneralVersionPraseStrategy & operator=(const GeneralVersionPraseStrategy & right) = default;

	GeneralVersionPraseStrategy & operator=(GeneralVersionPraseStrategy && right) = default;

	virtual ~GeneralVersionPraseStrategy();

	virtual void praseVersion(Version & version, QJsonDocument & jsonDocument)const override;
private:
	inline bool praseId(Version & version, QJsonObject & object)const;
	inline bool praseArguments(Version & version, QJsonObject & object)const;
	inline bool praseMainClass(Version & version, QJsonObject & object)const;
	inline bool praseInheritsFrom(Version & version, QJsonObject & object)const;
	inline bool praseJar(Version & version, QJsonObject & object)const;
	inline bool praseAssetIndex(Version & version, QJsonObject & object)const;
	inline bool praseAssets(Version & version, QJsonObject & object)const;
	inline bool praseLibraries(Version & version, QJsonObject & object)const;
	inline bool praseDownloads(Version & version, QJsonObject & object)const;
	inline bool praseLogging(Version & version, QJsonObject & object)const;
	inline bool praseType(Version & version, QJsonObject & object)const;
	inline bool praseTime(Version & version, QJsonObject & object)const;
	inline bool praseReleaseTime(Version & version, QJsonObject & object)const;
	inline bool praseMinimumLauncherVersion(Version & version, QJsonObject & object)const;
	/**/
	inline Rules praseRules(QJsonArray & arrayRules)const;
	inline QStringList praseValue(QJsonValue & valueValue)const;
	/**/
	inline Library praseLibrary(QJsonObject & object)const;
};
