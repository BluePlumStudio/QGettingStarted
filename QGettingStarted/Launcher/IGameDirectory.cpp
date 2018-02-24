#include "IGameDirectory.h"

IGameDirectory::IGameDirectory(const QDir & baseDir) :mBaseDir(baseDir)
{
	
}

IGameDirectory::IGameDirectory(QDir && baseDir) : mBaseDir(baseDir)
{

}

IGameDirectory::~IGameDirectory()
{
}