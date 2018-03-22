#include "QGSDownloads.h"

QGSDownloads::QGSDownloads(QGSIDownload & artifact, QMap<QString, QGSIDownload> & classifiers)
	:mArtifact(artifact), mClassifiers(classifiers)
{

}

QGSDownloads::~QGSDownloads()
{

}

QGSDownloads & QGSDownloads::setArtifact(const QGSIDownload & artifact)
{
	mArtifact = artifact;
	return *this;
}

QGSDownloads & QGSDownloads::setClassifiers(const QMap<QString, QGSIDownload> & classifiers)
{
	mClassifiers = classifiers;
	return *this;
}

QGSDownloads::QGSIDownload QGSDownloads::getArtifact()const
{
	return mArtifact;
}

QMap<QString, QGSDownloads::QGSIDownload> QGSDownloads::getClassifiers()const
{
	return mClassifiers;
}

void QGSDownloads::clear()
{
	mArtifact.clear();
	mClassifiers.clear();
}
