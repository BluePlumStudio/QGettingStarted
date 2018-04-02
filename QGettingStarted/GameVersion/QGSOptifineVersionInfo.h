#pragma once

#include <QString>
#include <QMetaType>

class QGSOptifineVersionInfo
{
public:
	QGSOptifineVersionInfo(const QString & id = "",
		const QString & mcversion = "",
		const QString & type = "",
		const QString & patch = "",
		const QString & fileName = "");

	QGSOptifineVersionInfo(const QGSOptifineVersionInfo & right) = default;

	QGSOptifineVersionInfo(QGSOptifineVersionInfo && right) = default;

	QGSOptifineVersionInfo & operator=(const QGSOptifineVersionInfo & right) = default;

	QGSOptifineVersionInfo & operator=(QGSOptifineVersionInfo && right) = default;

	bool operator<(const QGSOptifineVersionInfo & right)const;

	bool operator>(const QGSOptifineVersionInfo & right)const;

	bool operator==(const QGSOptifineVersionInfo & right)const;

	~QGSOptifineVersionInfo();

	QString getId()const;
	QString getMcversion()const;
	QString getType()const;
	QString getPatch()const;
	QString getFileName()const;

	QGSOptifineVersionInfo & setId(const QString & id);
	QGSOptifineVersionInfo & setMcversion(const QString & mcversion);
	QGSOptifineVersionInfo & setType(const QString & type);
	QGSOptifineVersionInfo & setPatch(const QString & patch);
	QGSOptifineVersionInfo & setFileName(const QString & fileName);
private:
	QString mId;
	QString mMcversion;
	QString mType;
	QString mPatch;
	QString mFileName;
};

Q_DECLARE_METATYPE(QGSOptifineVersionInfo)