#include <QJsonArray>
#include <algorithm>

#include "Util/QGSExceptionVersionNotFound.h"
#include "Util/QGSExceptionInvalidValue.h"
#include "Util/QGSExceptionFileIO.h"
#include "Util/QGSExceptionJsonPraseError.h"
#include "GameVersionInfoList.h"

GameVersionInfo::GameVersionInfo(const QString & id, const QString & type, const QString & time, const QString & releaseTime, const QUrl & url)
	:mId(id), mType(type), mTime(time), mReleaseTime(releaseTime), mUrl(url)
{

}

bool GameVersionInfo::operator<(const GameVersionInfo & right) const
{
	return mId < right.getId();
}

bool GameVersionInfo::operator>(const GameVersionInfo & right) const
{
	return mId > right.getId();
}

bool GameVersionInfo::operator==(const GameVersionInfo & right) const
{
	return mId == right.getId();
}

GameVersionInfo::~GameVersionInfo()
{

}

QString GameVersionInfo::getId()const
{
	return mId;
}

QString GameVersionInfo::getType()const
{
	return mType;
}

QString GameVersionInfo::getTime()const
{
	return mTime;
}

QString GameVersionInfo::getReleaseTime()const
{
	return mReleaseTime;
}

QUrl GameVersionInfo::getUrl()const
{
	return mUrl;
}

GameVersionInfo & GameVersionInfo::setId(const QString & id)
{
	mId = id;
	return *this;
}

GameVersionInfo & GameVersionInfo::setType(const QString & type)
{
	mType = type;
	return *this;
}

GameVersionInfo & GameVersionInfo::setTime(const QString & time)
{
	mTime = time;
	return *this;
}

GameVersionInfo & GameVersionInfo::setReleaseTime(const QString & releaseTime)
{
	mReleaseTime = releaseTime;
	return *this;
}

GameVersionInfo & GameVersionInfo::setUrl(const QUrl & url)
{
	mUrl = url;
	return *this;
}

/**/

GameVersionInfoList::GameVersionInfoList()
{

}

GameVersionInfo & GameVersionInfoList::operator[](const int index)
{
	return mGameVersionInfoVector[index];
}

GameVersionInfoList::~GameVersionInfoList()
{
}

QString GameVersionInfoList::getLatestSnapshot() const
{
	return mLatestSnapshot;
}

QString GameVersionInfoList::getLatestRelease() const
{
	return mLatestRelease;
}

GameVersionInfoList & GameVersionInfoList::setLatestSnapshot(const QString & snapshot)
{
	mLatestSnapshot = snapshot;
	return *this;
}

GameVersionInfoList & GameVersionInfoList::setLatestRelease(const QString & release)
{
	mLatestRelease = release;
	return *this;
}

GameVersionInfo & GameVersionInfoList::getVersionInfo(const QString & version)
{
	auto it{ findGameVersionInfo(version) };
	if (it == mGameVersionInfoVector.end())
	{
		throw QGSExceptionVersionNotFound();
	}

	return *it;
}

bool GameVersionInfoList::addVersionInfo(const GameVersionInfo & versionInfo)
{
	if (mGameVersionInfoVector.contains(versionInfo))
	{
		return false;
	}

	mGameVersionInfoVector.push_back(versionInfo);
	sort();
	return true;
}

bool GameVersionInfoList::removeVersionInfo(const QString & version)
{
	auto it{ findGameVersionInfo(version) };
	if (it == mGameVersionInfoVector.end())
	{
		return false;
	}

	mGameVersionInfoVector.erase(it);

	return true;
}

bool GameVersionInfoList::containsVersionInfo(const QString & version)
{
	auto it{ findGameVersionInfo(version) };
	if (it == mGameVersionInfoVector.end())
	{
		return false;
	}

	return true;
}

int GameVersionInfoList::size()
{
	return mGameVersionInfoVector.size();
}

void GameVersionInfoList::sort()
{
	qSort(mGameVersionInfoVector.begin(), mGameVersionInfoVector.end());
}

QVector<GameVersionInfo>::iterator GameVersionInfoList::findGameVersionInfo(const QString & version)
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
