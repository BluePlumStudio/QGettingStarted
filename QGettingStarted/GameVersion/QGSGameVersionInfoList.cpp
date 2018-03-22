#include <QJsonArray>
#include <algorithm>

#include "Util/QGSExceptionVersionNotFound.h"
#include "Util/QGSExceptionInvalidValue.h"
#include "Util/QGSExceptionFileIO.h"
#include "Util/QGSExceptionJsonPraseError.h"
#include "QGSGameVersionInfoList.h"

QGSGameVersionInfo::QGSGameVersionInfo(const QString & id, const QString & type, const QString & time, const QString & releaseTime, const QUrl & url)
	:mId(id), mType(type), mTime(time), mReleaseTime(releaseTime), mUrl(url)
{

}

bool QGSGameVersionInfo::operator<(const QGSGameVersionInfo & right) const
{
	return mId < right.getId();
}

bool QGSGameVersionInfo::operator>(const QGSGameVersionInfo & right) const
{
	return mId > right.getId();
}

bool QGSGameVersionInfo::operator==(const QGSGameVersionInfo & right) const
{
	return mId == right.getId();
}

QGSGameVersionInfo::~QGSGameVersionInfo()
{

}

QString QGSGameVersionInfo::getId()const
{
	return mId;
}

QString QGSGameVersionInfo::getType()const
{
	return mType;
}

QString QGSGameVersionInfo::getTime()const
{
	return mTime;
}

QString QGSGameVersionInfo::getReleaseTime()const
{
	return mReleaseTime;
}

QUrl QGSGameVersionInfo::getUrl()const
{
	return mUrl;
}

QGSGameVersionInfo & QGSGameVersionInfo::setId(const QString & id)
{
	mId = id;
	return *this;
}

QGSGameVersionInfo & QGSGameVersionInfo::setType(const QString & type)
{
	mType = type;
	return *this;
}

QGSGameVersionInfo & QGSGameVersionInfo::setTime(const QString & time)
{
	mTime = time;
	return *this;
}

QGSGameVersionInfo & QGSGameVersionInfo::setReleaseTime(const QString & releaseTime)
{
	mReleaseTime = releaseTime;
	return *this;
}

QGSGameVersionInfo & QGSGameVersionInfo::setUrl(const QUrl & url)
{
	mUrl = url;
	return *this;
}

/**/

QGSGameVersionInfoList::QGSGameVersionInfoList()
{

}

QGSGameVersionInfo & QGSGameVersionInfoList::operator[](const int index)
{
	return mGameVersionInfoVector[index];
}

QGSGameVersionInfoList::~QGSGameVersionInfoList()
{
}

QString QGSGameVersionInfoList::getLatestSnapshot() const
{
	return mLatestSnapshot;
}

QString QGSGameVersionInfoList::getLatestRelease() const
{
	return mLatestRelease;
}

QGSGameVersionInfoList & QGSGameVersionInfoList::setLatestSnapshot(const QString & snapshot)
{
	mLatestSnapshot = snapshot;
	return *this;
}

QGSGameVersionInfoList & QGSGameVersionInfoList::setLatestRelease(const QString & release)
{
	mLatestRelease = release;
	return *this;
}

QGSGameVersionInfo & QGSGameVersionInfoList::getVersionInfo(const QString & version)
{
	auto it{ findGameVersionInfo(version) };
	if (it == mGameVersionInfoVector.end())
	{
		throw QGSExceptionVersionNotFound();
	}

	return *it;
}

bool QGSGameVersionInfoList::addVersionInfo(const QGSGameVersionInfo & versionInfo)
{
	if (mGameVersionInfoVector.contains(versionInfo))
	{
		return false;
	}

	mGameVersionInfoVector.push_back(versionInfo);
	sort();
	return true;
}

bool QGSGameVersionInfoList::removeVersionInfo(const QString & version)
{
	auto it{ findGameVersionInfo(version) };
	if (it == mGameVersionInfoVector.end())
	{
		return false;
	}

	mGameVersionInfoVector.erase(it);

	return true;
}

bool QGSGameVersionInfoList::containsVersionInfo(const QString & version)
{
	auto it{ findGameVersionInfo(version) };
	if (it == mGameVersionInfoVector.end())
	{
		return false;
	}

	return true;
}

int QGSGameVersionInfoList::size()
{
	return mGameVersionInfoVector.size();
}

void QGSGameVersionInfoList::sort()
{
	qSort(mGameVersionInfoVector.begin(), mGameVersionInfoVector.end());
}

QVector<QGSGameVersionInfo>::iterator QGSGameVersionInfoList::findGameVersionInfo(const QString & version)
{
	auto it{ mGameVersionInfoVector.begin() };

	while (it++ != mGameVersionInfoVector.end())
	{
		if (it->getId() == version)
		{
			break;
		}
	}

	return it;
}
