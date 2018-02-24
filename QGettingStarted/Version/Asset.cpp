#include "Asset.h"

Asset::Asset(const QMap<QString, Object> & objects, const bool _virtual)
{
	mObjects = objects;
	mVirtual = _virtual;
}

Asset::~Asset()
{
}

Asset & Asset::setVirtual(const bool _virtual)
{
	mVirtual = _virtual;
	return *this;
}

Asset & Asset::setObjects(const QMap<QString, Object> & objects)
{
	mObjects = objects;
	return *this;
}

bool Asset::getVirtual()const
{
	return mVirtual;
}

QMap<QString, Asset::Object> Asset::getObjects()const
{
	return mObjects;
}