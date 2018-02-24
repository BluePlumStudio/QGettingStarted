#pragma once

#include <QString>
#include <QJsonDocument>

#include "../../Version/Version.h"

class IVersionPraseStrategy 
{
public:
	IVersionPraseStrategy(const int minimunLaunchVersion = 0);

	IVersionPraseStrategy(const IVersionPraseStrategy & right) = default;

	IVersionPraseStrategy(IVersionPraseStrategy && right) = default;

	IVersionPraseStrategy & operator=(const IVersionPraseStrategy & right) = default;

	IVersionPraseStrategy & operator=(IVersionPraseStrategy && right) = default;

	virtual ~IVersionPraseStrategy();

	virtual void praseVersion(Version & version, QJsonDocument & jsonDocument)const = 0;
protected: 
	int mMinimunLaunchVersion;
};
