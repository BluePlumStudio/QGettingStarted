#include "QGSAuthInfo.h"

QGSAuthInfo::QGSProfile::QGSProfile(const QString & id, const QString name, const bool legacy) 
	:mId(id), mName(name), mLegacy(legacy)
{

}

QGSAuthInfo::QGSProfile::~QGSProfile()
{

}

QGSAuthInfo::QGSProfile & QGSAuthInfo::QGSProfile::setId(const QString & id)
{
	mId = id;
	return *this;
}

QGSAuthInfo::QGSProfile & QGSAuthInfo::QGSProfile::setName(const QString & name)
{
	mName = name;
	return *this;
}

QGSAuthInfo::QGSProfile & QGSAuthInfo::QGSProfile::setId(const bool legacy)
{
	mLegacy = legacy;
	return *this;
}

QString QGSAuthInfo::QGSProfile::getId()const
{
	return mId;
}

QString QGSAuthInfo::QGSProfile::getName()const
{
	return mName;
}

bool QGSAuthInfo::QGSProfile::isLegacy()const
{
	return mLegacy;
}

/**/

QGSAuthInfo::QGSAuthInfo(const QString & accessToken, const QString & clientToken, const QString & userType, const QGSProfile & selectedProfile, const QString & twitchAccessToken)
	:mAccessToken(accessToken), mClientToken(clientToken), mUserType(userType), mSelectedProfile(selectedProfile), mTwitchAccessToken(twitchAccessToken)
{
}

QGSAuthInfo::~QGSAuthInfo()
{
}

QGSAuthInfo & QGSAuthInfo::setAccessToken(const QString & accessToken)
{
	mAccessToken = accessToken;
	return *this;
}

QGSAuthInfo & QGSAuthInfo::setClientToken(const QString & clientToken)
{
	mClientToken = clientToken;
	return *this;
}

QGSAuthInfo & QGSAuthInfo::setUserType(const QString & userType)
{
	mUserType = userType;
	return *this;
}

QGSAuthInfo & QGSAuthInfo::setSelectedProfile(const QGSProfile & selectedProfile)
{
	mSelectedProfile = selectedProfile;
	return *this;
}

QGSAuthInfo & QGSAuthInfo::setTwitchAccessToken(const QString & twitchAccessToken)
{
	mTwitchAccessToken = twitchAccessToken;
	return *this;
}

QString QGSAuthInfo::getAccessToken()const
{
	return mAccessToken;
}

QString QGSAuthInfo::getClientToken()const
{
	return mClientToken;
}

QString QGSAuthInfo::getUserType() const
{
	return mUserType;
}

QGSAuthInfo::QGSProfile QGSAuthInfo::getSelectedProfile()const
{
	return mSelectedProfile;
}

QString QGSAuthInfo::getTwitchAccessToken()const
{
	return mTwitchAccessToken;
}
