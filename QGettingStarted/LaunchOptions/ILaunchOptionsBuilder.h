#pragma once

#include "QGSLaunchOptions.h"

class ILaunchOptionsBuilder 
{
public: 
	
	QGSLaunchOptions * getLaunchOptions();
	
	ILaunchOptionsBuilder & setConcreteAttribute();
protected: 
	QGSLaunchOptions * mLaunchOptionsPtr;
};
