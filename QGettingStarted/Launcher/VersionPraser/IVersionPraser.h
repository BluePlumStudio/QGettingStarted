#pragma once

#include <QString>
#include <QJsonDocument>

#include "../../Version/Version.h"

class IVersionPraser 
{
public:
	IVersionPraser(const int minimunLaunchVersion = 0);

	IVersionPraser(const IVersionPraser & right) = default;

	IVersionPraser(IVersionPraser && right) = default;

	IVersionPraser & operator=(const IVersionPraser & right) = default;

	IVersionPraser & operator=(IVersionPraser && right) = default;

	virtual ~IVersionPraser();

	virtual void praseVersion(Version & version, QJsonDocument & jsonDocument)const = 0;
protected:
protected:
	bool praseId(Version & version, QJsonObject & object)const;
	bool praseArguments(Version & version, QJsonObject & object)const;
	bool praseMainClass(Version & version, QJsonObject & object)const;
	bool praseInheritsFrom(Version & version, QJsonObject & object)const;
	bool praseJar(Version & version, QJsonObject & object)const;
	bool praseAssetIndex(Version & version, QJsonObject & object)const;
	bool praseAssets(Version & version, QJsonObject & object)const;
	bool praseLibraries(Version & version, QJsonObject & object)const;
	bool praseDownloads(Version & version, QJsonObject & object)const;
	bool praseLogging(Version & version, QJsonObject & object)const;
	bool praseType(Version & version, QJsonObject & object)const;
	bool praseTime(Version & version, QJsonObject & object)const;
	bool praseReleaseTime(Version & version, QJsonObject & object)const;
	bool praseMinimumLauncherVersion(Version & version, QJsonObject & object)const;
private:
	inline Rules praseRules(QJsonArray & arrayRules)const;
	inline QStringList praseValue(QJsonValue & valueValue)const;
	/**/
	inline Library praseLibrary(QJsonObject & object)const;
protected: 
	int mMinimunLaunchVersion;
};
