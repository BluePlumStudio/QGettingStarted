#include "QGSRules.h"

QGSRules::QGSRules()
{

}

QGSRules::QGSRules(const QList<Rule> & rules)
{

}

QGSRules::~QGSRules()
{

}

QGSRules & QGSRules::setRules(const QList<Rule> & rules)
{
	mRules = rules;
	return *this;
}

QList<Rule> QGSRules::getRules()const
{
	return mRules;
}

QGSRules & QGSRules::addRule(const Rule & rule)
{
	mRules.push_back(rule);
	return *this;
}

void QGSRules::clear()
{
	mRules.clear();
}
