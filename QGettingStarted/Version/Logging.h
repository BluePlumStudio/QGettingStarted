#pragma once

#include <QString>
#include <QStringList>

#include "../Library/Downloads.h"

class Logging
{
private:
	struct File :public Downloads::Download
	{
		QString mId;
	};
public:
	Logging();
	~Logging();

private:
	File mFile;
	QString mArgument;
	QString mType;
};
