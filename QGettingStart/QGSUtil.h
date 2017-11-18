#pragma once

#include "QGSAbstractLauncher.h"
#include "QGSGameBuilder.h"
#include "QGSGame.h"

#include <string>

#include <QDir>
#include <QSettings>
#include <QStringList>
#include <QSysInfo>
#include <QDebug>

class QGSUtil
{
public:
	class Library
	{
	public:
		struct Downloads
		{
		public:
			Downloads(QString path = "", QString SHA1 = "", int size = -1, QString URL = "") :
				mPath(path), mSHA1(SHA1), mSize(size), mURL(URL)
			{

			}
		public:
			QString mPath;
			QString mSHA1;
			int mSize;
			QString mURL;
		};
	public:
		Library()
		{

		}

		~Library()
		{

		}

	public:
		QString mName;
		Downloads mDownloads;
	};
public:
	static QGSUtil * getInstance();

	QGSAbstractLauncher::LauncherError getLibrariesStringVector(QGSGame * game, QVector<QString> & item);

	QGSAbstractLauncher::LauncherError getMissingLibrariesStringVector(QGSGame * game, QVector<QString> & item);

	QGSAbstractLauncher::LauncherError getMinecraftArgumentsString(QGSGame * game, QString & item);

	QGSAbstractLauncher::LauncherError getLibrariesVector(QGSGame * game, QVector<Library> & item);

	bool replaceVariable(QString & arguments, QString before, QString after);

	static bool getJavaPathVectorFromStorage(QVector<QString> & vector, QString baseDirectory);

	static bool getJavaPathVectorFromSystemSettings(QVector<QString> & vector);

	static void praseServerAddress(QString serverAddress, QString & address, QString & port);

	static void praseLibraryName(QJsonObject & libraryObject, QString & name);

	static bool praseLibraryAllow(QJsonObject & libraryObject);

	static void praseOriginLibraryDownloads(QJsonObject & libraryObject, Library & library, QString URL = "https://libraries.minecraft.net/");

	static QString getUUID(QString seed);

	~QGSUtil();
private:
	QGSUtil();
private:
};

