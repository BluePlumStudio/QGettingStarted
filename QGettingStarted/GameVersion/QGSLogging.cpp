#include "QGSLogging.h"

QGSLogging::QGSLoggingDownload::QGSLoggingDownload(const int size, const QString & SHA1, const QString & path, const QUrl & url, const QString & id)
	:QGSDownloadBase(size, SHA1, path, url), mId(id)
{
	if (!QMetaType::isRegistered(QMetaType::type("QGSLogging::QGSLoggingDownload")))
	{
		qRegisterMetaType<QGSLogging::QGSLoggingDownload>("QGSLogging::QGSLoggingDownload");
	}
}

QGSLogging::QGSLoggingDownload::~QGSLoggingDownload()
{

}

QGSLogging::QGSLogging(const QGSLoggingDownload & fileDownload, const QString & argument, const QString & type) :mLoggingDownload(fileDownload), mArgument(argument), mType(type)
{
	if (!QMetaType::isRegistered(QMetaType::type("QGSLogging")))
	{
		qRegisterMetaType<QGSLogging>("QGSLogging");
	}
}

QGSLogging::~QGSLogging()
{
}

QGSLogging & QGSLogging::setLoggingDownload(const QGSLoggingDownload & fileDownload)
{
	mLoggingDownload = fileDownload;
	return *this;
}

QGSLogging & QGSLogging::setArgument(const QString & argument)
{
	mArgument = argument;
	return *this;
}

QGSLogging & QGSLogging::setType(const QString & type)
{
	mType = type;
	return *this;
}

QGSLogging::QGSLoggingDownload QGSLogging::getLoggingDownload()const
{
	return mLoggingDownload;
}

QString QGSLogging::getArgument()const
{
	return mArgument;
}

QString QGSLogging::getType()const
{
	return mType;
}