#pragma once

#include <QMetaType>

#include "QGSExtract.h"
#include "QGSRules.h"
#include "QGSDownloads.h"

class QGSLibrary 
{
public:
	QGSLibrary(const QString & package = "",
		const QString & name = "",
		const QString & version = "",
		const QGSDownloads & downloads = QGSDownloads(),
		const QGSExtract & extract = QGSExtract(),
		const bool lateload = false,
		const bool native = false,
		const QMap<QString, QString> & natives = QMap<QString, QString>(),
		const QGSRules & rules = QGSRules(),
		const QUrl & url = QUrl());

	QGSLibrary(const QGSLibrary & right) = default;

	QGSLibrary(QGSLibrary && right) = default;

	QGSLibrary & operator=(const QGSLibrary & right) = default;

	QGSLibrary & operator=(QGSLibrary && right) = default;

	~QGSLibrary();

	QGSLibrary & setPackage(const QString & package);
	QGSLibrary & setName(const QString & name);
	QGSLibrary & setVersion(const QString & version);
	QGSLibrary & setDownloads(const QGSDownloads & downloads);
	QGSLibrary & setExtract(const QGSExtract & extract);
	QGSLibrary & setLateload(const bool lateload);
	QGSLibrary & setNative(const bool native);
	QGSLibrary & setNatives(const QMap<QString, QString> & natives);
	QGSLibrary & setRules(const QGSRules & rules);
	QGSLibrary & serUrl(const QUrl & url);

	QString getPackage()const;
	QString getName()const;
	QString getVersion()const;
	QGSDownloads getDownloads()const;
	QGSExtract getExtract()const;
	bool getLateload()const;
	bool getNative()const;
	QMap<QString, QString> getNatives()const;
	QGSRules getRules()const;
	QUrl getUrl()const;

private:
	QString mPackage;
	QString mName;
	QString mVersion;
	QGSDownloads mDownloads;
	QGSExtract mExtract;
	bool mLateload;
	bool mNative;
	QMap<QString, QString> mNatives;
	QGSRules mRules;
	QUrl mUrl;
};

Q_DECLARE_METATYPE(QGSLibrary)