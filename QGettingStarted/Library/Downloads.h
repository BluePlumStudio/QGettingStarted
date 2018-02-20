#pragma once

#include <QString>
#include <QUrl>
#include <QMap>
#include <QStringList>

class Downloads
{
public:
	class Download
	{
	protected:
		int mSize;
		QString mSHA1;
		QString mPath;
		QUrl mUrl;
	};
public:
	Download mArtifact;
	QMap<QString, Download> mClassifiers;
};
