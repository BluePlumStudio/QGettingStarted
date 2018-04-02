#include "QGSILaunchOptionsBuilder.h"

QGSILaunchOptionsBuilder::QGSILaunchOptionsBuilder(QObject * parent) :QObject(parent), mLaunchOptionsPtr(new QGSLaunchOptions)
{
	
}

QGSILaunchOptionsBuilder::~QGSILaunchOptionsBuilder()
{
}