#pragma once

#include "ILaunchOptionsBuilder.h"
#include "QGSLaunchOptions.h"

class QGSLaunchOptionsBuilder: public ILaunchOptionsBuilder 
{
public: 
	
	QGSLaunchOptions * getLaunchOptions();

};