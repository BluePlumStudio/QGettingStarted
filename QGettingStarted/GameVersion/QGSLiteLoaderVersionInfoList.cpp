#include "QGSLiteLoaderVersionInfoList.h"
#include "../Util/QGSExceptionVersionNotFound.h"

QGSLiteLoaderVersionInfoList::QGSLiteLoaderVersionInfoList()
{
}

QGSLiteLoaderVersionInfo & QGSLiteLoaderVersionInfoList::operator[](const int index)
{
	return *(mLiteLoaderVersionInfoMap.begin() + index);
}

QGSLiteLoaderVersionInfoList::~QGSLiteLoaderVersionInfoList()
{

}

QGSLiteLoaderVersionInfo QGSLiteLoaderVersionInfoList::getLiteLoaderVersionInfo(const int index)
{
	return *(mLiteLoaderVersionInfoMap.begin() + index);
}

const QGSLiteLoaderVersionInfo & QGSLiteLoaderVersionInfoList::at(const int index)
{
	return *(mLiteLoaderVersionInfoMap.begin() + index);
}

bool QGSLiteLoaderVersionInfoList::addVersionInfo(const QString & version, const QGSLiteLoaderVersionInfo & versionInfo)
{
	if (mLiteLoaderVersionInfoMap.contains(version))
	{
		return false;
	}

	mLiteLoaderVersionInfoMap.insert(version, versionInfo);
	return true;
}

bool QGSLiteLoaderVersionInfoList::removeVersionInfo(const QString & version)
{
	if (!mLiteLoaderVersionInfoMap.contains(version))
	{
		return false;
	}

	mLiteLoaderVersionInfoMap.remove(version);
	return true;
}

bool QGSLiteLoaderVersionInfoList::containsVersionInfo(const QString & version)
{
	return mLiteLoaderVersionInfoMap.contains(version);
}

QGSLiteLoaderVersionInfo & QGSLiteLoaderVersionInfoList::getVersionInfo(const QString & version)
{
	return mLiteLoaderVersionInfoMap[version];
}

int QGSLiteLoaderVersionInfoList::size()const
{
	return mLiteLoaderVersionInfoMap.size();
}
