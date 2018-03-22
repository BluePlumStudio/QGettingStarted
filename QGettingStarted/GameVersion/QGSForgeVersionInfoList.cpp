#include <QJsonArray>
#include <algorithm>

#include "Util/QGSExceptionVersionNotFound.h"
#include "Util/QGSExceptionInvalidValue.h"
#include "Util/QGSExceptionFileIO.h"
#include "Util/QGSExceptionJsonPraseError.h"
#include "QGSForgeVersionInfoList.h"

QGSForgeVersionInfo::File::File(const QString & format, const QString & category, const QString & hash, const QString & id)
	:mFormat(format), mCategory(category), mHash(hash), mId(id)
{

}

QGSForgeVersionInfo::File::~File()
{

}

QGSForgeVersionInfo::File & QGSForgeVersionInfo::File::setFormat(const QString & format)
{
	mFormat = format;
	return *this;
}

QGSForgeVersionInfo::File & QGSForgeVersionInfo::File::setCategory(const QString & category)
{
	mCategory = category;
	return *this;
}

QGSForgeVersionInfo::File & QGSForgeVersionInfo::File::setHash(const QString & hash)
{
	mHash = hash;
	return *this;
}

QGSForgeVersionInfo::File & QGSForgeVersionInfo::File::setId(const QString & id)
{
	mId = id;
	return *this;
}

QString QGSForgeVersionInfo::File::getFormat()const
{
	return mFormat;
}

QString QGSForgeVersionInfo::File::getCategory()const
{
	return mCategory;
}

QString QGSForgeVersionInfo::File::getHash()const
{
	return mHash;
}

QString QGSForgeVersionInfo::File::getId()const
{
	return mId;
}

/**/

QGSForgeVersionInfo::QGSForgeVersionInfo(const QString & branch, const int build, const QString & mcversion, const QString & modified, const QString & version, const QString & id, const QList<File> & files)
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

QList<QGSForgeVersionInfo::File> QGSForgeVersionInfo::getFiles()const
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

QGSForgeVersionInfo & QGSForgeVersionInfo::setFiles(const QList<File> & files)
{
	mFileList = files;
	return *this;
}

/**/

QGSForgeVersionInfoList::QGSForgeVersionInfoList()
{

}

QGSForgeVersionInfo & QGSForgeVersionInfoList::operator[](const int index)
{
	return mForgeVersionInfoVector[index];
}

QGSForgeVersionInfoList::~QGSForgeVersionInfoList()
{
}

const QGSForgeVersionInfo & QGSForgeVersionInfoList::getVersionInfo(const QString & build)
{
	auto it{ findForgeVersionInfo(build) };
	if (it == mForgeVersionInfoVector.end())
	{
		throw QGSExceptionVersionNotFound();
	}
	
	return *it;
}

bool QGSForgeVersionInfoList::addVersionInfo(const QGSForgeVersionInfo & versionInfo)
{
	if (mForgeVersionInfoVector.contains(versionInfo))
	{
		return false;
	}

	mForgeVersionInfoVector.push_back(versionInfo);
	sort();
	return true;
}

bool QGSForgeVersionInfoList::removeVersionInfo(const QString & build)
{
	auto it{ findForgeVersionInfo(build) };
	if (it == mForgeVersionInfoVector.end())
	{
		return false;
	}

	mForgeVersionInfoVector.erase(it);

	return true;
}

bool QGSForgeVersionInfoList::containsVersionInfo(const QString & build)
{
	auto it{ findForgeVersionInfo(build) };
	if (it == mForgeVersionInfoVector.end())
	{
		return false;
	}

	return true;
}

int QGSForgeVersionInfoList::size()
{
	return mForgeVersionInfoVector.size();
}

bool QGSForgeVersionInfoList::merge(const QGSForgeVersionInfoList & right)
{
	std::vector<QGSForgeVersionInfo> newInfoVector;
	std::vector<QGSForgeVersionInfo> && oldInfoVector{ mForgeVersionInfoVector.toStdVector() };
	std::vector<QGSForgeVersionInfo> && rightInfoVector{ right.mForgeVersionInfoVector.toStdVector() };
	newInfoVector.resize(oldInfoVector.size() + rightInfoVector.size());
	std::merge(std::begin(oldInfoVector),
		std::end(oldInfoVector),
		std::begin(rightInfoVector),
		std::end(rightInfoVector),
		std::begin(newInfoVector));
	std::unique(std::begin(newInfoVector), std::end(newInfoVector));
	mForgeVersionInfoVector = QVector<QGSForgeVersionInfo>::fromStdVector(newInfoVector);

	return true;
}

void QGSForgeVersionInfoList::sort()
{
	qSort(mForgeVersionInfoVector.begin(), mForgeVersionInfoVector.end(), [](const QGSForgeVersionInfo & left, const QGSForgeVersionInfo & right)
	{
		return left.getBuild() < right.getBuild();
	});
}

QVector<QGSForgeVersionInfo>::iterator QGSForgeVersionInfoList::findForgeVersionInfo(const QString & build)
{
	auto it{ mForgeVersionInfoVector.begin() };

	while (it++ != mForgeVersionInfoVector.end())
	{
		if (it->getBuild() == build)
		{
			break;
		}
	}

	return it;
}

QVector<QGSForgeVersionInfo> QGSForgeVersionInfoList::getForgeVersionInfoVector()const
{
	return mForgeVersionInfoVector;
}
