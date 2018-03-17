#include <QJsonArray>
#include <algorithm>

#include "Util/QGSExceptionVersionNotFound.h"
#include "Util/QGSExceptionInvalidValue.h"
#include "Util/QGSExceptionFileIO.h"
#include "Util/QGSExceptionJsonPraseError.h"
#include "ForgeVersionInfoList.h"

ForgeVersionInfo::File::File(const QString & format, const QString & category, const QString & hash, const QString & id)
	:mFormat(format), mCategory(category), mHash(hash), mId(id)
{

}

ForgeVersionInfo::File::~File()
{

}

ForgeVersionInfo::File & ForgeVersionInfo::File::setFormat(const QString & format)
{
	mFormat = format;
	return *this;
}

ForgeVersionInfo::File & ForgeVersionInfo::File::setCategory(const QString & category)
{
	mCategory = category;
	return *this;
}

ForgeVersionInfo::File & ForgeVersionInfo::File::setHash(const QString & hash)
{
	mHash = hash;
	return *this;
}

ForgeVersionInfo::File & ForgeVersionInfo::File::setId(const QString & id)
{
	mId = id;
	return *this;
}

QString ForgeVersionInfo::File::getFormat()const
{
	return mFormat;
}

QString ForgeVersionInfo::File::getCategory()const
{
	return mCategory;
}

QString ForgeVersionInfo::File::getHash()const
{
	return mHash;
}

QString ForgeVersionInfo::File::getId()const
{
	return mId;
}

/**/

ForgeVersionInfo::ForgeVersionInfo(const QString & branch, const int build, const QString & mcversion, const QString & modified, const QString & version, const QString & id, const QList<File> & files)
	:mBranch(branch), mBuild(build), mMcversion(mcversion), mModified(modified), mVersion(version), mId(id), mFileList(files)
{

}

bool ForgeVersionInfo::operator<(const ForgeVersionInfo & right) const
{
	//	return mBuild < right.getBuild() && mVersion < right.getVersion() && mMcversion < right.getMcversion();
	return mBuild < right.getBuild();
}

bool ForgeVersionInfo::operator>(const ForgeVersionInfo & right) const
{
	//return mBuild > right.getBuild() && mVersion > right.getVersion() && mMcversion > right.getMcversion();
	return mBuild > right.getBuild();
}

bool ForgeVersionInfo::operator==(const ForgeVersionInfo & right) const
{
	//return mBuild == right.getBuild() && mVersion == right.getVersion() && mMcversion == right.getMcversion();
	return mBuild == right.getBuild();
}

ForgeVersionInfo::~ForgeVersionInfo()
{

}

QString ForgeVersionInfo::getBranch()const
{
	return mBranch;
}

int ForgeVersionInfo::getBuild()const
{
	return mBuild;
}

QString ForgeVersionInfo::getMcversion()const
{
	return mMcversion;
}

QString ForgeVersionInfo::getModified()const
{
	return mModified;
}

QString ForgeVersionInfo::getVersion()const
{
	return mVersion;
}

QString ForgeVersionInfo::getId()const
{
	return mId;
}

QList<ForgeVersionInfo::File> ForgeVersionInfo::getFiles()const
{
	return mFileList;
}

ForgeVersionInfo & ForgeVersionInfo::setBranch(const QString & branch)
{
	mBranch = branch;
	return *this;
}

ForgeVersionInfo & ForgeVersionInfo::setBuild(const int build)
{
	mBuild = build;
	return *this;
}

ForgeVersionInfo & ForgeVersionInfo::setMcversion(const QString & mcversion)
{
	mMcversion = mcversion;
	return *this;
}

ForgeVersionInfo & ForgeVersionInfo::setModified(const QString & modified)
{
	mModified = modified;
	return *this;
}

ForgeVersionInfo & ForgeVersionInfo::setVersion(const QString & version)
{
	mVersion = version;
	return *this;
}

ForgeVersionInfo & ForgeVersionInfo::setId(const QString & id)
{
	mId = id;
	return *this;
}

ForgeVersionInfo & ForgeVersionInfo::setFiles(const QList<File> & files)
{
	mFileList = files;
	return *this;
}

/**/

ForgeVersionInfoList::ForgeVersionInfoList()
{

}

ForgeVersionInfo & ForgeVersionInfoList::operator[](const int index)
{
	return mForgeVersionInfoVector[index];
}

ForgeVersionInfoList::~ForgeVersionInfoList()
{
}

const ForgeVersionInfo & ForgeVersionInfoList::getVersionInfo(const QString & build)
{
	auto it{ findForgeVersionInfo(build) };
	if (it == mForgeVersionInfoVector.end())
	{
		throw QGSExceptionVersionNotFound();
	}
	
	return *it;
}

bool ForgeVersionInfoList::addVersionInfo(const ForgeVersionInfo & versionInfo)
{
	if (mForgeVersionInfoVector.contains(versionInfo))
	{
		return false;
	}

	mForgeVersionInfoVector.push_back(versionInfo);
	sort();
	return true;
}

bool ForgeVersionInfoList::removeVersionInfo(const QString & build)
{
	auto it{ findForgeVersionInfo(build) };
	if (it == mForgeVersionInfoVector.end())
	{
		return false;
	}

	mForgeVersionInfoVector.erase(it);

	return true;
}

bool ForgeVersionInfoList::containsVersionInfo(const QString & build)
{
	auto it{ findForgeVersionInfo(build) };
	if (it == mForgeVersionInfoVector.end())
	{
		return false;
	}

	return true;
}

int ForgeVersionInfoList::size()
{
	return mForgeVersionInfoVector.size();
}

bool ForgeVersionInfoList::merge(const ForgeVersionInfoList & right)
{
	std::vector<ForgeVersionInfo> newInfoVector;
	std::vector<ForgeVersionInfo> && oldInfoVector{ mForgeVersionInfoVector.toStdVector() };
	std::vector<ForgeVersionInfo> && rightInfoVector{ right.mForgeVersionInfoVector.toStdVector() };
	newInfoVector.resize(oldInfoVector.size() + rightInfoVector.size());
	std::merge(std::begin(oldInfoVector),
		std::end(oldInfoVector),
		std::begin(rightInfoVector),
		std::end(rightInfoVector),
		std::begin(newInfoVector));
	std::unique(std::begin(newInfoVector), std::end(newInfoVector));
	mForgeVersionInfoVector = QVector<ForgeVersionInfo>::fromStdVector(newInfoVector);

	return true;
}

void ForgeVersionInfoList::sort()
{
	qSort(mForgeVersionInfoVector.begin(), mForgeVersionInfoVector.end(), [](const ForgeVersionInfo & left, const ForgeVersionInfo & right)
	{
		return left.getBuild() < right.getBuild();
	});
}

QVector<ForgeVersionInfo>::iterator ForgeVersionInfoList::findForgeVersionInfo(const QString & build)
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

QVector<ForgeVersionInfo> ForgeVersionInfoList::getForgeVersionInfoVector()const
{
	return mForgeVersionInfoVector;
}
