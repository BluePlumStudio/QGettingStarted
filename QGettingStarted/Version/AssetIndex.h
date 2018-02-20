#pragma once

#include <QString>

#include "Downloads.h"

class AssetIndex :public Downloads::Download
{
public:
	AssetIndex(const int size, const QString & SHA1, const QString & path, const QUrl & url, const qint64 totalSize, const QString & id);
	~AssetIndex();

	inline AssetIndex & setTotalSize(const qint64 totalSize);

	inline AssetIndex & setId(const QString & id);

	inline qint64 getTotalSize()const;

	inline QString getId()const;
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

