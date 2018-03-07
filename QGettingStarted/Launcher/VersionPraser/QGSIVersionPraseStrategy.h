#pragma once

#include <QString>
#include <QJsonDocument>

#include "../../Version/Version.h"

class QGSIVersionPraseStrategy 
{
public:
	QGSIVersionPraseStrategy(const int minimunLaunchVersion = 0);

	QGSIVersionPraseStrategy(const QGSIVersionPraseStrategy & right) = default;

	QGSIVersionPraseStrategy(QGSIVersionPraseStrategy && right) = default;

	QGSIVersionPraseStrategy & operator=(const QGSIVersionPraseStrategy & right) = default;

	QGSIVersionPraseStrategy & operator=(QGSIVersionPraseStrategy && right) = default;

	virtual ~QGSIVersionPraseStrategy();

	virtual void praseVersion(Version & version, QJsonDocument & jsonDocument)const = 0;
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
