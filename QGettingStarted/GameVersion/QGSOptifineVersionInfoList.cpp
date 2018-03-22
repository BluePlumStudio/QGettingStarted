#include "QGSOptifineVersionInfoList.h"

QGSOptifineVersionInfo::QGSOptifineVersionInfo(const QString & id, const QString & mcversion, const QString & type, const QString & patch, const QString & fileName)
	:mId(id), mMcversion(mcversion), mType(type), mPatch(patch), mFileName(fileName)
{

}

bool QGSOptifineVersionInfo::operator<(const QGSOptifineVersionInfo & right) const
{
	return mMcversion < right.getMcversion() && mType < right.getType() && mPatch < right.getPatch();
}

bool QGSOptifineVersionInfo::operator>(const QGSOptifineVersionInfo & right) const
{
	return mMcversion > right.getMcversion() && mType > right.getType() && mPatch > right.getPatch();
}

bool QGSOptifineVersionInfo::operator==(const QGSOptifineVersionInfo & right) const
{
	return mMcversion == right.getMcversion() && mType == right.getType() && mPatch == right.getPatch();
}

QGSOptifineVersionInfo::~QGSOptifineVersionInfo()
{

}

QString QGSOptifineVersionInfo::getId() const
{
	return mId;
}

QString QGSOptifineVersionInfo::getMcversion() const
{
	return mMcversion;
}

QString QGSOptifineVersionInfo::getType() const
{
	return mType;
}

QString QGSOptifineVersionInfo::getPatch() const
{
	return mPatch;
}

QString QGSOptifineVersionInfo::getFileName() const
{
	return mFileName;
}

QGSOptifineVersionInfo & QGSOptifineVersionInfo::setId(const QString & id)
{
	mId = id;
	return *this;
}

QGSOptifineVersionInfo & QGSOptifineVersionInfo::setMcversion(const QString & mcversion)
{
	mMcversion = mcversion;
	return *this;
}

QGSOptifineVersionInfo & QGSOptifineVersionInfo::setType(const QString & type)
{
	mType = type;
	return *this;
}

QGSOptifineVersionInfo & QGSOptifineVersionInfo::setPatch(const QString & patch)
{
	mPatch = patch;
	return *this;
}

QGSOptifineVersionInfo & QGSOptifineVersionInfo::setFileName(const QString & fileName)
{
	mFileName = fileName;
	return *this;
}

/**/

QGSOptifineVersionInfoList::QGSOptifineVersionInfoList()
{

}

QGSOptifineVersionInfo & QGSOptifineVersionInfoList::operator[](const int index)
{
	return mOptifineVersionInfoVector[index];
}

QGSOptifineVersionInfoList::~QGSOptifineVersionInfoList()
{

}

QList<QGSOptifineVersionInfo> QGSOptifineVersionInfoList::getVersionInfoList(const QString & mcversion)
{
	QList<QGSOptifineVersionInfo> ret;
	for (auto & versionInfo : mOptifineVersionInfoVector)
	{
		if (versionInfo.getMcversion() == mcversion)
		{
			ret.push_back(versionInfo);
		}
	}

	return ret;
}

bool QGSOptifineVersionInfoList::addVersionInfo(const QGSOptifineVersionInfo & versionInfo)
{
	if (mOptifineVersionInfoVector.contains(versionInfo))
	{
		return false;
	}

	mOptifineVersionInfoVector.push_back(versionInfo);
	sort();
	return true;
}

int QGSOptifineVersionInfoList::size()
{
	return mOptifineVersionInfoVector.size();
}

void QGSOptifineVersionInfoList::sort()
{
	qSort(mOptifineVersionInfoVector.begin(), mOptifineVersionInfoVector.end());
}
