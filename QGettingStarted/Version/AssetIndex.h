#pragma once

#include <QString>

#include "../Library/Downloads.h"

class AssetIndex :public Downloads::Download
{
public:
	AssetIndex();
	~AssetIndex();

private:
	qint64 mTotalSize;
	QString mId;
};

