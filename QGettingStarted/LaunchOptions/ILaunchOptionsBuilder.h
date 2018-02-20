#pragma once

#include "ILaunchOptions.h"

class ILaunchOptionsBuilder 
{
public: 
	
	ILaunchOptions * getLaunchOptions();
	
	ILaunchOptionsBuilder & setConcreteAttribute();
protected: 
	ILaunchOptions * mLaunchOptionsPtr;
};
