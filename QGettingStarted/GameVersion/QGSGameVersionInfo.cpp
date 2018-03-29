#include "QGSGameVersionInfo.h"


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