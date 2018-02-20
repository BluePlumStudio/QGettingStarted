#include "Arguments.h"

Arguments::Arguments()
{
}

Arguments::~Arguments()
{
}

Arguments & Arguments::setJvm(QList<Argument> jvm)
{
	mJvm = jvm;
}

Arguments & Arguments::setGame(QList<Argument> game)
{
	mGame = game;
}

QList<Arguments::Argument> Arguments::getGame()const
{
	return mGame;
}

QList<Arguments::Argument> Arguments::getJVM()const
{
	return mJvm;
}
