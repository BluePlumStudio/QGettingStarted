#pragma once

#include <QList>
#include <QString>
#include <QMap>

#include "../Util/QGSOperatingSystem.h"

namespace Action
{
	const QString ALLOW{ "allow" };
	const QString DISALLOW{ "disallow" };
}

class QGSRules 
{
public:
	class Rule
	{
	public:
		Rule(const QString & action = Action::ALLOW, const QMap<QString, bool> & features = QMap<QString, bool>(), const QString & os = OS::UNKNOWN, const QString & osVersion = "")
			:mAction(action), mFeatures(features), mOs(os), mOsVersion(osVersion), mOperatingSystem(QGSOperatingSystem::getInstance())
		{

		}

		Rule(const Rule & right) = default;

		Rule(Rule && right) = default;

		Rule & operator=(const Rule & right) = default;

		Rule & operator=(Rule && right) = default;

		~Rule()
		{

		}

		Rule & setAction(const QString & action)
		{
			mAction = action;
			return *this;
		}

		Rule & setFeatures(const QMap<QString, bool> & features)
		{
			mFeatures = features;
			return *this;
		}

		Rule & setOs(const QString & os)
		{
			mOs = os;
		}

		Rule & setOsVersion(const QString & osVersion)
		{
			mOsVersion = osVersion;
		}

		QString getAction()const
		{
			return mAction;
		}

		QMap<QString, bool> getFeatures()const
		{
			return mFeatures;
		}

		QString getOs()const
		{
			return mOs;
		}

		QString getOsVersion()const
		{
			return mOsVersion;
		}

		void clear()
		{
			mAction = Action::ALLOW;
			mFeatures.clear();
			mOs.clear();
		}
	private:
		QString mAction;
		QMap<QString, bool> mFeatures;
		QString mOs;
		QString mOsVersion;
		QGSOperatingSystem & mOperatingSystem;
	};
public:
	QGSRules();

	QGSRules(const QList<Rule> & rules);

	QGSRules(const QGSRules & right) = default;

	QGSRules(QGSRules && right) = default;

	QGSRules & operator=(const QGSRules & right) = default;

	QGSRules & operator=(QGSRules && right) = default;

	~QGSRules();

	QGSRules & setRules(const QList<Rule> & rules);

	QList<Rule> getRules()const;

	QGSRules & addRule(const Rule & rule);

	void clear();
private: 
	QList<Rule> mRules;
};
