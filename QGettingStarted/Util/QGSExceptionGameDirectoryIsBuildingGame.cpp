#include "QGSExceptionGameDirectoryIsBuildingGame.h"


QGSExceptionGameDirectoryIsBuildingGame::QGSExceptionGameDirectoryIsBuildingGame(QGSGameDirectory * gameDirectory) :mGameDirectory(gameDirectory)
{
}


QGSExceptionGameDirectoryIsBuildingGame::~QGSExceptionGameDirectoryIsBuildingGame()
{
}

QGSExceptionGameDirectoryIsBuildingGame * QGSExceptionGameDirectoryIsBuildingGame::clone()const
{
	return new QGSExceptionGameDirectoryIsBuildingGame(*this);
}

void QGSExceptionGameDirectoryIsBuildingGame::raise()const
{
	throw *this;
}

QGSGameDirectory * QGSExceptionGameDirectoryIsBuildingGame::getGameDirectory()const
{
	return mGameDirectory;
}
