#include "Extract.h"

Extract::Extract(const QStringList & exclude)
{
	mExclude = exclude;
}

Extract::~Extract()
{

}

Extract & Extract::setExclude(const QStringList & exclude)
{
	mExclude = exclude;
	return *this;
}

QStringList Extract::getExclude()const
{
	return mExclude;
}