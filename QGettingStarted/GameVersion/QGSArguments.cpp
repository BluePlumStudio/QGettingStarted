#include "QGSArguments.h"

QGSArguments::QGSArguments(const QList<QGSArgument> & jvm, const QList<QGSArgument> & game)
{
	mJvm = jvm;
	mGame = game;
}

QGSArguments::~QGSArguments()
{
}

QGSArguments & QGSArguments::setJvm(QList<QGSArgument> jvm)
{
	mJvm = jvm;
	return *this;
}

QGSArguments & QGSArguments::setGame(QList<QGSArgument> game)
{
	mGame = game;
	return *this;
}

QList<QGSArguments::QGSArgument> QGSArguments::getGame()const
{
	return mGame;
}

QList<QGSArguments::QGSArgument> QGSArguments::getJVM()const
{
	return mJvm;
}

void QGSArguments::clear()
{
	mGame.clear();
	mJvm.clear();
}