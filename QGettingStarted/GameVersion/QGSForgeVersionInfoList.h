#pragma once

#include <QString>
#include <QMap>
#include <QVector>
#include <QUrl>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QList>

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

class QGSForgeVersionInfoList
{
public:
	QGSForgeVersionInfoList();

	QGSForgeVersionInfoList(const QGSForgeVersionInfoList & right) = default;

	QGSForgeVersionInfoList(QGSForgeVersionInfoList && right) = default;

	QGSForgeVersionInfoList & operator=(const QGSForgeVersionInfoList & right) = default;

	QGSForgeVersionInfoList & operator=(QGSForgeVersionInfoList && right) = default;

	QGSForgeVersionInfo & operator[](const int index);

	~QGSForgeVersionInfoList();

	const QGSForgeVersionInfo & getVersionInfo(const QString & build);

	bool addVersionInfo(const QGSForgeVersionInfo & versionInfo);

	bool removeVersionInfo(const QString & build);

	bool containsVersionInfo(const QString & build);

	int size();

	bool merge(const QGSForgeVersionInfoList & right);

	QVector<QGSForgeVersionInfo> getForgeVersionInfoVector()const;
private:
	void sort();
	QVector<QGSForgeVersionInfo>::iterator findForgeVersionInfo(const QString & build);
private:
	QVector<QGSForgeVersionInfo> mForgeVersionInfoVector;
};
