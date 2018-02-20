#pragma once

#include <QList>
#include <QString>
#include <QMap>

#include "../Util/OperatingSystem.h"

class Rules 
{
public:
	class Rule
	{
	public:
		enum class Action
		{
			ALLOW,
			DISALLOW
		};
	public:
		Rule():mOperatingSystem(OperatingSystem::getInstance())
		{
		}
		~Rule()
		{
		}
	private:
		Action mAction;
		QMap<QString, bool> mFeatures;
		OperatingSystem & mOperatingSystem;
	};

private: 
	QList<Rule> mRules;
};
