#pragma once

#include <QString>
#include <QJsonDocument>

#include "../GameVersion/GameVersion.h"

class QGSIGameVersionPraseStrategy 
{
public:
	QGSIGameVersionPraseStrategy(const int minimunLaunchVersion = 0);

	QGSIGameVersionPraseStrategy(const QGSIGameVersionPraseStrategy & right) = default;

	QGSIGameVersionPraseStrategy(QGSIGameVersionPraseStrategy && right) = default;

	QGSIGameVersionPraseStrategy & operator=(const QGSIGameVersionPraseStrategy & right) = default;

	QGSIGameVersionPraseStrategy & operator=(QGSIGameVersionPraseStrategy && right) = default;

	virtual ~QGSIGameVersionPraseStrategy();

	virtual void praseVersion(GameVersion & version, QJsonDocument & jsonDocument)const = 0;
protected:
	bool praseId(GameVersion & version, QJsonObject & object)const;
	bool praseArguments(GameVersion & version, QJsonObject & object)const;
	bool praseMainClass(GameVersion & version, QJsonObject & object)const;
	bool praseInheritsFrom(GameVersion & version, QJsonObject & object)const;
	bool praseJar(GameVersion & version, QJsonObject & object)const;
	bool praseAssetIndex(GameVersion & version, QJsonObject & object)const;
	bool praseAssets(GameVersion & version, QJsonObject & object)const;
	bool praseLibraries(GameVersion & version, QJsonObject & object)const;
	bool praseDownloads(GameVersion & version, QJsonObject & object)const;
	bool praseLogging(GameVersion & version, QJsonObject & object)const;
	bool praseType(GameVersion & version, QJsonObject & object)const;
	bool praseTime(GameVersion & version, QJsonObject & object)const;
	bool praseReleaseTime(GameVersion & version, QJsonObject & object)const;
	bool praseMinimumLauncherVersion(GameVersion & version, QJsonObject & object)const;
private:
	inline Rules praseRules(QJsonArray & arrayRules)const;
	inline QStringList praseValue(QJsonValue & valueValue)const;
	/**/
	inline Library praseLibrary(QJsonObject & object)const;
protected: 
	int mMinimunLaunchVersion;
};
