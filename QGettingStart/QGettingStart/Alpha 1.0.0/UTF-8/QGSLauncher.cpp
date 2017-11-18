#include "QGSLauncher.h"

using namespace std;

QGSLauncher::QGSLauncher()
{
}


QGSLauncher::~QGSLauncher()
{
}

QVector<QString> QGSLauncher::getStringVector(Game * game, Option option)
{
	QGSGame * tmpGame = (QGSGame *)game;
	vector<string> strVector;
	QVector<QString> ret;

	if (tmpGame)
	{
		switch (option)
		{
		case Option::LIBRARIES:
			strVector = mLauncher.getStyledLibrariesStringVector(tmpGame->game, true);
			break;
		case Option::LIBRARIES_MISSING:
			strVector = mLauncher.getMissingLibrariesStringVector(tmpGame->game, true);
			break;
		default:
			strVector.clear();
			ret.clear();
			break;
		}

		for (vector<string>::iterator it = strVector.begin(); it != strVector.end(); ++it)
		{
			ret.push_back(QString::fromLocal8Bit((*it).c_str()));
		}
	}

	return ret;
}

QString QGSLauncher::getString(Game * game, Option option)
{
	QGSGame * tmpGame = (QGSGame *)game;
	string str;
	QString ret;

	if (tmpGame)
	{
		switch (option)
		{
		case Option::LAUNCH:
			mLauncher.getLaunchString(tmpGame->game, str);
			break;
		case Option::MINECRAFT_ARGUMENTS:
			str = mLauncher.getStyledMinecraftArgumentsString(tmpGame->game);
			break;
		default:
			str = "";
			ret = "";
			break;
		}

		ret = QString::fromLocal8Bit(str.c_str());
	}

	return ret;
}