#include "Arguments.h"

Arguments::Arguments(QList<Argument> & jvm, QList<Argument> & game)
{
	mJvm = jvm;
	mGame = game;
}

Arguments::~Arguments()
{
}

Arguments & Arguments::setJvm(QList<Argument> jvm)
{
	mJvm = jvm;
	return *this;
}

Arguments & Arguments::setGame(QList<Argument> game)
{
	mGame = game;
	return *this;
}

QList<Arguments::Argument> Arguments::getGame()const
{
	return mGame;
}

QList<Arguments::Argument> Arguments::getJVM()const
{
	return mJvm;
}

void Arguments::clear()
{
	mGame.clear();
	mJvm.clear();
}