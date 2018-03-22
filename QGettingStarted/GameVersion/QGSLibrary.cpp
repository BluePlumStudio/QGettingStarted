#include "QGSLibrary.h"

QGSLibrary::QGSLibrary(const QString & package,
	const QString & name,
	const QString & version,
	const QGSDownloads & downloads,
	const QGSExtract & extract,
	const bool lateload,
	const bool native,
	const QMap<QString, QString> & natives,
	const QGSRules & rules,
	const QUrl & url)
	:mPackage(package), mName(name), mVersion(version), mDownloads(downloads), mExtract(extract), mLateload(lateload), mNative(native), mNatives(natives), mRules(rules), mUrl(url)
{

}

QGSLibrary::~QGSLibrary()
{

}

QGSLibrary & QGSLibrary::setPackage(const QString & package)
{
	mPackage = package;
	return *this;
}

QGSLibrary & QGSLibrary::setName(const QString & name)
{
	mName = name;
	return *this;
}

QGSLibrary & QGSLibrary::setVersion(const QString & version)
{
	mVersion = version;
	return *this;
}

QGSLibrary & QGSLibrary::setDownloads(const QGSDownloads & downloads)
{
	mDownloads = downloads;
	return *this;
}

QGSLibrary & QGSLibrary::setExtract(const QGSExtract & extract)
{
	mExtract = extract;
	return *this;
}

QGSLibrary & QGSLibrary::setLateload(const bool lateload)
{
	mLateload = lateload;
	return *this;
}

QGSLibrary & QGSLibrary::setNative(const bool native)
{
	mNative = native;
	return *this;
}

QGSLibrary & QGSLibrary::setNatives(const QMap<QString, QString> & natives)
{
	mNatives = natives;
	return *this;
}

QGSLibrary & QGSLibrary::setRules(const QGSRules & rules)
{
	mRules = rules;
	return *this;
}

QGSLibrary & QGSLibrary::serUrl(const QUrl & url)
{
	mUrl = url;
	return *this;
}

QString QGSLibrary::getPackage()const
{
	return mPackage;
}

QString QGSLibrary::getName()const
{
	return mName;
}

QString QGSLibrary::getVersion()const
{
	return mVersion;
}

QGSDownloads QGSLibrary::getDownloads()const
{
	return mDownloads;
}

QGSExtract QGSLibrary::getExtract()const
{
	return mExtract;
}

bool QGSLibrary::getLateload()const
{
	return mLateload;
}

bool QGSLibrary::getNative() const
{
	return mNative;
}

QMap<QString, QString> QGSLibrary::getNatives()const
{
	return mNatives;
}

QGSRules QGSLibrary::getRules()const
{
	return mRules;
}

QUrl QGSLibrary::getUrl() const
{
	return mUrl;
}
