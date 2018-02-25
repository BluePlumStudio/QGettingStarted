#include "AuthInfo.h"

AuthInfo::AuthInfo(const QString & accessToken, const QString & clientToken, const QString & userType, const Profile & selectedProfile, const QString & twitchAccessToken)
	:mAccessToken(accessToken), mClientToken(clientToken), mUserType(userType), mSelectedProfile(selectedProfile), mTwitchAccessToken(twitchAccessToken)
{
}

AuthInfo::~AuthInfo()
{
}

AuthInfo & AuthInfo::setAccessToken(const QString & accessToken)
{
	mAccessToken = accessToken;
	return *this;
}

AuthInfo & AuthInfo::setClientToken(const QString & clientToken)
{
	mClientToken = clientToken;
	return *this;
}

AuthInfo & AuthInfo::setUserType(const QString & userType)
{
	mUserType = userType;
	return *this;
}

AuthInfo & AuthInfo::setSelectedProfile(const Profile & selectedProfile)
{
	mSelectedProfile = selectedProfile;
	return *this;
}

AuthInfo & AuthInfo::setTwitchAccessToken(const QString & twitchAccessToken)
{
	mTwitchAccessToken = twitchAccessToken;
	return *this;
}

QString AuthInfo::getAccessToken()const
{
	return mAccessToken;
}

QString AuthInfo::getClientToken()const
{
	return mClientToken;
}

QString AuthInfo::getUserType() const
{
	return mUserType;
}

AuthInfo::Profile AuthInfo::getSelectedProfile()const
{
	return mSelectedProfile;
}

QString AuthInfo::getTwitchAccessToken()const
{
	return mTwitchAccessToken;
}
