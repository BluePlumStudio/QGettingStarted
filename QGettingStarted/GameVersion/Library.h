#pragma once

#include "Extract.h"
#include "Rules.h"
#include "Downloads.h"

class Library 
{
public:
	Library(const QString & package = "",
		const QString & name = "",
		const QString & version = "",
		const Downloads & downloads = Downloads(),
		const Extract & extract = Extract(),
		const bool lateload = false,
		const bool native = false,
		const QMap<QString, QString> & natives = QMap<QString, QString>(),
		const Rules & rules = Rules(),
		const QUrl & url = QUrl());

	Library(const Library & right) = default;

	Library(Library && right) = default;

	Library & operator=(const Library & right) = default;

	Library & operator=(Library && right) = default;

	~Library();

	Library & setPackage(const QString & package);
	Library & setName(const QString & name);
	Library & setVersion(const QString & version);
	Library & setDownloads(const Downloads & downloads);
	Library & setExtract(const Extract & extract);
	Library & setLateload(const bool lateload);
	Library & setNative(const bool native);
	Library & setNatives(const QMap<QString, QString> & natives);
	Library & setRules(const Rules & rules);
	Library & serUrl(const QUrl & url);

	QString getPackage()const;
	QString getName()const;
	QString getVersion()const;
	Downloads getDownloads()const;
	Extract getExtract()const;
	bool getLateload()const;
	bool getNative()const;
	QMap<QString, QString> getNatives()const;
	Rules getRules()const;
	QUrl getUrl()const;

private:
	QString mPackage;
	QString mName;
	QString mVersion;
	Downloads mDownloads;
	Extract mExtract;
	bool mLateload;
	bool mNative;
	QMap<QString, QString> mNatives;
	Rules mRules;
	QUrl mUrl;
};
