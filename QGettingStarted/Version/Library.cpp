#include "Library.h"

Library::Library(const QString & package,
	const QString & name,
	const QString & version,
	const Downloads & downloads,
	const Extract & extract,
	const bool lateload,
	const bool native,
	const QMap<QString, QString> & natives,
	const Rules & rules)
	:mPackage(package), mName(name), mVersion(version), mDownloads(downloads), mExtract(extract), mLateload(lateload), mNative(native), mNatives(natives), mRules(rules)
{

}

Library::~Library()
{

}

Library & Library::setPackage(const QString & package)
{
	mPackage = package;
	return *this;
}

Library & Library::setName(const QString & name)
{
	mName = name;
	return *this;
}

Library & Library::setVersion(const QString & version)
{
	mVersion = version;
	return *this;
}

Library & Library::setDownloads(const Downloads & downloads)
{
	mDownloads = downloads;
	return *this;
}

Library & Library::setExtract(const Extract & extract)
{
	mExtract = extract;
	return *this;
}

Library & Library::setLateload(const bool lateload)
{
	mLateload = lateload;
	return *this;
}

Library & Library::setNative(const bool native)
{
	mNative = native;
	return *this;
}

Library & Library::setNatives(const QMap<QString, QString> & natives)
{
	mNatives = natives;
	return *this;
}

Library & Library::setRules(const Rules & rules)
{
	mRules = rules;
	return *this;
}

QString Library::getPackage()const
{
	return mPackage;
}

QString Library::getName()const
{
	return mName;
}

QString Library::getVersion()const
{
	return mVersion;
}

Downloads Library::getDownloads()const
{
	return mDownloads;
}

Extract Library::getExtract()const
{
	return mExtract;
}

bool Library::getLateload()const
{
	return mLateload;
}

bool Library::getNative() const
{
	return mNative;
}

QMap<QString, QString> Library::getNatives()const
{
	return mNatives;
}

Rules Library::getRules()const
{
	return mRules;
}
