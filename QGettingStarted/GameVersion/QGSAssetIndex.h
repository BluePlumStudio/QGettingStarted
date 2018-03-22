#pragma once

#include <QString>

#include "QGSDownloads.h"

class QGSAssetIndex :public QGSDownloads::QGSIDownload
{
public:
	QGSAssetIndex(const int size = 0, const QString & SHA1 = "", const QString & path = "", const QUrl & url = QUrl(), const qint64 totalSize = 0, const QString & id = "");
	
	QGSAssetIndex(const QGSAssetIndex & right) = default;

	QGSAssetIndex(QGSAssetIndex && right) = default;

	QGSAssetIndex & operator=(const QGSAssetIndex & right) = default;

	QGSAssetIndex & operator=(QGSAssetIndex && right) = default;
	
	~QGSAssetIndex();

	QGSAssetIndex & setTotalSize(const qint64 totalSize);

	QGSAssetIndex & setId(const QString & id);

	qint64 getTotalSize()const;

	QString getId()const;

	void clear();
private:
	/*QGSIDownload
	int mSize;
	QString mSHA1;
	QString mPath;
	QUrl mUrl;
	*/

	qint64 mTotalSize;
	QString mId;
};

