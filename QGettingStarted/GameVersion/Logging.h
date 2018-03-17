#pragma once

#include <QString>
#include <QStringList>

#include "Downloads.h"

class Logging
{
public:
	class File :public Downloads::Download
	{
	public:
		File(const int size = 0, const QString & SHA1 = "", const QString & path = "", const QUrl & url = QUrl(), const QString & id = "") :Downloads::Download(size, SHA1, path, url), mId(id)
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
	Logging(const File & file = File(), const QString & argument = "", const QString & type = "");

	Logging(const Logging & right) = default;

	Logging(Logging && right) = default;

	Logging & operator=(const Logging & right) = default;

	Logging & operator=(Logging && right) = default;

	~Logging();

	Logging & setFile(const File & file);
	Logging & setArgument(const QString & argument);
	Logging & setType(const QString & type);

	File getFile()const;
	QString getArgument()const;
	QString getType()const;
private:
	File mFile;
	QString mArgument;
	QString mType;
};
