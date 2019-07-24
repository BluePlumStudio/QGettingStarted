#include "QGSOptifineVersionInfo.h"


QGSOptifineVersionInfo::QGSOptifineVersionInfo(const QString & id, const QString & mcversion, const QString & type, const QString & patch, const QString & fileName)
	:mId(id), mMcversion(mcversion), mType(type), mPatch(patch), mFileName(fileName)
{
	if (!QMetaType::isRegistered(QMetaType::type("QGSOptifineVersionInfo")))
	{
		qRegisterMetaType<QGSOptifineVersionInfo>("QGSOptifineVersionInfo");
	}
}

bool QGSOptifineVersionInfo::operator<(const QGSOptifineVersionInfo & right) const
{
	return mMcversion < right.getMcversion() && mType < right.getType() && mPatch < right.getPatch();
}

bool QGSOptifineVersionInfo::operator>(const QGSOptifineVersionInfo & right) const
{
	return mMcversion > right.getMcversion() && mType > right.getType() && mPatch > right.getPatch();
}

bool QGSOptifineVersionInfo::operator==(const QGSOptifineVersionInfo & right) const
{
	return mMcversion == right.getMcversion() && mType == right.getType() && mPatch == right.getPatch();
}

QGSOptifineVersionInfo::~QGSOptifineVersionInfo()
{

}

QString QGSOptifineVersionInfo::getId() const
{
	return mId;
}

QString QGSOptifineVersionInfo::getMcversion() const
{
	return mMcversion;
}

QString QGSOptifineVersionInfo::getType() const
{
	return mType;
}

QString QGSOptifineVersionInfo::getPatch() const
{
	return mPatch;
}

QString QGSOptifineVersionInfo::getFileName() const
{
	return mFileName;
}

QGSOptifineVersionInfo & QGSOptifineVersionInfo::setId(const QString & id)
{
	mId = id;
	return *this;
}

QGSOptifineVersionInfo & QGSOptifineVersionInfo::setMcversion(const QString & mcversion)
{
	mMcversion = mcversion;
	return *this;
}

QGSOptifineVersionInfo & QGSOptifineVersionInfo::setType(const QString & type)
{
	mType = type;
	return *this;
}

QGSOptifineVersionInfo & QGSOptifineVersionInfo::setPatch(const QString & patch)
{
	mPatch = patch;
	return *this;
}

QGSOptifineVersionInfo & QGSOptifineVersionInfo::setFileName(const QString & fileName)
{
	mFileName = fileName;
	return *this;
}
