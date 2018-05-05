#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <algorithm>

#include "../Util/QGSExceptionVersionNotFound.h"
#include "../Util/QGSExceptionInvalidValue.h"
#include "../Util/QGSExceptionIO.h"
#include "../Util/QGSExceptionJsonPraseError.h"
#include "QGSGameVersionInfoList.h"

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

const QGSGameVersionInfo & QGSGameVersionInfoList::at(const int index)
{
	return mGameVersionInfoVector.at(index);
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
	auto it(findGameVersionInfo(version));
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
	auto it(findGameVersionInfo(version));
	if (it == mGameVersionInfoVector.end())
	{
		return false;
	}

	mGameVersionInfoVector.erase(it);

	return true;
}

bool QGSGameVersionInfoList::containsVersionInfo(const QString & version)
{
	auto it(findGameVersionInfo(version));
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
	auto it(mGameVersionInfoVector.begin());

	while (it++ != mGameVersionInfoVector.end())
	{
		if (it->getId() == version)
		{
			break;
		}
	}

	return it;
}
