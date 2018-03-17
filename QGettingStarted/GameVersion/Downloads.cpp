#include "Downloads.h"

Downloads::Downloads(Download & artifact, QMap<QString, Download> & classifiers)
	:mArtifact(artifact), mClassifiers(classifiers)
{

}

Downloads::~Downloads()
{

}

Downloads & Downloads::setArtifact(const Download & artifact)
{
	mArtifact = artifact;
	return *this;
}

Downloads & Downloads::setClassifiers(const QMap<QString, Download> & classifiers)
{
	mClassifiers = classifiers;
	return *this;
}

Downloads::Download Downloads::getArtifact()const
{
	return mArtifact;
}

QMap<QString, Downloads::Download> Downloads::getClassifiers()const
{
	return mClassifiers;
}

void Downloads::clear()
{
	mArtifact.clear();
	mClassifiers.clear();
}
