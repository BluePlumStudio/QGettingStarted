#include "QGSLiteLoaderVersionReposity.h"

QGSLiteLoaderVersionReposity::QGSLiteLoaderVersionReposity(const QString & stream, const QString & type, const QUrl & url, const QString & classifier)
	:mStream(stream), mType(type), mUrl(url), mClassifier(classifier)
{
	if (!QMetaType::isRegistered(QMetaType::type("QGSLiteLoaderVersionReposity")))
	{
		qRegisterMetaType<QGSLiteLoaderVersionReposity>("QGSLiteLoaderVersionReposity");
	}
}

QGSLiteLoaderVersionReposity::~QGSLiteLoaderVersionReposity()
{

}

QString QGSLiteLoaderVersionReposity::getStream() const
{
	return mStream;
}

QString QGSLiteLoaderVersionReposity::getType() const
{
	return mType;
}

QUrl QGSLiteLoaderVersionReposity::getUrl() const
{
	return mUrl;
}

QString QGSLiteLoaderVersionReposity::getClassifier() const
{
	return mClassifier;
}

QGSLiteLoaderVersionReposity & QGSLiteLoaderVersionReposity::setStream(const QString & stream)
{
	mStream = stream;
	return *this;
}

QGSLiteLoaderVersionReposity & QGSLiteLoaderVersionReposity::setType(const QString & type)
{
	mType = type;
	return *this;
}

QGSLiteLoaderVersionReposity & QGSLiteLoaderVersionReposity::setUrl(const QUrl & url)
{
	mUrl = url;
	return *this;
}

QGSLiteLoaderVersionReposity & QGSLiteLoaderVersionReposity::setClassifier(const QString & classifier)
{
	mClassifier = classifier;
	return *this;
}
