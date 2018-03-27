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
    bool praseId(QGSGameVersion & version, const QJsonObject & object)const;
    bool praseArguments(QGSGameVersion & version, const QJsonObject & object)const;
    bool praseMainClass(QGSGameVersion & version, const QJsonObject & object)const;
    bool praseInheritsFrom(QGSGameVersion & version, const QJsonObject & object)const;
    bool praseJar(QGSGameVersion & version, const QJsonObject & object)const;
    bool praseAssetIndex(QGSGameVersion & version, const QJsonObject & object)const;
    bool praseAssets(QGSGameVersion & version, const QJsonObject & object)const;
    bool praseLibraries(QGSGameVersion & version, const QJsonObject & object)const;
    bool praseDownloads(QGSGameVersion & version, const QJsonObject & object)const;
    bool praseLogging(QGSGameVersion & version, const QJsonObject & object)const;
    bool praseType(QGSGameVersion & version, const QJsonObject & object)const;
    bool praseTime(QGSGameVersion & version, const QJsonObject & object)const;
    bool praseReleaseTime(QGSGameVersion & version, const QJsonObject & object)const;
    bool praseMinimumLauncherVersion(QGSGameVersion & version, const QJsonObject & object)const;
private:
    inline QGSRules praseRules(const QJsonArray & arrayRules)const;
    inline QStringList praseValue(const QJsonValue & valueValue)const;
	/**/
    inline QGSLibrary praseLibrary(const QJsonObject & object)const;
};
