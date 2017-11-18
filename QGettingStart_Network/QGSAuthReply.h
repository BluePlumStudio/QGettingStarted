#pragma once

#include "../QGettingStart_Util/Exception.h"

#include <QNetworkAccessManager>
#include <QNetworkConfiguration>
#include <QNetworkReply>
#include <QNetworkRequest>

class QGSAuthReply :public QObject
{
public:
	Q_OBJECT
public:

	/*Ó¦´ðÄÚÈÝ*/
	struct ReplyData
	{
	public:
		friend class QGSAuthReply;
	public:
		struct Profile
		{
		public:
			Profile(QString ID = "", QString name = "", bool legacy = false) :
				mID(ID), mName(name), mLegacy(legacy)
			{

			}
		public:
			QString mID;
			QString mName;
			bool mLegacy;
		};

		struct ReplyError
		{
		public:
		public:
			ReplyError(QString error = "", QString errorMessage = "", QString cause = "", uint errorCode = 0) :
				mError(error), mErrorMessage(errorMessage), mCause(cause), mErrorCode(errorCode)
			{

			}

			~ReplyError()
			{

			}

		public:
			QString mError;
			QString mErrorMessage;
			QString mCause;
			uint mErrorCode;
		};

	public:
		ReplyData()
		{

		}
		ReplyData(
			QVector<Profile> availableProfiles,
			Profile selectedProfile,
			QString accessToken = "",
			QString clientToken = ""
			) :
			mAccessToken(accessToken),
			mClientToken(clientToken),
			mAvailableProfiles(availableProfiles),
			mSelectedProfile(selectedProfile)
		{

		}
		ReplyData(
			QVector<Profile> availableProfiles,
			QString accessToken = "",
			QString clientToken = ""
			) :
			mAccessToken(accessToken),
			mClientToken(clientToken),
			mAvailableProfiles(availableProfiles)
		{
			mSelectedProfile.mID.clear();
			mSelectedProfile.mName.clear();
			mSelectedProfile.mLegacy = false;
		}
		~ReplyData()
		{

		}
	private:

	public:
		QString mAccessToken;
		QString mClientToken;
		QVector<Profile> mAvailableProfiles;
		Profile mSelectedProfile;

		QString mData;

		ReplyError mReplyError;
	};

public:
	explicit QGSAuthReply(QNetworkReply * reply, QObject *parent = nullptr);
	QGSAuthReply(const QGSAuthReply & ref)Q_DECL_EQ_DELETE;
	QGSAuthReply & operator =(QGSAuthReply rhs)Q_DECL_EQ_DELETE;

	QGSAuthReply::ReplyData::ReplyError getReplyData(ReplyData & replyData)const;

	~QGSAuthReply();
signals:
	void finished();

public:
	class Private;
	friend class Private;
	friend class QGSNetwork;

	Private * d;
};

