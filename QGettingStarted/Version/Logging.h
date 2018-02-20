#pragma once

#include <QString>
#include <QStringList>

#include "Downloads.h"

class Logging
{
private:
	class File :public Downloads::Download
	{
	public:
		File(const int size, const QString & SHA1, const QString & path, const QUrl & url, const QString & id) :Downloads::Download(size, SHA1, path, url), mId(id)
		{

		}
		~File()
		{

		}
	private:
		QString mId;
	};
public:
	Logging();
	~Logging();

private:
	//File mFile;
	QString mArgument;
	QString mType;
};
