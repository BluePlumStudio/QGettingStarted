#include "QGSExtract.h"

QGSExtract::QGSExtract(const QStringList & exclude)
{
	mExclude = exclude;
}

QGSExtract::~QGSExtract()
{

}

QGSExtract & QGSExtract::setExclude(const QStringList & exclude)
{
	mExclude = exclude;
	return *this;
}

QStringList QGSExtract::getExclude()const
{
	return mExclude;
}