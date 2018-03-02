#pragma once

#include <QString>

namespace UserType
{
	const QString MOJANG("Mojang");
	const QString LEGACY("Legacy");
}

class AuthInfo
{
public:
	struct Profile
	{
		Profile(const QString & id = "{}", const QString name = "{}", const bool legacy = false) :mId(id), mName(name), mLegacy(legacy)
		{

		}

		Profile(const Profile & right) = default;

		Profile(Profile && right) = default;

		Profile & operator=(const Profile & right) = default;

		Profile & operator=(Profile && right) = default;

		~Profile()
		{

		}

		Profile & setId(const QString & id)
		{
			mId = id;
			return *this;
		}

		Profile & setName(const QString & name)
		{
			mName = name;
			return *this;
		}

		Profile & setId(const bool legacy)
		{
			mLegacy = legacy;
			return *this;
		}

		QString getId()const
		{
			return mId;
		}

		QString getName()const
		{
			return mName;
		}

		bool getLegacy()const
		{
			return mLegacy;
		}

	private:
		QString mId;
		QString mName;
		bool mLegacy;
	};
public:
	AuthInfo(const QString & accessToken = "{}",
		const QString & clientToken = "{}",
		const QString & userType = UserType::LEGACY,
		const Profile & selectedProfile = Profile(),
		const QString & twitchAccessToken = "{}");
	
	~AuthInfo();

	AuthInfo & setAccessToken(const QString & accessToken);
	AuthInfo & setClientToken(const QString & clientToken);
	AuthInfo & setUserType(const QString & userType);
	AuthInfo & setSelectedProfile(const Profile & selectedProfile);
	AuthInfo & setTwitchAccessToken(const QString & twitchAccessToken);

	QString getAccessToken()const;
	QString getClientToken()const;
	QString getUserType()const;
	Profile getSelectedProfile()const;
	QString getTwitchAccessToken()const;

private:
	QString mAccessToken;
	QString mClientToken;
	QString mUserType;
	Profile mSelectedProfile;
	QString mTwitchAccessToken;
};
