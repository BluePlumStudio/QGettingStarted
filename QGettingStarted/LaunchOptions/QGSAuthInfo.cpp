#include "QGSAuthInfo.h"

QGSAuthInfo::QGSAuthInfo(const QString & accessToken, const QString & clientToken, const QString & userType, const Profile & selectedProfile, const QString & twitchAccessToken)
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

QGSAuthInfo & QGSAuthInfo::setSelectedProfile(const Profile & selectedProfile)
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

QGSAuthInfo::Profile QGSAuthInfo::getSelectedProfile()const
{
	return mSelectedProfile;
}

QString QGSAuthInfo::getTwitchAccessToken()const
{
	return mTwitchAccessToken;
}
