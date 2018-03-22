#pragma once

#include <QString>
#include <QStringList>

#include "QGSDownloads.h"

class QGSLogging
{
public:
	class File :public QGSDownloads::QGSIDownload
	{
	public:
		File(const int size = 0, const QString & SHA1 = "", const QString & path = "", const QUrl & url = QUrl(), const QString & id = "") :QGSDownloads::QGSIDownload(size, SHA1, path, url), mId(id)
		{

		}

		File(const File & right) = default;

		File(File && right) = default;

		File & operator=(const File & right) = default;

		File & operator=(File && right) = default;

		~File()
		{

		}
	private:
		QString mId;
	};
public:
	QGSLogging(const File & file = File(), const QString & argument = "", const QString & type = "");

	QGSLogging(const QGSLogging & right) = default;

	QGSLogging(QGSLogging && right) = default;

	QGSLogging & operator=(const QGSLogging & right) = default;

	QGSLogging & operator=(QGSLogging && right) = default;

	~QGSLogging();

	QGSLogging & setFile(const File & file);
	QGSLogging & setArgument(const QString & argument);
	QGSLogging & setType(const QString & type);

	File getFile()const;
	QString getArgument()const;
	QString getType()const;
private:
	File mFile;
	QString mArgument;
	QString mType;
};
