#pragma once

#include <QString>

#include "Downloads.h"

class AssetIndex :public Downloads::Download
{
public:
	AssetIndex(const int size = 0, const QString & SHA1 = "", const QString & path = "", const QUrl & url = QUrl(), const qint64 totalSize = 0, const QString & id = "");
	
	AssetIndex(const AssetIndex & right) = default;

	AssetIndex(AssetIndex && right) = default;

	AssetIndex & operator=(const AssetIndex & right) = default;

	AssetIndex & operator=(AssetIndex && right) = default;
	
	~AssetIndex();

	AssetIndex & setTotalSize(const qint64 totalSize);

	AssetIndex & setId(const QString & id);

	qint64 getTotalSize()const;

	QString getId()const;

	void clear();
private:
	/*Download
	int mSize;
	QString mSHA1;
	QString mPath;
	QUrl mUrl;
	*/

	qint64 mTotalSize;
	QString mId;
};

