#include "QGSRules.h"

QGSRules::QGSRule::QGSRule(const QString & action, const QMap<QString, bool> & features, const QString & os, const QString & osVersion)
	:mAction(action), mFeatures(features), mOs(os), mOsVersion(osVersion), mOperatingSystemPtr(&QGSOperatingSystem::getInstance())
{

}

QGSRules::QGSRule::~QGSRule()
{

}

QGSRules::QGSRule & QGSRules::QGSRule::setAction(const QString & action)
{
	mAction = action;
	return *this;
}

QGSRules::QGSRule & QGSRules::QGSRule::setFeatures(const QMap<QString, bool> & features)
{
	mFeatures = features;
	return *this;
}

QGSRules::QGSRule & QGSRules::QGSRule::setOs(const QString & os)
{
	mOs = os;
	return *this;
}

QGSRules::QGSRule & QGSRules::QGSRule::setOsVersion(const QString & osVersion)
{
	mOsVersion = osVersion;
	return *this;
}

QString QGSRules::QGSRule::getAction()const
{
	return mAction;
}

QMap<QString, bool> QGSRules::QGSRule::getFeatures()const
{
	return mFeatures;
}

QString QGSRules::QGSRule::getOs()const
{
	return mOs;
}

QString QGSRules::QGSRule::getOsVersion()const
{
	return mOsVersion;
}

void QGSRules::QGSRule::clear()
{
	mAction = Action::ALLOW;
	mFeatures.clear();
	mOs.clear();
}

/**/

QGSRules::QGSRules()
{

}

QGSRules::QGSRules(const QList<QGSRule> & rules)
{

}

QGSRules::~QGSRules()
{

}

QGSRules & QGSRules::setRules(const QList<QGSRule> & rules)
{
	mRules = rules;
	return *this;
}

QList<QGSRules::QGSRule> QGSRules::getRules()const
{
	return mRules;
}

QGSRules & QGSRules::addRule(const QGSRule & rule)
{
	mRules.push_back(rule);
	return *this;
}

void QGSRules::clear()
{
	mRules.clear();
}
