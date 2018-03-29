#pragma once

#include <QString>
#include <QUrl>

class QGSGameVersionInfo
{
public:
	QGSGameVersionInfo(const QString & id = "", const QString & type = "", const QString & time = "", const QString & releaseTime = "", const QUrl & url = QUrl());

	QGSGameVersionInfo(const QGSGameVersionInfo & right) = default;

	QGSGameVersionInfo(QGSGameVersionInfo && right) = default;

	QGSGameVersionInfo & operator=(const QGSGameVersionInfo & right) = default;

	QGSGameVersionInfo & operator=(QGSGameVersionInfo && right) = default;

	bool operator<(const QGSGameVersionInfo & right)const;

	bool operator>(const QGSGameVersionInfo & right)const;

	bool operator==(const QGSGameVersionInfo & right)const;

	~QGSGameVersionInfo();

	QString getId()const;
	QString getType()const;
	QString getTime()const;
	QString getReleaseTime()const;
	QUrl getUrl()const;

	QGSGameVersionInfo & setId(const QString & id);
	QGSGameVersionInfo & setType(const QString & type);
	QGSGameVersionInfo & setTime(const QString & time);
	QGSGameVersionInfo & setReleaseTime(const QString & releaseTime);
	QGSGameVersionInfo & setUrl(const QUrl & url);

private:
	QString mId;
	QString mType;
	QString mTime;
	QString mReleaseTime;
	QUrl mUrl;
};
