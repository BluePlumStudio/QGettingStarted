#include "QGSExtract.h"

QGSExtract::QGSExtract(const QStringList & exclude) :mExclude(exclude)
{
	if (!QMetaType::isRegistered(QMetaType::type("QGSExtract")))
	{
		qRegisterMetaType<QGSExtract>("QGSExtract");
	}
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