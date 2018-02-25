#pragma once

#include "IVersionPraser.h"

class GeneralVersionPraser :public IVersionPraser
{
public:
	GeneralVersionPraser(const int minimunLaunchVersion = 0);

	GeneralVersionPraser(const GeneralVersionPraser & right) = default;

	GeneralVersionPraser(GeneralVersionPraser && right) = default;

	GeneralVersionPraser & operator=(const GeneralVersionPraser & right) = default;

	GeneralVersionPraser & operator=(GeneralVersionPraser && right) = default;

	virtual ~GeneralVersionPraser();

	virtual void praseVersion(Version & version, QJsonDocument & jsonDocument)const override;

};
