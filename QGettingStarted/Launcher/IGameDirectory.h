#pragma once

#include <QDir>
#include <QMap>

class IGameDirectory
{
public:
	IGameDirectory();
	virtual ~IGameDirectory();

protected:
	QDir mBaseDir;
};

