#include "OptifineVersionInfoList.h"

OptifineVersionInfo::OptifineVersionInfo(const QString & id, const QString & mcversion, const QString & type, const QString & patch, const QString & fileName)
	:mId(id), mMcversion(mcversion), mType(type), mPatch(patch), mFileName(fileName)
{

}

bool OptifineVersionInfo::operator<(const OptifineVersionInfo & right) const
{
	return mMcversion < right.getMcversion() && mType < right.getType() && mPatch < right.getPatch();
}

bool OptifineVersionInfo::operator>(const OptifineVersionInfo & right) const
{
	return mMcversion > right.getMcversion() && mType > right.getType() && mPatch > right.getPatch();
}

bool OptifineVersionInfo::operator==(const OptifineVersionInfo & right) const
{
	return mMcversion == right.getMcversion() && mType == right.getType() && mPatch == right.getPatch();
}

OptifineVersionInfo::~OptifineVersionInfo()
{

}

QString OptifineVersionInfo::getId() const
{
	return mId;
}

QString OptifineVersionInfo::getMcversion() const
{
	return mMcversion;
}

QString OptifineVersionInfo::getType() const
{
	return mType;
}

QString OptifineVersionInfo::getPatch() const
{
	return mPatch;
}

QString OptifineVersionInfo::getFileName() const
{
	return mFileName;
}

OptifineVersionInfo & OptifineVersionInfo::setId(const QString & id)
{
	mId = id;
	return *this;
}

OptifineVersionInfo & OptifineVersionInfo::setMcversion(const QString & mcversion)
{
	mMcversion = mcversion;
	return *this;
}

OptifineVersionInfo & OptifineVersionInfo::setType(const QString & type)
{
	mType = type;
	return *this;
}

OptifineVersionInfo & OptifineVersionInfo::setPatch(const QString & patch)
{
	mPatch = patch;
	return *this;
}

OptifineVersionInfo & OptifineVersionInfo::setFileName(const QString & fileName)
{
	mFileName = fileName;
	return *this;
}

/**/

OptifineVersionInfoList::OptifineVersionInfoList()
{

}

OptifineVersionInfo & OptifineVersionInfoList::operator[](const int index)
{
	return mOptifineVersionInfoVector[index];
}

OptifineVersionInfoList::~OptifineVersionInfoList()
{

}

QList<OptifineVersionInfo> OptifineVersionInfoList::getVersionInfoList(const QString & mcversion)
{
	QList<OptifineVersionInfo> ret;
	for (auto & versionInfo : mOptifineVersionInfoVector)
	{
		if (versionInfo.getMcversion() == mcversion)
		{
			ret.push_back(versionInfo);
		}
	}

	return ret;
}

bool OptifineVersionInfoList::addVersionInfo(const OptifineVersionInfo & versionInfo)
{
	if (mOptifineVersionInfoVector.contains(versionInfo))
	{
		return false;
	}

	mOptifineVersionInfoVector.push_back(versionInfo);
	sort();
	return true;
}

int OptifineVersionInfoList::size()
{
	return mOptifineVersionInfoVector.size();
}

void OptifineVersionInfoList::sort()
{
	qSort(mOptifineVersionInfoVector.begin(), mOptifineVersionInfoVector.end());
}
