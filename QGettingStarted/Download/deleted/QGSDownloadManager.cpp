#include "QGSDownloadManager.hpp"
#include "Util/QGSUuidGenerator.h"
#include "Util/QGSOperatingSystem.h"

static const QString SEPARATOR = QGSOperatingSystem::getInstance().getSeparator();

template<class T>
QGSDownloadManager<T>::QGSDownloadManager()
{
}

template<class T>
QGSDownloadManager<T>::~QGSDownloadManager()
{
}

template<class T>
QGSDownloader * QGSDownloadManager<T>::generateForgeDownloader(
	DownloadInfo & downloadInfo, 
	const QString & mcversion, 
	const QString & version, 
	const QString & category, 
	const QString & format, 
	const QString & branch)
{
	if (mcversion.isEmpty()
		|| version.isEmpty()
		|| category.isEmpty()
		|| format.isEmpty())
	{
		return nullptr;
	}

	QUrl url{
		QString(mDownloadSource.getApiUrlBase(ApiName::FORGE) + "maven/net/minecraftforge/forge/%1-%2%3/forge-%4-%5%6-%7.%8")
		.arg(mcversion)
		.arg(version)
		.arg(branch.isEmpty() ? "" : QString("(branch?%1:'')").arg(branch))
		.arg(mcversion)
		.arg(version)
		.arg(branch.isEmpty() ? "" : QString("(branch?%1:'')").arg(branch))
		.arg(category)
		.arg(format)
	};

	return new QGSDownloader{ DownloadInfo{ -1,"","",url } };
}
