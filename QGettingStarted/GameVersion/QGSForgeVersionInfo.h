#pragma once

#include <QString>
#include <QList>
#include <QMetaType>

class QGSForgeVersionInfo
{
public:
	class File
	{
	public:
		File(const QString & format = "", const QString & category = "", const QString & hash = "", const QString & id = "");

		~File();

		File & setFormat(const QString & format);
		File & setCategory(const QString & category);
		File & setHash(const QString & hash);
		File & setId(const QString & id);

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
		const QList<File> & files = QList<File>());

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
	QList<File> getFiles()const;

	QGSForgeVersionInfo & setBranch(const QString & branch);
	QGSForgeVersionInfo & setBuild(const int build);
	QGSForgeVersionInfo & setMcversion(const QString & mcversion);
	QGSForgeVersionInfo & setModified(const QString & modified);
	QGSForgeVersionInfo & setVersion(const QString & version);
	QGSForgeVersionInfo & setId(const QString & id);
	QGSForgeVersionInfo & setFiles(const QList<File> & files);
private:
	QString mBranch;
	int mBuild;
	QString mMcversion;
	QString mModified;
	QString mVersion;
	QString mId;
	QList<File> mFileList;
};

Q_DECLARE_METATYPE(QGSForgeVersionInfo)