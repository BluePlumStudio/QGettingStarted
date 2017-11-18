#include "QGSAuthReply.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

class QGSAuthReply::Private
{
public:
	Private()
	{
		mReply = nullptr;
	}

	~Private()
	{
		if (mReply)
		{
			mReply->deleteLater();
		}

		mReply = nullptr;
	}

public:
	QNetworkReply * mReply;
};


/**/

QGSAuthReply::QGSAuthReply(QNetworkReply * reply, QObject *parent) :QObject(parent), d(new QGSAuthReply::Private)
{
	if (!d)
	{
		throw ExceptionBadAlloc();
	}

	d->mReply = reply;

	connect(d->mReply, &QNetworkReply::finished, this,
		[=]()
	{
		emit finished();
	});

}

/*
QGSAuthReply::QGSAuthReply(const QGSAuthReply & ref):QObject(ref.parent()), d(new QGSAuthReply::Private)
{
	if (!d)
	{
		throw ExceptionBadAlloc();
	}

	d->mReply = ref.d->mReply;
}
*/

QGSAuthReply::ReplyData::ReplyError QGSAuthReply::getReplyData(ReplyData & replyData)const
{
	ReplyData newReplyData;
	QGSAuthReply::ReplyData::ReplyError ret;

	if (d->mReply)
	{
		newReplyData.mData = d->mReply->readAll();
		ret.mErrorCode = (uint)d->mReply->error();

		QJsonDocument jsonDocument = QJsonDocument::fromJson(newReplyData.mData.toUtf8());
		QJsonObject jsonObject = jsonDocument.object();

		if (jsonObject.contains("error"))
		{
			ret.mError = jsonObject.value("error").toString();
			ret.mErrorMessage = jsonObject.value("errorMessage").toString();
			ret.mCause = jsonObject.value("cause").toString();
			newReplyData.mReplyError = ret;
		}
		else
		{
			newReplyData.mAccessToken = jsonObject.value("accessToken").toString();
			newReplyData.mClientToken = jsonObject.value("clientToken").toString();

			if (jsonObject.contains("availableProfiles"))
			{
				QJsonArray jsonArray = jsonObject.value("availableProfiles").toArray();
				const int size = jsonArray.size();
				for (auto i = 0; i < size; i++)
				{
					QJsonObject profileObject = jsonArray.at(i).toObject();
					QGSAuthReply::ReplyData::Profile profile;

					profile.mID = profileObject.value("id").toString();
					profile.mName = profileObject.value("name").toString();
					profile.mLegacy = profileObject.value("legacy").toBool();

					newReplyData.mAvailableProfiles.push_back(profile);
				}
			}

			if (jsonObject.contains("selectedProfile"))
			{
				QJsonObject profileObject = jsonObject.value("selectedProfile").toObject();
				QGSAuthReply::ReplyData::Profile profile;

				profile.mID = profileObject.value("id").toString();
				profile.mName = profileObject.value("name").toString();
				profile.mLegacy = profileObject.value("legacy").toBool();

				newReplyData.mSelectedProfile = profile;
			}
		}

		replyData = newReplyData;
	}

	return ret;
}

QGSAuthReply::~QGSAuthReply()
{
	if (d)
	{
		delete d;
	}

	d = nullptr;
}
