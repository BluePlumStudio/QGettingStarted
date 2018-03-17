#pragma once

#include <QString>
#include <QMap>
#include <QVector>
#include <QUrl>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QList>

class ForgeVersionInfo
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
	ForgeVersionInfo(const QString & branch = "",
		const int build = 0,
		const QString & mcversion = "",
		const QString & modified = "",
		const QString & version = "",
		const QString & id = "",
		const QList<File> & files = QList<File>());

	ForgeVersionInfo(const ForgeVersionInfo & right) = default;

	ForgeVersionInfo(ForgeVersionInfo && right) = default;

	ForgeVersionInfo & operator=(const ForgeVersionInfo & right) = default;

	ForgeVersionInfo & operator=(ForgeVersionInfo && right) = default;

	bool operator<(const ForgeVersionInfo & right)const;

	bool operator>(const ForgeVersionInfo & right)const;

	bool operator==(const ForgeVersionInfo & right)const;

	~ForgeVersionInfo();

	QString getBranch()const;
	int getBuild()const;
	QString getMcversion()const;
	QString getModified()const;
	QString getVersion()const;
	QString getId()const;
	QList<File> getFiles()const;

	ForgeVersionInfo & setBranch(const QString & branch);
	ForgeVersionInfo & setBuild(const int build);
	ForgeVersionInfo & setMcversion(const QString & mcversion);
	ForgeVersionInfo & setModified(const QString & modified);
	ForgeVersionInfo & setVersion(const QString & version);
	ForgeVersionInfo & setId(const QString & id);
	ForgeVersionInfo & setFiles(const QList<File> & files);
private:
	QString mBranch;
	int mBuild;
	QString mMcversion;
	QString mModified;
	QString mVersion;
	QString mId;
	QList<File> mFileList;
};

class ForgeVersionInfoList
{
public:
	ForgeVersionInfoList();

	ForgeVersionInfoList(const ForgeVersionInfoList & right) = default;

	ForgeVersionInfoList(ForgeVersionInfoList && right) = default;

	ForgeVersionInfoList & operator=(const ForgeVersionInfoList & right) = default;

	ForgeVersionInfoList & operator=(ForgeVersionInfoList && right) = default;

	ForgeVersionInfo & operator[](const int index);

	~ForgeVersionInfoList();

	const ForgeVersionInfo & getVersionInfo(const QString & build);

	bool addVersionInfo(const ForgeVersionInfo & versionInfo);

	bool removeVersionInfo(const QString & build);

	bool containsVersionInfo(const QString & build);

	int size();

	bool merge(const ForgeVersionInfoList & right);

	QVector<ForgeVersionInfo> getForgeVersionInfoVector()const;
private:
	void sort();
	QVector<ForgeVersionInfo>::iterator findForgeVersionInfo(const QString & build);
private:
	QVector<ForgeVersionInfo> mForgeVersionInfoVector;
};
