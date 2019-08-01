#pragma once
#include "QGSException.h"
#include "../Launcher/QGSGameDirectory.h"

class QGSExceptionGameDirectoryIsBuildingGame :
	public QGSException
{
public:
	QGSExceptionGameDirectoryIsBuildingGame(QGSGameDirectory * gameDirectory = nullptr);

	virtual ~QGSExceptionGameDirectoryIsBuildingGame();

	virtual QGSExceptionGameDirectoryIsBuildingGame * clone()const override;

	virtual void raise()const override;

	QGSGameDirectory * getGameDirectory()const;
private:
	QGSGameDirectory * mGameDirectory;
};

