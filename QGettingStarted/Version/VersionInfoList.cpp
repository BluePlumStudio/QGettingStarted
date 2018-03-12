#include <QJsonArray>
#include <algorithm>

#include "Util/QGSExceptionVersionNotFound.h"
#include "Util/QGSExceptionInvalidValue.h"
#include "Util/QGSExceptionFileIO.h"
#include "Util/QGSExceptionJsonPraseError.h"
#include "VersionInfoList.h"

VersionInfo::VersionInfo(const QString & id, const QString & type, const QString & time, const QString & releaseTime, const QUrl & url)
	:mId(id), mType(type), mTime(time), mReleaseTime(releaseTime), mUrl(url)
{

}

bool VersionInfo::operator<(const VersionInfo & right) const
{
	return mId < right.getId();
}

VersionInfo::~VersionInfo()
{

}

QString VersionInfo::getId()const
{
	return mId;
}

QString VersionInfo::getType()const
{
	return mType;
}

QString VersionInfo::getTime()const
{
	return mTime;
}

QString VersionInfo::getReleaseTime()const
{
	return mReleaseTime;
}

QUrl VersionInfo::getUrl()const
{
	return mUrl;
}

VersionInfo & VersionInfo::setId(const QString & id)
{
	mId = id;
	return *this;
}

VersionInfo & VersionInfo::setType(const QString & type)
{
	mType = type;
	return *this;
}

VersionInfo & VersionInfo::setTime(const QString & time)
{
	mTime = time;
	return *this;
}

VersionInfo & VersionInfo::setReleaseTime(const QString & releaseTime)
{
	mReleaseTime = releaseTime;
	return *this;
}

VersionInfo & VersionInfo::setUrl(const QUrl & url)
{
	mUrl = url;
	return *this;
}

/**/

VersionInfoList::VersionInfoList(QFile & manifestFile)
{
	init(manifestFile);
}

VersionInfo & VersionInfoList::operator[](const int index)
{
	int i = 0;
	for (auto & j : mVersionInfoVector)
	{
		if (i++ == index)
		{
			return j;
		}
	}

	throw QGSExceptionVersionNotFound();
}

VersionInfoList::~VersionInfoList()
{
}

QString VersionInfoList::getLatestSnapshot() const
{
	return QString();
}

QString VersionInfoList::getLatestRelease() const
{
	return QString();
}

const VersionInfo & VersionInfoList::getVersionInfo(const QString & version)
{
	auto it{ findVersionInfo(version) };
	if (it == mVersionInfoVector.end())
	{
		throw QGSExceptionVersionNotFound();
	}

	return *it;
}

bool VersionInfoList::addVersionInfo(const VersionInfo & versionInfo)
{
	auto && id{ versionInfo.getId() };

	if (id.isEmpty())
	{
		return false;
	}

	mVersionInfoVector.push_back(versionInfo);

	return true;
}

bool VersionInfoList::removeVersionInfo(const QString & version)
{
	auto it{ findVersionInfo(version) };
	if (it == mVersionInfoVector.end())
	{
		return false;
	}

	mVersionInfoVector.erase(it);

	return true;
}

bool VersionInfoList::containsVersionInfo(const QString & version)
{
	auto it{ findVersionInfo(version) };
	if (it == mVersionInfoVector.end())
	{
		return false;
	}

	return true;
}

int VersionInfoList::size()
{
	return mVersionInfoVector.size();
}

void VersionInfoList::init(QFile & manifestFile)
{
	if (!manifestFile.exists())
	{
		throw QGSExceptionInvalidValue();
	}
	//打开文件读取json
	if (!manifestFile.isOpen())
	{
		if (!manifestFile.open(QIODevice::ReadOnly))
		{
			throw QGSExceptionFileIO(manifestFile.fileName());
		}
	}
	QJsonParseError jsonPraseError;
	QJsonDocument jsonDocument{ QJsonDocument::fromJson(manifestFile.readAll(),&jsonPraseError) };
	if (jsonPraseError.error != QJsonParseError::NoError)
	{
		manifestFile.flush();
		throw QGSExceptionJsonPraseError(jsonPraseError);
	}

	if (!praseLatest(jsonDocument.object()) || !praseVersions(jsonDocument.object()))
	{
		throw QGSExceptionJsonPraseError();
	}
}

bool VersionInfoList::praseLatest(QJsonObject & jsonObject)
{
	if (!jsonObject.contains("latest"))
	{
		return false;
	}

	auto && latestObject{ jsonObject.value("latest").toObject() };
	mLatestRelease = latestObject.value("release").toString();
	mLatestSnapshot = latestObject.value("snapshot").toString();
	
	return true;
}

bool VersionInfoList::praseVersions(QJsonObject & jsonObject)
{
	if (!jsonObject.contains("versions"))
	{
		return false;
	}

	auto && versionsArray{ jsonObject.value("versions").toArray() };
	for (auto & i : versionsArray)
	{
		auto && versionObject{ i.toObject() };
		addVersionInfo(VersionInfo{ versionObject.value("id").toString(),
			versionObject.value("type").toString() ,
			versionObject.value("time").toString() ,
			versionObject.value("releaseTime").toString() ,
			versionObject.value("url").toString() });
	}

	return true;
}

void VersionInfoList::sort()
{
	qSort(mVersionInfoVector.begin(), mVersionInfoVector.end(), [](const VersionInfo & left, const VersionInfo & right)
	{
		return left.getId() < right.getId();
	});
}

QVector<VersionInfo>::iterator VersionInfoList::findVersionInfo(const QString & version)
{
	auto it{ mVersionInfoVector.begin() };

	while (it++ != mVersionInfoVector.end())
	{
		if (it->getId() == version)
		{
			break;
		}
	}

	return it;
}
