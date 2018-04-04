#pragma once

#include <QString>
#include <QList>
#include <QMetaType>

class QGSForgeVersionInfo
{
public:
	class QGSForgeFileInfo
	{
	public:
		QGSForgeFileInfo(const QString & format = "", const QString & category = "", const QString & hash = "", const QString & id = "");

		QGSForgeFileInfo(const QGSForgeFileInfo & right) = default;

		QGSForgeFileInfo(QGSForgeFileInfo && right) = default;

		QGSForgeFileInfo & operator=(const QGSForgeFileInfo & right) = default;

		QGSForgeFileInfo & operator=(QGSForgeFileInfo && right) = default;

		~QGSForgeFileInfo();

		QGSForgeFileInfo & setFormat(const QString & format);
		QGSForgeFileInfo & setCategory(const QString & category);
		QGSForgeFileInfo & setHash(const QString & hash);
		QGSForgeFileInfo & setId(const QString & id);

		QString getFormat()const;
		QString getCategory()const;
		QString getHash()const;
		QString getId()const;

	private:
		QString mFormat;
		QString mCategory;
		QString mHash;
		QString mId;
	};
public:
	QGSForgeVersionInfo(const QString & branch = "",
		const int build = 0,
		const QString & mcversion = "",
		const QString & modified = "",
		const QString & version = "",
		const QString & id = "",
		const QList<QGSForgeFileInfo> & files = QList<QGSForgeFileInfo>());

	QGSForgeVersionInfo(const QGSForgeVersionInfo & right) = default;

	QGSForgeVersionInfo(QGSForgeVersionInfo && right) = default;

	QGSForgeVersionInfo & operator=(const QGSForgeVersionInfo & right) = default;

	QGSForgeVersionInfo & operator=(QGSForgeVersionInfo && right) = default;

	bool operator<(const QGSForgeVersionInfo & right)const;

	bool operator>(const QGSForgeVersionInfo & right)const;

	bool operator==(const QGSForgeVersionInfo & right)const;

	~QGSForgeVersionInfo();

	QString getBranch()const;
	int getBuild()const;
	QString getMcversion()const;
	QString getModified()const;
	QString getVersion()const;
	QString getId()const;
	QList<QGSForgeFileInfo> getFiles()const;

	QGSForgeVersionInfo & setBranch(const QString & branch);
	QGSForgeVersionInfo & setBuild(const int build);
	QGSForgeVersionInfo & setMcversion(const QString & mcversion);
	QGSForgeVersionInfo & setModified(const QString & modified);
	QGSForgeVersionInfo & setVersion(const QString & version);
	QGSForgeVersionInfo & setId(const QString & id);
	QGSForgeVersionInfo & setFiles(const QList<QGSForgeFileInfo> & files);
private:
	QString mBranch;
	int mBuild;
	QString mMcversion;
	QString mModified;
	QString mVersion;
	QString mId;
	QList<QGSForgeFileInfo> mFileList;
};

Q_DECLARE_METATYPE(QGSForgeVersionInfo)
Q_DECLARE_METATYPE(QGSForgeVersionInfo::QGSForgeFileInfo)