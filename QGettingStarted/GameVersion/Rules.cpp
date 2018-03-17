#include "Rules.h"

Rules::Rules()
{

}

Rules::Rules(const QList<Rules::Rule> & rules)
{

}

Rules::~Rules()
{

}

Rules & Rules::setRules(const QList<Rules::Rule> & rules)
{
	mRules = rules;
	return *this;
}

QList<Rules::Rule> Rules::getRules()const
{
	return mRules;
}

Rules & Rules::addRule(const Rules::Rule & rule)
{
	mRules.push_back(rule);
	return *this;
}

void Rules::clear()
{
	mRules.clear();
}