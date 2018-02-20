#pragma once

#include <QString>

namespace UserType
{
	const QString MOJANG("Mojang");
	const QString LEGACY("Legacy");
}

class IAuthenticator 
{
public: 
	class AuthenticationInfo
	{
	private:
		QString mUsername;
		QString mUserId;
		QString mAccessToken;
		QString mUserType;
		QString mUserProperties;
	};
public:

};

