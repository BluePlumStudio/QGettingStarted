#pragma once

#include "Extract.h"
#include "Rules.h"
#include "Downloads.h"

class Library 
{
public:

private: 
	QString mPackage;
	QString mName;
	QString mVersion;
	Downloads mDownloads;
	Extract mExtract;
	bool mLateload;
	QMap<QString, QString> mNatives;
	Rules mRules;
};
