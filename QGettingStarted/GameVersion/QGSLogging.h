#pragma once

#include <QString>
#include <QStringList>
#include <QMetaType>

#include "QGSDownloads.h"

class QGSLogging
{
public:
	class QGSFileDownload :public QGSDownloadBase
	{
	public:
		QGSFileDownload(const int size = 0, const QString & SHA1 = "", const QString & path = "", const QUrl & url = QUrl(), const QString & id = "") :QGSDownloadBase(size, SHA1, path, url), mId(id)
		{

		}

		QGSFileDownload(const QGSFileDownload & right) = default;

		QGSFileDownload(QGSFileDownload && right) = default;

		QGSFileDownload & operator=(const QGSFileDownload & right) = default;

		QGSFileDownload & operator=(QGSFileDownload && right) = default;

		~QGSFileDownload()
		{

		}
	private:
		QString mId;
	};
public:
	QGSLogging(const QGSFileDownload & fileDownload = QGSFileDownload(), const QString & argument = "", const QString & type = "");

	QGSLogging(const QGSLogging & right) = default;

	QGSLogging(QGSLogging && right) = default;

	QGSLogging & operator=(const QGSLogging & right) = default;

	QGSLogging & operator=(QGSLogging && right) = default;

	~QGSLogging();

	QGSLogging & setFileDownload(const QGSFileDownload & file);
	QGSLogging & setArgument(const QString & argument);
	QGSLogging & setType(const QString & type);

	QGSFileDownload getFileDownload()const;
	QString getArgument()const;
	QString getType()const;
private:
	QGSFileDownload mFileDownload;
	QString mArgument;
	QString mType;
};

Q_DECLARE_METATYPE(QGSLogging::QGSFileDownload)
Q_DECLARE_METATYPE(QGSLogging)
