#pragma once

#include <QString>

namespace UserType
{
	const QString Mojang("Mojang");
	const QString Legacy("Legacy");
}

class QGSAuthInfo
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
	QGSAuthInfo(const QString & accessToken = "{}",
		const QString & clientToken = "{}",
		const QString & userType = UserType::Legacy,
		const Profile & selectedProfile = Profile(),
		const QString & twitchAccessToken = "{}");
	
	~QGSAuthInfo();

	QGSAuthInfo & setAccessToken(const QString & accessToken);
	QGSAuthInfo & setClientToken(const QString & clientToken);
	QGSAuthInfo & setUserType(const QString & userType);
	QGSAuthInfo & setSelectedProfile(const Profile & selectedProfile);
	QGSAuthInfo & setTwitchAccessToken(const QString & twitchAccessToken);

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
