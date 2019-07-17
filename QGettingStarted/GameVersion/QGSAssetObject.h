#pragma once

#include <QMap>
#include <QString>
#include <QMetaType>

class QGSAssetObject
{
public:
	QGSAssetObject(const QString & path = "", const QString & hash = "", const qint64 & size = 0);

	QGSAssetObject(const QGSAssetObject & right) = default;

	QGSAssetObject(QGSAssetObject && right) = default;

	QGSAssetObject & operator=(const QGSAssetObject & right) = default;

	QGSAssetObject & operator=(QGSAssetObject && right) = default;

	~QGSAssetObject();

	QGSAssetObject & setPath(const QString & path);
	QGSAssetObject & setHash(const QString & hash);
	QGSAssetObject & setSize(const qint64 size);

	QString getPath()const;
	QString getHash()const;
	qint64 getSize()const;
private:
	QString mPath;
	QString mHash;
	qint64 mSize;
};

Q_DECLARE_METATYPE(QGSAssetObject)