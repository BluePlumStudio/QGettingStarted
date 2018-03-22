#include "QGSRules.h"

QGSRules::QGSRules()
{

}

QGSRules::QGSRules(const QList<QGSRules::Rule> & rules)
{

}

QGSRules::~QGSRules()
{

}

QGSRules & QGSRules::setRules(const QList<QGSRules::Rule> & rules)
{
	mRules = rules;
	return *this;
}

QList<QGSRules::Rule> QGSRules::getRules()const
{
	return mRules;
}

QGSRules & QGSRules::addRule(const QGSRules::Rule & rule)
{
	mRules.push_back(rule);
	return *this;
}

void QGSRules::clear()
{
	mRules.clear();
}