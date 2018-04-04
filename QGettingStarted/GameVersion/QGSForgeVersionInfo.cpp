#include "QGSForgeVersionInfo.h"


QGSForgeVersionInfo::QGSForgeFileInfo::QGSForgeFileInfo(const QString & format, const QString & category, const QString & hash, const QString & id)
	:mFormat(format), mCategory(category), mHash(hash), mId(id)
{

}

QGSForgeVersionInfo::QGSForgeFileInfo::~QGSForgeFileInfo()
{

}

QGSForgeVersionInfo::QGSForgeFileInfo & QGSForgeVersionInfo::QGSForgeFileInfo::setFormat(const QString & format)
{
	mFormat = format;
	return *this;
}

QGSForgeVersionInfo::QGSForgeFileInfo & QGSForgeVersionInfo::QGSForgeFileInfo::setCategory(const QString & category)
{
	mCategory = category;
	return *this;
}

QGSForgeVersionInfo::QGSForgeFileInfo & QGSForgeVersionInfo::QGSForgeFileInfo::setHash(const QString & hash)
{
	mHash = hash;
	return *this;
}

QGSForgeVersionInfo::QGSForgeFileInfo & QGSForgeVersionInfo::QGSForgeFileInfo::setId(const QString & id)
{
	mId = id;
	return *this;
}

QString QGSForgeVersionInfo::QGSForgeFileInfo::getFormat()const
{
	return mFormat;
}

QString QGSForgeVersionInfo::QGSForgeFileInfo::getCategory()const
{
	return mCategory;
}

QString QGSForgeVersionInfo::QGSForgeFileInfo::getHash()const
{
	return mHash;
}

QString QGSForgeVersionInfo::QGSForgeFileInfo::getId()const
{
	return mId;
}

/**/

QGSForgeVersionInfo::QGSForgeVersionInfo(const QString & branch, const int build, const QString & mcversion, const QString & modified, const QString & version, const QString & id, const QList<QGSForgeFileInfo> & files)
	:mBranch(branch), mBuild(build), mMcversion(mcversion), mModified(modified), mVersion(version), mId(id), mFileList(files)
{

}

bool QGSForgeVersionInfo::operator<(const QGSForgeVersionInfo & right) const
{
	//	return mBuild < right.getBuild() && mVersion < right.getVersion() && mMcversion < right.getMcversion();
	return mBuild < right.getBuild();
}

bool QGSForgeVersionInfo::operator>(const QGSForgeVersionInfo & right) const
{
	//return mBuild > right.getBuild() && mVersion > right.getVersion() && mMcversion > right.getMcversion();
	return mBuild > right.getBuild();
}

bool QGSForgeVersionInfo::operator==(const QGSForgeVersionInfo & right) const
{
	//return mBuild == right.getBuild() && mVersion == right.getVersion() && mMcversion == right.getMcversion();
	return mBuild == right.getBuild();
}

QGSForgeVersionInfo::~QGSForgeVersionInfo()
{

}

QString QGSForgeVersionInfo::getBranch()const
{
	return mBranch;
}

int QGSForgeVersionInfo::getBuild()const
{
	return mBuild;
}

QString QGSForgeVersionInfo::getMcversion()const
{
	return mMcversion;
}

QString QGSForgeVersionInfo::getModified()const
{
	return mModified;
}

QString QGSForgeVersionInfo::getVersion()const
{
	return mVersion;
}

QString QGSForgeVersionInfo::getId()const
{
	return mId;
}

QList<QGSForgeVersionInfo::QGSForgeFileInfo> QGSForgeVersionInfo::getFiles()const
{
	return mFileList;
}

QGSForgeVersionInfo & QGSForgeVersionInfo::setBranch(const QString & branch)
{
	mBranch = branch;
	return *this;
}

QGSForgeVersionInfo & QGSForgeVersionInfo::setBuild(const int build)
{
	mBuild = build;
	return *this;
}

QGSForgeVersionInfo & QGSForgeVersionInfo::setMcversion(const QString & mcversion)
{
	mMcversion = mcversion;
	return *this;
}

QGSForgeVersionInfo & QGSForgeVersionInfo::setModified(const QString & modified)
{
	mModified = modified;
	return *this;
}

QGSForgeVersionInfo & QGSForgeVersionInfo::setVersion(const QString & version)
{
	mVersion = version;
	return *this;
}

QGSForgeVersionInfo & QGSForgeVersionInfo::setId(const QString & id)
{
	mId = id;
	return *this;
}

QGSForgeVersionInfo & QGSForgeVersionInfo::setFiles(const QList<QGSForgeFileInfo> & files)
{
	mFileList = files;
	return *this;
}