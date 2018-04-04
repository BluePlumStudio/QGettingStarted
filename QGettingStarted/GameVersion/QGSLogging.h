#pragma once

#include <QString>
#include <QStringList>
#include <QMetaType>

#include "QGSDownloads.h"

class QGSLogging
{
public:
	class QGSLoggingDownload :public QGSDownloadBase
	{
	public:
		QGSLoggingDownload(const int size = 0, const QString & SHA1 = "", const QString & path = "", const QUrl & url = QUrl(), const QString & id = "") :QGSDownloadBase(size, SHA1, path, url), mId(id)
		{

		}

		QGSLoggingDownload(const QGSLoggingDownload & right) = default;

		QGSLoggingDownload(QGSLoggingDownload && right) = default;

		QGSLoggingDownload & operator=(const QGSLoggingDownload & right) = default;

		QGSLoggingDownload & operator=(QGSLoggingDownload && right) = default;

		~QGSLoggingDownload()
		{

		}
	private:
		QString mId;
	};
public:
	QGSLogging(const QGSLoggingDownload & fileDownload = QGSLoggingDownload(), const QString & argument = "", const QString & type = "");

	QGSLogging(const QGSLogging & right) = default;

	QGSLogging(QGSLogging && right) = default;

	QGSLogging & operator=(const QGSLogging & right) = default;

	QGSLogging & operator=(QGSLogging && right) = default;

	~QGSLogging();

	QGSLogging & setLoggingDownload(const QGSLoggingDownload & file);
	QGSLogging & setArgument(const QString & argument);
	QGSLogging & setType(const QString & type);

	QGSLoggingDownload getLoggingDownload()const;
	QString getArgument()const;
	QString getType()const;
private:
	QGSLoggingDownload mLoggingDownload;
	QString mArgument;
	QString mType;
};

Q_DECLARE_METATYPE(QGSLogging::QGSLoggingDownload)
Q_DECLARE_METATYPE(QGSLogging)
